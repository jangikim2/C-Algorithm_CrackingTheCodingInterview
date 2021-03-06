//
//  main.cpp
//  Chapter4_TreesAndGraphs
//
//  Created by JaeYoon Kim on 30/01/2017.
//  Copyright © 2017 JaeYoon Kim. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>s
#include <list>
using namespace std;

//http://www.bogotobogo.com/cplusplus/binarytree.php

enum State
{
    Unvisited, Visited, Visiting
};

typedef struct Tree
{
    char data;
    Tree *left;
    Tree *right;
    Tree *parent;
    State state;
} TREE;

TREE *newTreeNode(int data)
{
    TREE *node = new TREE;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    
    return node;
}

//void insertTreeNode(TREE *node, char ch)
struct Tree* insertTreeNode(TREE *node, int data)
{
    /*
    TREE *newNode = new TREE;
    newNode->data = ch;
    newNode->left = NULL;
    newNode->right = NULL;
    while(node) {
        if(ch <= node->data) {
            if(node->left == NULL) {
                newNode->parent = node;
                node->left = newNode;
                return;
            }
            else
                node = node->left;
        }
        else {
            if(node->right == NULL) {
                newNode->parent = node;
                node->right = newNode;
                return;
            }
            else
                node = node->right;
        }
    }
    */
    
    static Tree *p;
    Tree *retNode;
    
    //if(node != NULL) p = node;
    
    if(node == NULL)  {
        retNode = newTreeNode(data);
        retNode->parent = p;
        return retNode;
    }
    if(data <= node->data ) {
        p = node;
        node->left = insertTreeNode(node->left,data);
    }
    else {
        p = node;
        node->right = insertTreeNode(node->right,data);
    } 
    return node;
    
    
}

void isBST(struct Tree *node)
{
    static int lastData = INT_MIN;
    if(node == NULL) return;
    
    isBST(node->left);
    
    /* check if the given tree is BST */
    if(lastData < node->data)
        lastData = node->data;
    else {
        cout << "Not a BST" << endl;
        return;
    }
    
    isBST(node->right);
    return;
}

int treeSize(struct Tree *node)
{
    if(node == NULL) return 0;
    else
        return treeSize(node->left) + 1 + treeSize(node->right);
}




TREE *getNode(TREE *node, char c)
{
    if(node == NULL) return node;
    if(c < node->data)
        return getNode(node->left,c);
    else if( c > node->data)
        return getNode(node->right, c);
    else
        return node;
}

void printTreeInOrder(TREE *node)
{
    if(node == NULL) return;
    
    printTreeInOrder(node->left);
    cout  << (int)node->data  << "-";
    printTreeInOrder(node->right);
}

/* recursion routine to find path */
void pathFinder(struct Tree *node, int path[], int level, int mode)
{
    if(node == NULL) return;
    // save leaf node
    if(node->left == NULL && node->right == NULL) {
        path[level] = node->data;
        node->state = Unvisited;//jangikim
        for(int i = 0; i <= level; i++) {
            switch (mode) {
                case 0:
                    cout << (char)path[i];
                    break;
                case 1:
                    cout << path[i];
                default:
                    break;
            }
        }
        cout << endl;
        return;
    }
    // save parent node
    node->state = Unvisited;//jangikim
    path[level] = node->data;
    pathFinder(node->left, path, level+1, mode);
    pathFinder(node->right, path, level+1, mode);
}

Tree* lookUp(struct Tree *node, char key)
{
    if(node == NULL) return node;
    
    if(node->data == key)
        return node;
    else {
        if(node->data < key)
            return lookUp(node->right, key) ;
        else
            return lookUp(node->left, key);
    }
}

