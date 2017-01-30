//
//  main.cpp
//  Chapter4_TreesAndGraphs
//
//  Created by JaeYoon Kim on 30/01/2017.
//  Copyright © 2017 JaeYoon Kim. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;

//http://www.bogotobogo.com/cplusplus/binarytree.php
typedef struct Tree
{
    char data;
    Tree *left;
    Tree *right;
    Tree *parent;
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

void insertTreeNode(TREE *node, char ch)
{
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
//4.1
int maxDepth(Tree *root) {
    if (root == nullptr ) {
        return 0;
    }
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

int minDepth(Tree *root) {
    if (root == nullptr ) {
        return 0;
    }
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

bool isBalanced(Tree *root) {
    return (maxDepth(root) - minDepth(root) <= 1);
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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //4.1
    TREE *root = newTreeNode('F');
    insertTreeNode(root,'B');
    insertTreeNode(root,'A');
    insertTreeNode(root,'D');
    insertTreeNode(root,'C');
    insertTreeNode(root,'E');
    insertTreeNode(root,'G');
    insertTreeNode(root,'I');
    insertTreeNode(root,'H');
    
    int maxDepthInt = maxDepth(root);
    int minDepthInt = minDepth(root);
    bool isBalancedInt = isBalanced(root);
    
    
    //4.3
    int array1[ 10 ] = {1,2,3,4,5,6,7,8,9,10};
    int sizeArray1 = sizeof(array1)/sizeof(*array1);
    Tree *root1 = createMinimalBST(array1, sizeArray1);
    
    cout << "Tree start" << "\n";
    printTreeInOrder(root1);
    cout << "\n" << "Tree end" << "\n";
    
    return 0;
}
