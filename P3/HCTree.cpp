#include "HCTree.hpp"
#include <string>

 /** HCTree.cpp
  *  Author: Evan Carey (cs100vbg)
  */

HCTree::~HCTree() {
	clear(root);
}

void HCTree::build(const vector<int>& freqs) {

	priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest;

	// Create leaf nodes to store symbols in the frequency table
	// and add them to the forest
	for (int i = 0; i < freqs.size(); i++) {
		if (freqs[i] != 0) {
			leaves[i] = new HCNode(freqs.at(i), i);
			forest.push(leaves[i]);
		}
	}

	// Special case for a forest with only one node
	if (forest.size() == 1) {
		forest.push(new HCNode(0, 0));
	}

	// Construct Huffman tree 
	while (forest.size() > 1) {

		// create new internal node
		HCNode* parent = new HCNode(0, 0);
		
		// Set it's children to the top nodes in the forest
		
		// set right child
		parent->c0 = forest.top();
		parent->c0->p = parent;
		forest.pop();

		// set left child
		parent->c1 = forest.top();
		parent->c1->p = parent;
		forest.pop();

		// Set the internal node's count to the sum of it's childrens' count
		parent->count += (parent->c0->count + parent->c1->count);

		// Insert the node into the priority queue
		forest.push(parent);
		
	}
	root = forest.top();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
	
        // Find the leaf containing symbol
	HCNode* node = leaves[symbol];

        stack<int> code;
	
	// Get code by traversing from the leaf to the root,
	// storing each bit of the code on a stack
	while (node != root) {
		if (node->p->c0 == node)
		  code.push(0);
		else if (node->p->c1 == node)
		  code.push(1);
		node = node->p;
	}

	// Write the bits stored on the stack
	while (!code.empty()) {
	  out.writeBit(code.top());
	  code.pop();
	}
}

byte HCTree::decode(BitInputStream& in) const {
	HCNode* node = root;
	int bit;
	
	// Traverse from root to leaf by reading bits from the stream
	while (node->c0 || node->c1) {
		bit = in.readBit();
		if (bit == 1)
			node = node->c1;
		else if (bit == 0)
			node = node->c0;
		else
			return -1;
	}
	// Return the symbol stored in the leaf node
	return node->symbol;
}

/** Delete all nodes in the tree (used by destructor)
 */
void HCTree::clear(HCNode* node) {
	if (node) {
		clear(node->c1);
		clear(node->c0);
	}
	delete node;
}