//4.1
int maxDepth(Tree *root) {
    //if(root == NULL)
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

int minDepth(Tree *root) {
    //if(root == NULL)
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

bool isBalanced(Tree *root) {
    return (maxDepth(root) - minDepth(root) <= 1);
}

//4.2

bool search(Tree *node, Tree *start, Tree *end)
{
    stack <Tree *> q;
    Tree *u;

    while(!q.empty())
    {
        q.top();
    }
    
    q.push(start);
    
    while (!q.empty()) {
        u = q.top();
        q.pop();
        if(u != NULL) {
            if (u->state == Unvisited) {
                if (u == end) {
                    cout << u->data << endl;
                    cout << "True in search return ..." << endl;
                    return true;
                } else {
                    u->state = Visiting;
                    if (u->left != NULL) {
                        q.push(u->left);
                    }
                    if (u->right != NULL) {
                        q.push(u->right);
                    }
                }
            }
            cout << u->data << endl;
            u->state = Visited;
        }
    }
    
    cout << "False in search return ..." << endl;
    
    return false;
}


//4.3
Tree * addToTree(int arr[], int start, int end){
    if(end < start) {
        return nullptr;
    }
    
    int mid = (start + end) / 2;
    Tree *n = newTreeNode(arr[mid]);
    n->left = addToTree(arr, start, mid - 1);
    n->right = addToTree(arr, mid+1, end);
    return n;
}

Tree * createMinimalBST(int array[], int size) {
    return addToTree(array, 0, size-1);
}

//4.4
/* get the level of a node element: root level = 0 */
int getLevel(struct Tree *node, int elm, int level)
{
    if(node == NULL) return 0;
    if(elm == node->data)
        return level;
    else if(elm < node->data)
        return getLevel(node->left, elm, level+1);
    else
        return getLevel(node->right, elm, level+1);
}

/* This code prints out all nodes at the same depth (level) */
void BreadthFirst_LevelElement_Print(struct Tree *root, vector<vector<int> > &v)
{
    if(root == NULL) return;
    deque<Tree *> q;
    q.push_back(root);
    while(!q.empty()) {
        Tree *p =  q.front();
        int lev = getLevel(root, p->data, 0);
        v[lev].push_back(p->data);
        q.pop_front();
        if(p->left) q.push_back(p->left);
        if(p->right)q.push_back(p->right);
    }
    return;
}

/* levelPrint()
 prints nodes at the same level
 This is simpler than the BreadthFirstTraversal(root) above
 It takes 2D vector with the same size of level (= MaxDepth+1)
 and fills elements as we traverse (preOrder) */

void levelPrint(struct Tree *node, vector<vector<char> >&elm, int level)
{
    if(node == NULL) return;
    // leaf nodes
    if(node->left == NULL && node->right == NULL) {
        elm[level].push_back(node->data);
        return;
    }
    // other nodes
    elm[level++].push_back(node->data);
    levelPrint(node->left, elm, level);
    levelPrint(node->right, elm, level);
}

//4.5
/* Tree Minimum */
Tree* minTree(struct Tree *node)
{
    if(node == NULL) return NULL;
    while(node->left)
        node = node -> left;
    return node;
}

/* In Order Successor - a node which has the next higher key */
Tree *succesorInOrder(struct Tree *node)
{
    /* if the node has right child, seccessor is Tree-Minimum */
    if(node->right != NULL) return minTree(node->right);
    
    Tree *y = node->parent;
    while(y != NULL && node == y->right) {
        node = y;
        y = y->parent;
    }
    return y;
}

//4.6
Tree *lowestCommonAncestor(Tree *node, Tree *p, Tree *q)
{
    Tree *left, *right;
    if(node == NULL) return NULL;
    if(node->left == p || node->left == q
       || node->right == p || node->right == q) return node;
    
    left = lowestCommonAncestor(node->left,p,q);
    right = lowestCommonAncestor(node->right, p,q);
    if(left && right)
        return node;
    else
        return (left) ? left : right;
}

//4.7

bool matchTree(Tree *r1, Tree *r2)
{
    /* Nothing left in the subtree */
    if(r1 == NULL && r2 == NULL)
        return true;
    /* Big tree empty and subtree not found */
    if(r1 == NULL || r2 == NULL)
        return false;
    /* Not matching */
    if(r1->data != r2->data)
        return false;
    return (matchTree(r1->left, r2->left) &&
            matchTree(r1->right, r2->right));
}

bool subTree(Tree *r1, Tree *r2)
{
    /*Big tree empty and subtree not found */
    if(r1 == NULL)
        return false;
    if(r1->data == r2->data)
        if(matchTree(r1, r2)) return true;
    return
    (subTree(r1->left, r2) || subTree(r1->right, r2));
}

bool isSubTree(Tree *r1, Tree *r2)
{
    /* Empty tree is subtree */
    if(r2 == NULL)
        return true;
    else
        return subTree(r1, r2);
}

//4.8
typedef struct Tree48
{
    int data;
    Tree48 *left;
    Tree48 *right;
} Node;

/* recursion routine to find path */
void pathFinder48(Node* node, int path[], int level)
{
    if(node == NULL) return;
    // leaf node save
    if(node->left == NULL && node->right == NULL) {
        path[level] = node->data;
        int sum = 0;
        for(int i = 0; i <= level; i++) {
            cout << path[i] << " ";
            sum += path[i];
        }
        cout << "  sum = " << sum << endl;
        return;
    }
    // parent node save
    path[level] = node->data;
    pathFinder48(node->left, path, level+1);
    pathFinder48(node->right, path, level+1);
}

struct Tree48* insertNode(Tree48 *node, int data)
{
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    char ch, ch1, ch2;
    Tree *found;
    Tree *succ;
	Tree *ancestor;
    
    std::cout << "Hello, World!\n";
    
    TREE *root = newTreeNode('F');
    insertTreeNode(root,'B');
    insertTreeNode(root,'A');
    insertTreeNode(root,'D');
    insertTreeNode(root,'C');
    insertTreeNode(root,'E');
    insertTreeNode(root,'G');
    insertTreeNode(root,'I');
    insertTreeNode(root,'H');
    
    /* is the tree BST? */
    isBST(root);
    
    /* size of tree */
    cout << "size = " << treeSize(root) << endl;
    
    //4.1
    /* max depth */
    cout << "max depth = " << maxDepth(root) << endl;
    
    /* min depth */
    cout << "min depth = " << minDepth(root) << endl;
    
    /* balanced tree? */
    if(isBalanced(root))
        cout << "This tree is balanced!\n";
    else
        cout << "This tree is not balanced!\n";
    
    /* printing all paths :
     Given a binary tree, print out all of its root-to-leaf
     paths, one per line. Uses a recursive helper to do the work. */
    cout << "printing paths ..." << endl;
    int path[10];
    
    //4.2
    pathFinder(root, path, 0, 0);//Initialize state of tree into 'Unvisited'
    //Test1 condition
    //ch1 = 'F';
    //ch2 = 'D';
    //Test2 condition
    ch1 = 'B';
    ch2 = 'E';
    //Test3 condition
    //ch1 = 'E';
    //ch2 = 'E';
    search(root, lookUp(root,ch1), lookUp(root,ch2));
    
    //4.3 This is the same as the solution of bogotobogo.com.
    int array1[ 10 ] = {1,2,3,4,5,6,7,8,9,10};
    int sizeArray1 = sizeof(array1)/sizeof(*array1);
    Tree *root1 = createMinimalBST(array1, sizeArray1);
    
    cout << "Tree start" << "\n";
    printTreeInOrder(root1);
    cout << "\n" << "Tree end" << "\n";
    
    /* max depth */
    cout << "max depth = " << maxDepth(root1) << endl;
    int path1[10];
    pathFinder(root1, path1, 0, 1);//Initialize state of tree into 'Unvisited'
    
    //4.4 This is the same as the solution of bogotobogo.com.
    /* Prints all element at the same depth (level) */
    int row = maxDepth(root);
    vector<vector<int> > levVec(row+1);
    BreadthFirst_LevelElement_Print(root, levVec);
    for(int m = 0; m < levVec.size(); m++) {
        cout << "Level at " << m << ": ";
        for(int n = 0; n < levVec[m].size(); n++)
            cout << (char)levVec[m][n] << " ";
        cout << endl;
    }
    
    /* levelPrint()
     prints nodes at the same level
     This is simpler than the BreadthFirstTraversal(root) above
     It takes 2D vector (elm) with the same size of level (= MaxDepth+1)
     and fills elements as we traverse (preOrder) */
    vector<vector<char> > elm;
    int mxDepth = maxDepth(root);
    elm.resize(mxDepth+1);
    int level = 0;
    levelPrint(root, elm, level);
    cout << "levelPrint() " << endl;
    for(int i = 0; i <= mxDepth; i++) {
        cout << "level " << i << ": " ;
        for(int j = 0; j < elm[i].size(); j++)
            cout << elm[i][j] << " ";
        cout << endl;
    }
    
    //4.5 This is the same as the solution of bogotobogo.com.
    ch = 'B';
    found = lookUp(root,ch);
    if(found) {
        succ = succesorInOrder(found);
        if(succ)
            cout << "In Order Successor of " << ch << " is "
            << succesorInOrder(found)->data << endl;
        else
            cout << "In Order Successor of " << ch << " is None\n";
    }
    
    ch = 'E';
    found = lookUp(root,ch);
    if(found) {
        succ = succesorInOrder(found);
        if(succ)
            cout << "In Order Successor of " << ch << " is "
            << succesorInOrder(found)->data << endl;
        else 
            cout << "In Order Successor of " << ch << " is None\n";
    }
    
    ch = 'I';
    found = lookUp(root,ch);
    if(found) {
        succ = succesorInOrder(found);
        if(succ)
            cout << "In Order Successor of " << ch << " is "
            << succesorInOrder(found)->data << endl;
        else
            cout << "In Order Successor of " << ch << " is None\n";
    }
    
    //4.6 This is the same as the solution of bogotobogo.com.
    /* Lowest Common Ancestor */
    ch1 = 'A';
    ch2 = 'C';
    ancestor =
    lowestCommonAncestor(root,
                         lookUp(root,ch1), lookUp(root,ch2));
    if(ancestor)
        cout << "The lowest common ancestor of " << ch1 << " and "
        << ch2 << " is " << ancestor->data << endl;
    
    ch1 = 'E';
    ch2 = 'H';
    ancestor =
    lowestCommonAncestor(root,
                         lookUp(root,ch1), lookUp(root,ch2));
    if(ancestor)
        cout << "The lowest common ancestor of " << ch1 << " and "
        << ch2 << " is " << ancestor->data << endl;

    ch1 = 'D';
    ch2 = 'E';
    ancestor =
    lowestCommonAncestor(root,
                         lookUp(root,ch1), lookUp(root,ch2));
    if(ancestor)
        cout << "The lowest common ancestor of " << ch1 << " and "
        << ch2 << " is " << ancestor->data << endl;
    
    ch1 = 'G';
    ch2 = 'I';
    ancestor =
    lowestCommonAncestor(root,
                         lookUp(root,ch1), lookUp(root,ch2));
    if(ancestor)
        cout << "The lowest common ancestor of " << ch1 << " and "
        << ch2 << " is " << ancestor->data << endl;

    
    ch1 = 'H';
    ch2 = 'I';
    ancestor =
    lowestCommonAncestor(root,
                         lookUp(root,ch1), lookUp(root,ch2));
    if(ancestor)
        cout << "The lowest common ancestor of " << ch1 << " and "
        << ch2 << " is " << ancestor->data << endl;
    
    //4.7 This is the same as the solution of bogotobogo.com.
    /* subtree */
    Tree *root2 = newTreeNode('D');
    insertTreeNode(root2,'C');
    insertTreeNode(root2,'E');
    cout << "1-2 subtree: " << isSubTree(root, root2) << endl;
    
    Tree *root3 = newTreeNode('B');
    insertTreeNode(root3,'A');
    insertTreeNode(root3,'D');
    insertTreeNode(root3,'C');
    insertTreeNode(root3,'E');
    cout << "1-3 subtree: " << isSubTree(root, root3) << endl;
    
    Tree *root4 = newTreeNode('B');
    insertTreeNode(root4,'D');
    insertTreeNode(root4,'C');
    insertTreeNode(root4,'E');
    cout << "1-4 subtree: " << isSubTree(root, root4) << endl;
    
    cout << "2-3 subtree: " << isSubTree(root2, root3) << endl;
    cout << "3-2 subtree: " << isSubTree(root3, root2) << endl;

    //4.8 This is the same as the solution of bogotobogo.com.
    {
        Tree48 *root = NULL;
        Tree48 *nodeLeft = NULL;
        Tree48 *nodeRight = NULL;
        
        /*       3
                / \
              -1   2
              / \  /
             5   7 1
         */
        // unsorted binary tree
        // root
        root = insertNode(new Tree48, 3);
        
        // 1st level
        nodeLeft = insertNode(new Tree48, -1);
        root->left = nodeLeft;
        nodeRight = insertNode(new Tree48, 2);
        root->right = nodeRight;
        
        // 2nd level
        nodeLeft->left = insertNode(new Tree48, 5);
        nodeLeft->right = insertNode(new Tree48, 7);
        nodeRight->left = insertNode(new Tree48, 1);
        
        // path find
        int path[10];
        pathFinder48(root,path,0);
    }
    
    
    return 0;
}

/* output */
/*
 Hello, World!
 size = 9
 max depth = 3
 min depth = 2
 This tree is balanced!
 printing paths ...
 FBA
 FBDC
 FBDE
 FGIH
 B
 D
 E
 True in search return ...
 Tree start
 1-2-3-4-5-6-7-8-9-10-
 Tree end
 max depth = 3
 521
 5234
 5867
 58910
 Level at 0: F
 Level at 1: B G
 Level at 2: A D I
 Level at 3: C E H
 levelPrint()
 level 0: F
 level 1: B G
 level 2: A D I
 level 3: C E H
 In Order Successor of B is C
 In Order Successor of E is F
 In Order Successor of I is None
 The lowest common ancestor of A and C is B
 The lowest common ancestor of E and H is F
 The lowest common ancestor of D and E is B
 The lowest common ancestor of G and I is F
 The lowest common ancestor of H and I is G
 1-2 subtree: 1
 1-3 subtree: 1
 1-4 subtree: 0
 2-3 subtree: 0
 3-2 subtree: 1
 3 -1 5   sum = 7
 3 -1 7   sum = 9
 3 2 1   sum = 6
 Program ended with exit code: 0
*/