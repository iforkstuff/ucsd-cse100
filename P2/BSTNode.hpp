#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
#include <cstdlib>

 /** BSTNode.hpp
  *  Author: Evan Carey (cs100vbg)
  */


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
	//Set info for RSTNode
	info = rand();
  }

  ~BSTNode() {
  }

  /** Return info member variable
   */
  int getPriority() const {
	  return info;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */
  BSTNode<Data>* successor() {
	BSTNode<Data>* currNode = this;
    // If node has a right subtree, return left-most leaf of that subtree
    if (currNode->right != nullptr) {
      currNode = currNode->right;
      while (currNode->left != nullptr) {
		currNode = currNode->left;
      }
      return currNode;
	// Otherwise, iterate up parents nodes until one is the left child and return its parent
    } else if (this->parent != nullptr) {
      BSTNode<Data>* parentNode = this->parent;
      while (parentNode != nullptr && currNode != parentNode->left) {
		currNode = parentNode;
		parentNode = parentNode->parent;
      }
      return parentNode;
    }
    // No inorder successor
    return nullptr;
  }

}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
