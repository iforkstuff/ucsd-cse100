#ifndef BISTREAM_HPP
#define BISTREAM_HPP

#include <iostream>

typedef unsigned char byte;
 /** BitInputStream.hpp
  *  Author: Evan Carey (cs100vbg)
  *  *Adapted from Paul Kube's BitInputStream class.
  */
class BitInputStream {
private:
  byte buf;		// one byte buffer of bits
  int nbits;		// how many bits have been read from buf
  std::istream& in;	// the input stream to use

public:
  /** Initialize a BitInputStream that will use
   *  the given istream for input.
   */
  BitInputStream(std::istream& is) : in(is) {
    buf = 0; // clear buffer
    nbits = 8; // initialize bit index
  }


  /** Fill the buffer from the input */
  void fill() {
    nbits = 0;
    buf = in.get();
  }

  /** Read the next bit from the bit buffer.
   *  Fill the buffer from the input stream first if needed.
   *  Return 1 if the bit read is 1;
   *  return 0 if the bit read is 0.
   */
  int readBit();

};
#endif // BISTREAM_HPP
