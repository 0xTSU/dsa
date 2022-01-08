/// @brief Assignment 5
/// Header file for Binary Search Tree
#ifndef BINTREE_H_
#define BINTREE_H_

#include <iostream>
#include <vector>

// node
struct visibilityType
{
	int id;
	bool camera;
	bool seen;
	
	bool operator==(int x)
	{
		return id == x;
	}

};

// binary tree class
template <typename type>
class binTree
{
	struct binTreeNode
	{
		type data;
		binTreeNode * left;
		binTreeNode * right;
	};
	
public:

	class binTreeIterator
	{
	public:
	
		friend class binTree;
		binTreeIterator();
		binTreeIterator(binTreeNode*);
		binTreeIterator leftChild() const;
		binTreeIterator rightChild() const;
		type& operator*() const;
		bool operator==(const binTreeIterator&) const;
		bool operator!=(const binTreeIterator&) const;

	private:
	
		binTreeNode* binTreeNodePointer;
	
	};
	
	binTree();
	binTree(const binTree<type>&);
	const binTree& operator=(const binTree<type>&);
	~binTree();
	
	void buildTree(std::vector<type>);
	binTreeIterator rootIterator() const;
	
private:

	void destroyTree(binTreeNode*);
	void copyTree(binTreeNode*, binTreeNode*);
	void buildTree(std::vector<type>, binTreeNode *, int);
	
	binTreeNode * root;
};
