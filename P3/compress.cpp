#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

 /** compress.cpp
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
    cout << "Please check that the file \"" << argv[1] << "\" exists and try again." << endl;
    return -1;
  }

  // 2. Read bytes form the file, counting the number of occurrences of each byte value; then close the file
  vector<int> freqTable(256, 0);
  BitInputStream bistream(inStream);
  byte buf;
  int index;
  
  while (!inStream.eof()) {
    buf = inStream.get();
    index = (int)buf;
    freqTable[index]++;
  }
  inStream.close();
  
  // 3. Use these bytes to construct a Huffman coding tree.
  HCTree huffTree;
  huffTree.build(freqTable);
  
  // 4. Open the output file for writing.
  ofstream outStream;
  outStream.open(argv[2], ios::binary);
  if (outStream.fail()) {
    cout << "Error: Failed to open output stream!" << endl;
    cout << "Please check write permissions and try again." << endl;
    return -1;
  }
  
  // 5. Write enough information (a "file header") to the output file to enable the coding tree
  //    to be reconstructed when the file is read by the uncompress program
  for (int i = 0; i < freqTable.size(); i++) {
    outStream << " " << freqTable.at(i);
  }
  
  // 6. Open the input file for reading, again.
  inStream.open(argv[1], ios::binary);
  
  
  // 7. Using the Huffman coding tree, translate each byte from the input file into it code,
  //    and append these codes as a sequence of bits to the output file, after the header.
  BitOutputStream bostream(outStream);
  
  while (!inStream.eof()) {
    char c = inStream.get();
    buf = (byte) c;
    huffTree.encode(buf, bostream);
  }
  bostream.flush();
  
  // 8. Close the input and output files.
  inStream.close();
  outStream.close();
  
  return 0;
}
