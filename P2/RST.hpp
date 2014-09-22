#ifndef RST_HPP
#define RST_HPP
#include "BSTNode.hpp"
#include "countint.hpp"
#include "BST.hpp"

 /** RST.hpp
  *  Author: Evan Carey (cs100vbg)
  */
template<typename Data>
class RST : public BST<Data> {

  private:
  	
  	/**
  	* left rotate around node
  	*/
	void leftRotate(BSTNode<Data>* node)
	{
		BSTNode<Data>* temp = node->right;
		temp->parent = node->parent;
		if (temp->parent) {
			if (temp->parent->left == node)
				temp->parent->left = temp;
			else
				temp->parent->right = temp;
		}
		node->right = temp->left;
		if (node->right)
			node->right->parent = node;
		node->parent = temp;
		temp->left = node;
		if (node == BST<Data>::root) {
			BST<Data>::root = temp;
			BST<Data>::root->parent = NULL;
		}
	}
	
	/**
  	* right rotate around node
  	*/
	void rightRotate(BSTNode<Data>* node)
	{
		BSTNode<Data>* temp = node->left;
		temp->parent = node->parent;
		if (temp->parent) {
			if (temp->parent->left == node)
				temp->parent->left = temp;
			else
				temp->parent->right = temp;
		}
		node->left = temp->right;
		if (node->left)
			node->left->parent = node;
		node->parent = temp;
		temp->right = node;
		if (node == BST<Data>::root) {
			BST<Data>::root = temp;
			BST<Data>::root->parent = NULL;
		}
	}

	void repair(BSTNode<Data>* newNode) {

		while (newNode->parent && newNode->parent->info < newNode->info) {
			if (newNode->parent->right == newNode)
				leftRotate(newNode->parent);
			else
				rightRotate(newNode->parent);
		}
		if (newNode->parent == NULL)
			BST<Data>::root = newNode;
	}

    
public:

	/** Constructor */
	RST() {}

	/** Destructor */
	~RST() {}

	/** Insert a new node and, if successful, repair tree.
	 */
	virtual std::pair<typename BST<Data>::iterator,bool> insert(const Data& item) {

		std::pair<typename BST<Data>::iterator,bool> p = BST<Data>::insert(item);
		if (p.second) {
			repair(p.first.curr);
		}
		return p;
	}
	
};
#endif // RST_HPP