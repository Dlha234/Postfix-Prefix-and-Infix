// Delbert Harrison
// Program 4
// Sec 001
// Tree.cpp

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>
#include <string>
#include "Tree.h"
using namespace std;

int findPlusMinus(vector<string> E, int left, int right) // Finding + and -
{
    int parenCnt = 0, loc = right;
    while(loc >= left)
    {
        if(E[loc] == ")")
        {
            parenCnt++ ;
        }
        else
        {
            if(E[loc] == "(")
            {
                parenCnt-- ;
            }
            else
            {
                if(E[loc] == "+" || E[loc] == "-")
                {
                    if (parenCnt == 0)
                    {
                        return loc;
                    }
                }
            }
        }
        loc--;
    }
    return -1 ;
}

int findMulDiv(vector<string> E, int left, int right) // Finding * and /
{
    int parenCnt = 0, loc = right;
    while(loc >= left)
    {
        if(E[loc] == ")") parenCnt++ ;
        else
            if(E[loc] == "(") parenCnt-- ;
            else
            if(E[loc] == "*" || E[loc] == "/")
                if (parenCnt == 0)      return loc;
        loc--;
    }
    return -1 ;
}

Tree::Tree()
{
	root = NULL;
}

Tree::Tree(string key)
{
    buildTree(key);
}

// recursive function to delete(free) tree node
// starting from the node pointed by T
void Tree::destroy(TreeNode* T)
{
	if  (T != NULL)
	{
		destroy(T->left) ;
		destroy(T->right) ;

		delete  T ;
	}
}

// destructor
// by calling destory function to free each node of the tree
// starting from the root node
Tree::~Tree()
{
	destroy(root);
}

// calculate the height of tree (tree levels)
// an empty tree has zero height
// The height of the tree is the number of nodes at the longest path
// from the root node to the leaf node
int Tree::height(TreeNode* T)
{
        int hh = 0;
        int lh, rh;
        if (T == NULL) return hh;
        if ((T->left == NULL) && (T->right == NULL)) return (hh++);
        lh = height(T->left);
        rh = height(T->right);
        if (lh >= rh)
            hh = lh + 1;
        else
            hh = rh + 1;
        return hh;
}

// return the height of the parse tree
int Tree::getHeight()
{
    if (root == NULL)
        return 0;
    else
        return (height(root));
}

// To push back the strings into vectors for main
void Tree::buildTree(string E)
{
    vector<string> EVec;

    while(E.find(' ') != string::npos)//while this is not the last element
    {
        EVec.push_back(E.substr(0, E.find(' ')));
        E = E.substr(E.find(' ') + 1, E.length());
    }

    EVec.push_back(E);//add last element

    root = build(EVec, 0, EVec.size()-1);
}

// to build the parse tree from an infix expression
TreeNode* Tree::build(vector<string> E, int left, int right)
{

    if (left == right) //a single operand
        return (new TreeNode(E[left]));
    TreeNode *T;
    int loc = findPlusMinus(E, left, right);
    if(loc != -1)
        {
            if(E[loc] == "+")
                T = new TreeNode("+");
            else
                T = new TreeNode("-");
            T->left = build(E, left, loc-1);
            T->right = build(E, loc+1, right);
            return T;
        }
        loc = findMulDiv(E, left, right);
        if(loc != -1)
        {
            if(E[loc] == "*")
                T = new TreeNode("*");
            else
                T = new TreeNode("/");
            T->left = build(E, left, loc-1);
            T->right = build(E, loc+1, right);
            return T;
        }
        return build(E, left+1, right-1); //parentheses eliminated
}


// display the parse tree strcture visually
void Tree::printTree()
{
        queue<TreeNode*> nodes;
        queue<int> levelList;
        TreeNode* current = NULL;
        int printDepth = this->getHeight();
        int possibleNodes = static_cast<int>(pow(2.0, printDepth + 1));
        int countNodes = 0;

        nodes.push(root);
        int currentLevel = 0;
        int previousLevel = -1;
        levelList.push(currentLevel);

        while (countNodes < possibleNodes)
        {
            countNodes = countNodes + 1;
            if (!nodes.empty())
            {
                current = nodes.front();
                nodes.pop();
            }
            if (!levelList.empty())
            {
                currentLevel = levelList.front();
                levelList.pop();
            }
            if (currentLevel > previousLevel)
            {
                cout << endl << endl;
                previousLevel = currentLevel;
                for (int j = 0; j < int ((pow(2.0, (printDepth - currentLevel))) - 1); j++)
                    cout << setw(FORMAT_WIDTH)<< " ";
            }
            else
            {
                for (int i = 0; i < int ((pow(2.0, (printDepth - currentLevel + 1)) - 1)) ; i++)
                {
                    cout << setw(FORMAT_WIDTH) <<" ";
                }
            }
            if (current != NULL)
            {
                cout << setw(FORMAT_WIDTH) << current->key;
                nodes.push(current->left);
                levelList.push(currentLevel + 1);
                nodes.push(current->right);
                levelList.push(currentLevel + 1);
            }
            else {
                nodes.push(NULL);
                levelList.push(currentLevel + 1);
                nodes.push(NULL);
                levelList.push(currentLevel + 1);
                cout << setw(FORMAT_WIDTH) << " ";
            }

        }
}

void Tree::prefix() // We need to label the root in each expression in
                    // order to traverse through the expression
{
    prefix(root);
}

void Tree::prefix(TreeNode* node) // For prefix notation
{
    if(node == NULL)
        return;

    cout << node->key << " ";
    prefix(node->left);
    prefix(node->right);
}

string Tree::postfix()
{
    return postfix(root);
}

string Tree::postfix(TreeNode* node) // For postfix notation
{
    if(node == NULL)
        return "";

    return postfix(node->left) + postfix(node-> right) + node->key + " ";
}

void Tree::infix()
{
    infix(root);
}
void Tree::infix(TreeNode* node) // Infix notation
{
    if(node == NULL)
        return;

    if(node->key == "+" || node->key == "-" || node->key == "/" || node->key == "*") //Adding the extra parentheses
        cout << "( ";

    infix(node->left);
    cout << node->key << " ";
    infix(node-> right);

    if(node->key == "+" || node->key == "-" || node->key == "/" || node->key == "*")
        cout << " ) ";
}

long Tree::evaluateByPostfix()
{
    string line = postfix();
    stack<string> stack;

    vector<string> v;
    while(line.find(' ') != string::npos)//while this is not the last element
    {
        v.push_back(line.substr(0, line.find(' ')));
        line = line.substr(line.find(' ') + 1, line.length());
    }

    v.push_back(line);//add last element

    for(unsigned int i = 0; i < v.size(); i++)
    {
        if(strtol(v[i].c_str(), NULL, 10) != 0L)
            stack.push(v[i]);
        else
        {
            long num1 = strtol(stack.top().c_str(), NULL, 10);
            stack.pop();
            long num2 = strtol(stack.top().c_str(), NULL, 10);
            stack.pop();
            long result;
            if(v[i] == "+")
                result = num1 + num2;
            else if(v[i] == "-")
                result = num1 - num2;
            else if(v[i] == "*")
                result = num1 * num2;
            else
                result = num1 / num2;

            //string temp = to_string(result, 10);
            //stack.push(temp);
        }
    }

    return strtol(stack.top().c_str(), NULL, 10);
}
