#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

 /** BST.hpp
  *  Author: Evan Carey (cs100vbg)
  */

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */
  virtual ~BST() {
	clear();
	delete root;
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */

  // INSTRUCTOR'S SAMPLE INSERT FUNCTION
  /*
  virtual std::pair<iterator,bool> insert(const Data& item) {
    if(nullptr == root) {  // empty tree, create new root
      root = new BSTNode<Data>(item);
      isize++;
      return std::pair<iterator,bool>(BSTIterator<Data>(root),true);
    } else {
      BSTNode<Data> *curr = root;
      while(1) {
        if(item < curr->data) {
          if(nullptr == curr->left) {
            curr->left = new BSTNode<Data>(item);
            curr->left->parent = curr;
            isize++;
            return std::pair<iterator,bool>(BSTIterator<Data>(curr->left),true);
          } else {
            curr = curr->left;
          }
        } else if(curr->data < item) {
          if(nullptr == curr->right) {
            curr->right = new BSTNode<Data>(item);
            curr->right->parent = curr;
            isize++;
            return std::pair<iterator,bool>(BSTIterator<Data>(curr->right),true);
          } else {
            curr = curr->right;
          }
        } else { // item == curr->data, already there
            return std::pair<iterator,bool>(BSTIterator<Data>(curr),false);
        }
      }
   }
}
*/
  
  virtual std::pair<iterator,bool> insert(const Data& item) {
      
	  BSTNode<Data>* node = 0;
	  if (root)
		  return recInsert(root, item);
	  else {
		  node = root = new BSTNode<Data>(item);
		  ++isize;
		  return std::pair<iterator, bool>(iterator(node), true);
	  }
  }
  
  

  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */
  iterator find(const Data& item) const {
	  BSTNode<Data>* node = NULL;
	  if (root != NULL)
		  node = recFind(root, item);

	  if (node)
		  return iterator(node);
	  else
		  return end();
  }

  
  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
	  return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */
  void clear() {
      if (root)
		  recClear(root);
	  root = NULL;
  }

  /** Return true if the BST is empty, else false.
   */
  bool empty() const {
      return isize == 0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */
  iterator begin() const {
	  if (empty())
		  return typename BST<Data>::iterator(NULL);
	  else {
		BSTNode<Data>* currentNode = root;
		while (currentNode->left) {
			currentNode = currentNode->left;
		}
		return typename BST<Data>::iterator(currentNode);
	  }
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  /** Print nodes in BST and size
   */
  void print() const {
	  std::cout << "--------------Size: " << size() << "---------------------" << std::endl;
	  if (root)
		  recPrint(root, 1);
	  std::cout << std::endl;
  }

private:
  /** Insert an item into the BST
   */
  std::pair<iterator, bool> recInsert(BSTNode<Data>* node, const Data& item) {
      if (item < node->data) {
		  if (node->left)
			  return recInsert(node->left, item);
		  else {
			  node->left = new BSTNode<Data>(item);
			  node->left->parent = node;
			  ++isize;
			  return std::pair<iterator, bool>(iterator(node->left), true);
		  }
	  } else if (node->data < item) {
		  if (node->right)
			  return recInsert(node->right, item);
		  else {
			  node->right = new BSTNode<Data>(item);
			  node->right->parent = node;
			  ++isize;
			  return std::pair<iterator, bool>(iterator(node->right), true);
		  }
	  } else {
		  return std::pair<iterator, bool>(iterator(node), false);
	  }
  }

  /** Find an item in the BST
   */
  BSTNode<Data>* recFind(BSTNode<Data>* node, const Data& item) const {

	  if (item < node->data) {
		  if (node->left)
			  return recFind(node->left, item);
		  else
			  return 0;
	  } else if (node->data < item) {
		  if (node->right)
			  return recFind(node->right, item);
		  else
			  return 0;
	  } else
		  return node;	
  }


  /** Delete all nodes in a given node's tree
   */
  void recClear(BSTNode<Data>* node) {
      if (node->left) {
		recClear(node->left);
      }
      if (node->right) {
		recClear(node->right);
      }
	  --isize;
      delete node;
  }

  /** Print nodes in BST
   */
  void recPrint(BSTNode<Data>* node, int level) const {
	  if (node->left)
		  recPrint(node->left, level+1);
	  std::cout << "Level " << level << "-  Data: " << node->data << "\t" << *node << std::endl;
	  if (node->right)
		  recPrint(node->right, level+1);
  }
};


#endif //BST_HPP
