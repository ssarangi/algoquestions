/*
Problem Statement
    	
Balanced binary search trees are among the most studied data structures in computer science. However, implementing them can be rather tricky. Most designs of balanced binary search trees are based on the same four basic transformations--left single rotations, right single rotations, left double rotations, and right double rotations--but differ in exactly when and where these transformations are applied.

Red-black trees are one of the most popular kinds of balanced binary search trees. In a red-black tree, every node is colored either red or black, and no red node is allowed to have a red parent. In addition, every path from the root to a leaf contains the same number of black nodes. Most books on data structures contain a description of how to maintain the red-black properties, based on the usual four rotations. In this problem, we will consider a simpler scheme for maintaining red-black trees, based on a single transformation, called a twist.

Inserting a new key into a red-black tree proceeds in two phases: a search phase followed by a rebalancing phase. In the search phase, you start at the root and walk down the tree, going left when the new key is smaller than the key at the current node and going right when the new key is larger than the key at the current node. (You may assume the new key will not be equal to the key at the current node.) When the search reaches the bottom of the tree, the new key is added as a new child of the last node in the search path, on the left or right, as appropriate. The new node is always a leaf and is always colored red.

If the new node's parent is also red, then we now have a violation of the rule that no red node may have a red parent. The job of the rebalancing phase is to detect such situations, and to correct them using a transformation called a twist. A twist involves the red node, its red parent, and its black grandparent. There are four possible configurations for these three nodes, shown below:

     (Blk) z         (Blk) z               x (Blk)         x (Blk)
          / \             / \             / \             / \
   (Red) y   T4    (Red) x   T4         T1   z (Red)    T1   y (Red)
        / \             / \                 / \             / \
 (Red) x   T3         T1   y (Red)   (Red) y   T4         T2   z (Red)
      / \                 / \             / \                 / \
    T1   T2             T2   T3         T2   T3             T3   T4
where T1, T2, T3, and T4 are subtrees (possibly empty). All four configurations are rewritten to exactly the same shape:
                             (Red) y
                                  / \
                                 /   \
                          (Blk) x     z (Blk)
                               / \   / \
                              T1 T2 T3 T4  
After the twist, y's parent may be red, so the process continues until there are no more positions where a twist can be applied. Note that there will never be more than one red node with a red parent at the same time.
There is one last case to worry about. It is possible to have a red node with a red parent, but with no grandparent because the parent is the root. A twist cannot be applied without the grandparent, so to protect against this case, we color the root black at the end of every insert.

Given a sequence of numbers to be inserted one at a time into an initially empty red-black tree, your task is to determine the total number of twists that occur during the inserts.

As an example, consider the steps involved in inserting the numbers {1,2,3}. Initially the tree is empty, so when we insert the 1 node, it becomes the new root. The new node starts out red, but, because it is the root, it is recolored black at the end of the insert. The tree now looks like

            1 (Blk)
When we insert the 2 node, it goes on the right. The new node is colored red.
            1 (Blk)
             \
              2 (Red)
When we insert the 3 node, it again goes on the right and is colored red.
            1 (Blk)
             \
              2 (Red)
               \
                3 (Red)
The new node starts out red, but it has a red parent, so a twist is necessary. After the twist, the tree looks like
            2 (Red)
           / \
    (Blk) 1   3 (Blk)
However, the root is recolored black at the end of every insert, so the final tree is
            2 (Blk)
           / \
    (Blk) 1   3 (Blk)
Altogether, this series of inserts requires 1 twist, so your method should return 1.
 
Definition
    	
Class:	RedBlack
Method:	numTwists
Parameters:	int[]
Returns:	int
Method signature:	int numTwists(int[] keys)
(be sure your method is public)
    
 
Constraints
-	keys contains between 1 and 50 elements, inclusive.
-	keys is a permutation of the numbers between 1 and n, inclusive, where n is the length of keys.
 
Examples
0)	
    	
{ 1,2,3 }
Returns: 1
The example above.
1)	
    	
{ 1,2,3,4,5,6,7 }
Returns: 4
One twist happens when we insert the 3, and another happens when we insert the 5, leaving
            2 (Blk)
           / \
    (Blk) 1   4 (Red)
             / \
      (Blk) 3   5 (Blk)
When we insert the 7, we initially get
            2 (Blk)
           / \
    (Blk) 1   4 (Red)
             / \
      (Blk) 3   5 (Blk)
                 \
                  6 (Red)
                   \
                    7 (Red)
but the 7 node has a red parent, so we do a twist
            2 (Blk)
           / \
    (Blk) 1   4 (Red)
             / \
      (Blk) 3   6 (Red)
               / \
        (Blk) 5   7 (Blk)
Now, the 6 node has a red parent, so we do another twist.
            4 (Red)
           / \
          /   \
   (Blk) 2     6 (Blk)
        / \   / \
       1   3 5   7   <--- all four leaves are black
At the end of the insert, we recolor the root black.
            4 (Blk)
           / \
          /   \
   (Blk) 2     6 (Blk)
        / \   / \
       1   3 5   7   <--- all four leaves are black
Altogether, 4 twists were required.
2)	
    	
{ 7,1,4,6,3,5,2 }
Returns: 3
3)	
    	
{ 5,10,15,14,3,4,11,2,1,12,6,9,7,13,8 }
Returns: 11
4)	
    	
{ 6,8,10,12,4,2,18,14,16,19,7,15,9,17,13,5,11,3,1 }
Returns: 5

    Single Round Match 155 Round 1 - Division I, Level Three
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <assert.h>

using namespace std;

enum Color
{
    RED,
    BLACK
};

template <typename T>
struct Node
{
    T data;
    Node* parent;
    Node* leftChild;
    Node* rightChild;

    Color color;

    // Color every new Node RED by default. A twist might then happen
    // after that
    Node(Node* p, T val) : parent(p), color(RED), data(val), leftChild(NULL), rightChild(NULL) { }
    Node(const Node& n)
    {
        data = n.data;
        parent = n.parent;
        leftChild = n.leftChild;
        rightChild = n.rightChild;
    }

    Node(const Node* n)
    {
        data = n->data;
        parent = n->parent;
        leftChild = n->leftChild;
        rightChild = n->rightChild;
    }
};

template <typename T>
void checkTree(Node<T>* node, Node<T>* parent)
{
    // Verify all the info is correct.
    if (node == NULL)
        return;

    assert(node->parent == parent);
    
    if (node->leftChild != NULL)
    {
        assert(node->leftChild->data < node->data);
        checkTree(node->leftChild, node);
    }

    if (node->rightChild != NULL)
    {
        assert(node->rightChild->data > node->data);
        checkTree(node->rightChild, node);
    }
}

template <typename T>
int addNode(Node<T>* &root, T val)
{
    int twistNeeded = 0;
    bool leftChild = false;

    Node<T>* node = root;

    // Find a leaf node
    Node<T>* tparent;
    while (node != NULL)
    {
        tparent = node;

        if (val > node->data)
            node = node->rightChild;
        else
            node = node->leftChild;
    }

    node = tparent;

    Node<T>* newNode = new Node<T>(node, val);
    newNode->parent = node;

    if (newNode->data > node->data)
    {
        node->rightChild = newNode;
    }
    else
    {
        node->leftChild = newNode;
        leftChild = true;
    }

    if (node == root)
    {
        checkTree<int>(root, NULL);
        return twistNeeded;
    }

/*
       (1)              (2)               (3)             (4)
    (Blk) z         (Blk) z               x (Blk)         x (Blk)
          / \             / \             / \             / \
   (Red) y   T4    (Red) x   T4         T1   z (Red)    T1   y (Red)
        / \             / \                 / \             / \
 (Red) x   T3         T1   y (Red)   (Red) y   T4         T2   z (Red)
      / \                 / \             / \                 / \
    T1   T2             T2   T3         T2   T3             T3   T4

*/
    while (node != NULL && node->parent != NULL && node->parent->color == BLACK && node->color == RED && newNode->color == RED)
    {
        Node<T>* parent = node->parent;
        Node<T>* grandParent = node->parent->parent;
        Node<T>* newlocalroot = NULL;

        // A Twist is required since the node to be added is also red.
        // Case 1
        if (parent->leftChild == node && node->leftChild == newNode)
        {
            newlocalroot = new Node<T>(node->parent, node->data);
            newlocalroot->leftChild = newNode;
            newlocalroot->rightChild = parent;

            // Now set the children's children
            newlocalroot->leftChild->leftChild = newNode->leftChild;
            newlocalroot->leftChild->rightChild = newNode->rightChild;
            newlocalroot->rightChild->leftChild = node->rightChild;
            newlocalroot->rightChild->rightChild = parent->rightChild;
        }
        // Case 2
        else if (parent->leftChild == node && node->rightChild == newNode)
        {
            newlocalroot = new Node<T>(newNode->parent, newNode->data);
            newlocalroot->leftChild = node;
            newlocalroot->rightChild = parent;

            // Now set the children's children
            newlocalroot->leftChild->leftChild = node->leftChild;
            newlocalroot->leftChild->rightChild = newNode->leftChild;
            newlocalroot->rightChild->leftChild = newNode->rightChild;
            newlocalroot->rightChild->rightChild = parent->rightChild;
        }
        // Case 3
        else if (parent->rightChild == node && node->leftChild == newNode)
        {
            newlocalroot = new Node<T>(newNode->parent, newNode->data);
            newlocalroot->leftChild = parent;
            newlocalroot->rightChild = node;

            // Now set the children's children
            newlocalroot->leftChild->leftChild = parent->leftChild;
            newlocalroot->leftChild->rightChild = newNode->leftChild;
            newlocalroot->rightChild->leftChild = newNode->rightChild;
            newlocalroot->rightChild->rightChild = node->rightChild;
        }
        // Case 4
        else if (parent->rightChild == node && node->rightChild == newNode)
        {
            newlocalroot = new Node<T>(node->parent, node->data);
            newlocalroot->leftChild = parent;
            newlocalroot->rightChild = newNode;

            // Now set the children's children
            newlocalroot->leftChild->leftChild = parent->leftChild;
            newlocalroot->leftChild->rightChild = node->leftChild;
            newlocalroot->rightChild->leftChild = newNode->leftChild;
            newlocalroot->rightChild->rightChild = newNode->rightChild;
        }

        // Assign the parent
        newlocalroot->leftChild->parent = newlocalroot->rightChild->parent = newlocalroot;

        // Set the parents for the leftChild's & rightChild's children
        if (newlocalroot->leftChild->leftChild != NULL)
            newlocalroot->leftChild->leftChild->parent   = newlocalroot->leftChild;

        if (newlocalroot->leftChild->rightChild != NULL)
            newlocalroot->leftChild->rightChild->parent  = newlocalroot->leftChild;

        if (newlocalroot->rightChild->leftChild != NULL)
            newlocalroot->rightChild->leftChild->parent  = newlocalroot->rightChild;

        if (newlocalroot->rightChild->rightChild != NULL)
            newlocalroot->rightChild->rightChild->parent = newlocalroot->rightChild;


        // Assign Colors to the left child & right child
        newlocalroot->leftChild->color = newlocalroot->rightChild->color = BLACK;

        newlocalroot->parent = grandParent;

        // If parent is not the root, then it will have a parent too.
        if (grandParent != NULL)
        {
            if (grandParent->leftChild->data == parent->data)
                grandParent->leftChild = newlocalroot;
            else
                grandParent->rightChild = newlocalroot;
        }
        else
        {
            // Root has now changed. So reassign the new root
            root = newlocalroot;
        }

        // Now change the node to look for
        node = newlocalroot->parent;
        newNode = newlocalroot;

        twistNeeded += 1;

        checkTree<int>(root, NULL);
    }

    // Color the root Black
    root->color = BLACK;

    checkTree<int>(root, NULL);

    return twistNeeded;
}

class RedBlack 
{
public:
	int numTwists(vector <int> keys) 
    {
        int twistNeeded = 0;

        // This is the root node. So color is Black.
        Node<int>* root = new Node<int>(NULL, keys[0]);
        root->color = BLACK;
        
        for (unsigned int i = 1; i < keys.size(); i++)
        {
            cout << "Current value: " << keys[i] << endl;
            twistNeeded += addNode<int>(root, keys[i]); 
        }

        return twistNeeded;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, bool hasAnswer, int p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}";
	cout << "]" << endl;
	RedBlack *obj;
	int answer;
	obj = new RedBlack();
	clock_t startTime = clock();
	answer = obj->numTwists(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p1 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p1;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	vector <int> p0;
	int p1;
	
	{
	// ----- test 0 -----
	int t0[] = {1,2,3};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {1,2,3,4,5,6,7};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 4;
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {7,1,4,6,3,5,2};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3;
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {5,10,15,14,3,4,11,2,1,12,6,9,7,13,8};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 11;
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	int t0[] = {6,8,10,12,4,2,18,14,16,19,7,15,9,17,13,5,11,3,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 5;
	all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}

    system("pause");
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
