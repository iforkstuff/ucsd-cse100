#include "HCNode.hpp"

using namespace std;

 /** HCNode.cpp
  *  Author: Evan Carey (cs100vbg)
  */

HCNode::~HCNode() {}

bool HCNode::operator<(const HCNode& other) {
  // Reverse comparison operator so Huffman Tree correctly assigns shorter
  // codes to more frequently occurring symbols
  return count > other.count;
}

bool comp(HCNode* one, HCNode* other) {
  return *one < *other;
}
