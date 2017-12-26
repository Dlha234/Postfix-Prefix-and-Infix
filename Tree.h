// Delbert Harrison
// Program 4
// Sec 001
// Tree.h

#ifndef TREE_H
#define TREE_H

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class TreeNode // Basic tree structure
{
private:
	string key;
	TreeNode *left, *right;
public:
	TreeNode(string k) {key = k; left = right = NULL;}
	friend class Tree;
};

const string PLUS = "+";
const string MINUS = "-";
const string MULTIPLY = "*";
const string DIVIDE = "/";
const string OPENBRACE = "(";
const string CLOSEBRACE = ")";
const int FORMAT_WIDTH = 3;  // It is for the display of a tree structure: the width of each operand

class Tree
{
private:
	TreeNode* root;				// points to the root of the tree
	void prefix(TreeNode* node);
	string postfix(TreeNode* node);
	void infix(TreeNode* node);

public:
	Tree();			//constructor
        Tree(string key);
	~Tree();			//destructor
        void buildTree(string E);
        TreeNode* build(vector<string> E, int left, int right);
        int getHeight();
        void printTree();               // show the tree in a figure
        void prefix(); // Add the notations
        string postfix();
        void infix();
        long evaluateByPostfix();

	// ------------------------------------------
        void destroy(TreeNode* T);
        int height(TreeNode* T);
};


#endif	/* TREE_H */
