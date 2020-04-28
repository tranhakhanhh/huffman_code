/*
File: huffman.cpp
------------------
This program compresses and decompresses text files using prefix-free code.
Author: Khue Le, Khanh Tran
*/


#include <string>
#include <map>
#include "pqueue.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;

class Node
{

  public:

    Node (string c, double f)
    {
      letter = c;
      freq = f;
    }

    void update(string c, double f) // update new letter and freq value
    {
      letter = c;
      freq = f;
    }

    bool operator<(const Node& node) // Compare feq value. Return 1 if LHS<RHS and vice versa
    {
      if (freq < node.freq)
          return 1;
      return 0;
    }

    std::string toString() const
    {
      std::stringstream ss;
      ss << "(" << letter << ", " << freq << ")";
      return ss.str();
    }

    string letter;
    double freq;

};

std::ostream& operator<<(std::ostream& stream, const Node& node)
{
  stream<< node.toString();
  return stream;
};

//Compress text file inFileName into huffman-encoded file outFileName.
void compress(string inFileName, string outFileName)
{
  //Read in text file content to string fullText
  string fullText = "";
  std::ifstream ifs(inFileName);
  fullText.assign( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()) );



  //Create a map to hold letters in fullText and its frequency
  map<char, int> letterFreq;
  for (unsigned int m=0; m < fullText.length(); m++)         //Read in char by char
  {
    //populate map of letter-times appeared in text
    if (letterFreq.find(fullText[m]) == letterFreq.end())
    {
      letterFreq.insert(pair<char,int>(fullText[m],1));
    }
    else
    {
      letterFreq[fullText[m]] = letterFreq[fullText[m]]+1;
    }
  }

  //create a vector of nodes for each pair in map <char, int>
  vector <Node> nodeOfTree;

  map<char, int>::iterator mit;
  string letter;
  double frequency;
  for (mit = letterFreq.begin(); mit != letterFreq.end(); mit++)
  {
    //transform said key and value to Node
    letter = mit->first;
    frequency = mit->second;
    Node myNode (letter, frequency);
    nodeOfTree.push_back(myNode);
  }

  //Populate priorityQueue with Nodes of letter-frequency
  MinPriorityQueue<Node> pq(letterFreq.size());
  vector<Node>::iterator vit;
  for (vit = nodeOfTree.begin(); vit != nodeOfTree.end(); vit++)
  {
    pq.insert(&(*vit)); //add Node to priority queue
  }

  //Create and populate actual Maping of our encoding (letter, encoding)
  map<char, string> resultMap;
  while (pq.length()>1)
  {
    Node* min0 = pq.extractMin();
    Node* min1 = pq.extractMin();

    string letter0 = min0->letter;
    double freq0 = min0->freq;

    string letter1 = min1->letter;
    double freq1 = min1->freq;

    for (int unsigned i =0; i<letter0.length(); i++)
    {
      resultMap[letter0[i]] = "0" + resultMap[letter0[i]];
    }

    for (int unsigned i =0; i<letter1.length(); i++)
    {
      resultMap[letter1[i]] = "1" + resultMap[letter1[i]];
    }

    string newletter = letter0 + letter1;
    double newfreq = freq0 + freq1;

    (*min0).update(newletter, newfreq);
    pq.insert(min0);
  }

  //Write map encoding and actuall compressed file content into outFileName
  ofstream outdata;
  //clear old data in file
  outdata.open(outFileName,ios::out|ios::trunc);
  outdata.close();

  //write to file
  outdata.open(outFileName,ios::app);


  map<char, string>::iterator it;
  for (it = resultMap.begin(); it != resultMap.end(); it++)
  {
    outdata << it->first << it->second << ",";
  }
  outdata << "aa";// TERMINATION OF HEADER WARNING CHARACTERS!

  string binary = ""; //string that holds 0s and 1s to convert to bit string
  for (unsigned int j=0; j<fullText.length(); j++) //encode all chars to binary
  {
    binary = binary + resultMap[fullText[j]];
  }

  //Make padding
  string pad = "";
  if (binary.length() % 8 ==0)
  {
    pad = "00000001";
  }
  else
  {
    for (unsigned int p=0; p < (8 - binary.length()%8)-1; p++)
    {
      pad = pad +"0";
    }
    pad = pad + "1";
  }
  binary = pad + binary;


  //convert from binary to ascii characters
  std::stringstream sstream(binary);
  string bitStr = "";
  while(sstream.good())
  {
      std::bitset<8> bits;
      sstream >> bits;
      char c = char(bits.to_ulong());
      bitStr += c;
  }
  outdata << bitStr;
  outdata.close();
}




void decompress(string inFileName, string outFileName)
{
  //put all characters in the input file to a string named fullText
  string fullText = "";
  std::ifstream ifs(inFileName);
  fullText.assign( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>()) );



   //create a map called encode to hold 0s and 1s and their encoding
  map<string, char> encode;
  unsigned int i =0;
  while(1)
  {
    if ((fullText[i] == 'a') && (fullText[i+1] == 'a')) //terminate loop when you see aa - header terminator
    {
      break;
    }
    if ((fullText[i] == ',') && (fullText[i-1] != ',')) //skip if the current comma is a separator between encodings
    {
      i++;
    }
    else
    {
      string e = "";
      int j= i+1;
      while(fullText[j] != ',') //iterate through the encoding of the letter fullText[i]
      {
        e = e + fullText[j];
        j++;
      }
      encode.insert(pair<string,char>(e,fullText[i])); //add the encoding from 0s and 1s to letter
      i=j+1; //skip through the separator to the next letter or terminator
    }
  }
  i=i+2; //go through the latter a of terminator a


  ofstream outdata;
  //clear old data in file
  outdata.open(outFileName,ios::out|ios::trunc);
  outdata.close();

  //write to file
  outdata.open(outFileName,ios::app);
  //convert everything to binary;
  string binary="";

  while(i < fullText.length())
  {
    binary= binary + bitset<8>(fullText.c_str()[i]).to_string();
    //binary= binary + bitset<8>(fullText[i]).to_string();
    i++;
  }

  //from binary, write corresponding letters
  unsigned int b=0;
  while (binary[b] != '1') //skip over the padding
  {
    b++;
  }
  b++; //go over number 1 of our padding

  string s = ""; //binary string to encode
  while(b <binary.length()) //go through the rest of the compressed file
  {
    s = s + binary[b];
    if (encode.find(s) != encode.end()) //if the combination of 0s and 1s so far can be encoded
    {
      outdata << encode[s]; //write the encoded letter to the output file
      s= ""; //reset the string to hold the next combination of 0s and 1s for encoding
    }
    b++;
  }
  outdata.close();
}



int main(int argc, char** argv)
{
  string src; //string that holds name of source file
  string dest; //string that holds name of destination file

  if (strcmp(argv[1], "-c") == 0)
  {
    src = argv[2];
    dest = argv[3];
    compress(src, dest); //call compress if command line has -c
  }
  else if (strcmp(argv[1], "-d") == 0)
  {
    src = argv[2];
    dest = argv[3];
    decompress(src, dest); ////call decompress if command line has -d
  }
  return 0;
}
