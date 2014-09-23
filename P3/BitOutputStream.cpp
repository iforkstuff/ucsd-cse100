#include "BitOutputStream.hpp"
#include <iostream>
#include <fstream>

using namespace std;

 /** BitOutputStream.cpp
  *  Author: Evan Carey (cs100vbg)
  */

BitOutputStream::~BitOutputStream() {
  if (nbits) flush();
}

void BitOutputStream::writeBit(int i) {

  if (out.good()) {
    // Write the least significant bit of i into the buffer
    // at the current index
    int j = i << (7 - nbits);
    buf |= j;
    
    nbits++; // increment the index
    
    // if the buffer's full, flush it
    if (nbits == 8) flush();
    
  } else {
    flush();
  } 
}
