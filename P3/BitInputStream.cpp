#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <iostream>
#include <fstream>

using namespace std;

 /** BitOutputStream.cpp
  *  Author: Evan Carey (cs100vbg)
  */


int BitInputStream::readBit() {
  // If all bits in the buffer are read, fill the buffer first
  if (nbits == 8) {
    fill();
    if (!in.good()) return -1;
  }
	
  if (in.good()) {
    // Get the bit at the appropriate location in the bit buffer
    int bit = ((buf & (1 << (7 - nbits))) ? 1 : 0);
    
    nbits++;	// Increment the index   
    return bit; // Return the bit
  } else {
    return -1;
  }
}
