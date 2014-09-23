#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

 /** uncompress.cpp
  *  Author: Evan Carey (cs100vbg)
  */
int main(int argc, char** argv) {

  // Test to ensure two files are specified
  if (argc != 3) {
    cout << "Error: Invalid Arguments!" << endl;
    cout << "Files must be specified in the format \"./compress [input_file] [output_file]\"" << endl;
    cout << "Please try again." << endl;
    return -1;
  }
  
  // Test to ensure files are different
  if (strcmp(argv[1], argv[2]) == 0) {
    cout << "Error: Unsupported Operation!" << endl;
    cout << "Files specified for input and output must be distinct" << endl;
    cout << "Please try again." << endl;
    return -1;
  }
  
  
  
  // 1. Open the input file for reading.
  ifstream inStream;
  inStream.open(argv[1], ios::binary);
  if (inStream.fail()) {
    cout << "Error: Failed to open input stream!" << endl;
    cout << "Please check that the file\"" << argv[1] << "\" exists and try again." << endl;
    return -1;
  }
  
  // 2. Read the file header at the beginning of the input file, and reconstruct the Huffman coding tree.
  /** NOTE - must have a test to make sure input file was compressed using the compress program */
  vector<int> freqTable(256);
  
  int n;
  byte buf;
  int count = 0;
  int total = 0;
  
  for (int i = 0; i < freqTable.size(); i++) {
    inStream >> n;
    if (!inStream.good()) {
      cout << "Error reading file header." << endl;
      cout << "Please check \"" << argv[1] << "\" was compressed properly and try again." << endl;
      inStream.close();
      return -1;
    }
    freqTable[i] = n;
    total += n;
  }
  
  // reconstruct Huffman tree
  HCTree huffTree;
  huffTree.build(freqTable);
  
  
  // 3. Open the output file for writing.
  ofstream outStream;
  outStream.open(argv[2], ios::binary);
  if (outStream.fail()) {
    cout << "Error: Failed to open output stream!" << endl;
    cout << "Please check write permissions and try again." << endl;
    return -1;
  }
  
  
  // 4. Using the Huffman coding tree, decode the bits from the input file into
  //    the appropriate sequence of bytes, writing them to the output file.
  BitInputStream bistream(inStream);
  
  for (int i = 0; i < total; i++) {
    buf = huffTree.decode(bistream);
    if (buf == (byte)-1) break;
    outStream.put(buf);
  }
  
  // 5. Close the input and output files.
  inStream.close();
  outStream.close();
  
  return 0;
}
