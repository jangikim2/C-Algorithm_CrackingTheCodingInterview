//
//  main.cpp
//  Chapter2_LinkedLists
//
//  Created by JaeYoon Kim on 23/01/2017.
//  Copyright © 2017 JaeYoon Kim. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

class Node;
void deleteDups2(Node *head);
int nthToLast(list<int> head, int n);
Node * addLists(Node *l1, Node *l2, int carry);
Node * FindBeginning(Node *head);


//http://code.runnable.com/Us53QO5op1hWAACi/how-to-remove-a-node-from-a-linked-list-for-c%2B%2B
/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int _value; /* data, can be any data type, but use integer for easiness */
    Node *_pNext; /* pointer to the next node */
    
public:
    /* Constructors with No Arguments */
    Node(void)
    : _pNext(nullptr)
    { }
    
    /* Constructors with a given value */
    Node(int val)
    : _value(val), _pNext(nullptr)
    { }
    
    /* Constructors with a given value and a link of the next node */
    Node(int val, Node* next)
    : _value(val), _pNext(next)
    {}
    
    /* Getters */
    int getValue(void)
    { return _value; }
    
    Node* getNext(void)
    { return _pNext; }
    
    //jangikim
    /* Setters */
    void setValue(int val)
    {
        _value = val;
    }
    
    void setNext(Node* next)
    {
        _pNext = next;
    }
    
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *_pHead;
    /* pointer of tail node */
    Node *_pTail;
    
public:
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);
    
    /* Function to append a node to the end of a linked list */
    void tailAppend(int val);
    
    /* Remove a node with a specific value if it exists */
    void remove(int val);
    
    /* Function to delete all the elements of a linked list */
    void clear();
    
    /* Traversing the list and printing the value of each node */
    void traverse_and_print();
};

LinkedList::LinkedList(int val)
{
    /* Create a new node, acting as both the head and tail node */
    _pHead = new Node(val);
    _pTail = _pHead;
}

LinkedList::~LinkedList()
{
    /*
     * Leave it empty temporarily.
     * It will be described in detail in the example "How to delete a linkedlist".
     */
}

void LinkedList::tailAppend(int val)
{
    /* The list is empty? */
    if (_pHead == nullptr) {
        /* the same to create a new list with a given value */
        _pTail = _pHead = new Node(val);
    }
    else
    {
        /* Append the new node to the tail */
        _pTail->_pNext = new Node(val);
        /* Update the tail pointer */
        _pTail = _pTail->_pNext;
    }
}

void LinkedList::remove(int val)
{
    Node *pPre = nullptr, *pDel = nullptr;
    
    /* Check whether it is the head node?
     if it is, delete and update the head node */
    if (_pHead->_value == val) {
        /* point to the node to be deleted */
        pDel = _pHead;
        /* update */
        _pHead = pDel->_pNext;
        delete pDel;
        return;
    }
    
    pPre = _pHead;
    pDel = _pHead->_pNext;
    
    /* traverse the list and check the value of each node */
    while (pDel != nullptr) {
        if (pDel->_value == val) {
            /* Update the list */
            pPre->_pNext = pDel->_pNext;
            /* If it is the last node, update the tail */
            if (pDel == _pTail) {
                _pTail = pPre;
            }
            delete pDel; /* Here only remove the first node with the given value */
            break; /* break and return */
        }
        pPre = pDel;
        pDel = pDel->_pNext;
    }
}

void LinkedList::clear()
{
    Node *pDel = _pHead;
    
    /* Traverse the list and delete the node one by one from the head */
    while (pDel != NULL) {
        /* take out the head node */
        _pHead = _pHead->_pNext;
        delete pDel;
        /* update the head node */
        pDel = _pHead;
    }
    /* Reset the head and tail node */
    _pTail = _pHead = NULL;
}

void LinkedList::traverse_and_print()
{
    Node *p = _pHead;
    
    /* The list is empty? */
    if (_pHead == nullptr) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    /* A basic way of traversing a linked list */
    while (p != nullptr) { /* while there are some more nodes left */
        /* output the value */
        cout << p->_value << " ";
        /* The pointer moves along to the next one */
        p = p->_pNext;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //2.1
    Node *A1 = new Node(5);
    Node *B1 = new Node(3);
    Node *C1 = new Node(5);
    Node *D1 = new Node(3);
    Node *E1 = new Node(5);
    Node *F1 = new Node(1);
    
    A1->setNext(B1);
    B1->setNext(C1);
    C1->setNext(D1);
    D1->setNext(E1);
    E1->setNext(F1);
    
    deleteDups2(A1);
    
    //2.2
    std::list<int> testlist{1,2,3,4,5,6};
    int nthint = 0;
    nthint = nthToLast(testlist,1);
    
    /* Create a list with only one node */
    //LinkedList list(1);
    /* Append 3 nodes to the end of the list */
    //list.tailAppend(2);
    //list.tailAppend(3);
    //list.tailAppend(4);
    //cout << "Before removing: " << endl;
    /* output the result */
    //list.traverse_and_print();
    
    /* Remode the node with value 3 */
    //cout << "Trying to remove the node with value 3" << endl;
    //list.remove(3);
    /* output the result */
    //cout << "After removing: " << endl;
    //list.traverse_and_print();
    
    //2.4
    Node *node1 = new Node(3, new Node(1, new Node(5, nullptr)));
    Node *node2 = new Node(5, new Node(9, new Node(2, nullptr)));
    
    Node *finalresult = addLists(node1, node2, 0);
    
    //Take advantage of the above 'void LinkedList::clear()' in order to clean finalresult
    {
        /* pointer of head node */
        Node *_pHead = finalresult;
        Node *pDel = _pHead;
        /* Traverse the list and delete the node one by one from the head */
        while (pDel != nullptr) {
            /* take out the head node */
            //_pHead = _pHead->_pNext;
            _pHead = _pHead->getNext();
            delete pDel;
            /* update the head node */
            pDel = _pHead;
        }
        /* Reset the head and tail node */
        //_pTail = _pHead = NULL;
        _pHead = nullptr;
    }
    
    //2.5
    Node *A = new Node(1);
    Node *B = new Node(2);
    Node *C = new Node(3);
    Node *D = new Node(4);
    Node *E = new Node(5);
    
    A->setNext(B);
    B->setNext(C);
    C->setNext(D);
    D->setNext(E);
    E->setNext(C);
    
    Node *beginningreturn = FindBeginning(A);
    
    return 0;
}

//2.1
void deleteDups2(Node *head)
{
    if (head == nullptr) {
        return;
    }
    
    Node *previous = head;
    Node *current = previous->getNext();
    while (current != nullptr) {
        Node * runner = head;
        while (runner != current) {
            if (runner->getValue() == current->getValue()) {
                Node *tmp = current->getNext();
                previous->setNext(tmp);
                delete current;//jangikim
                current = tmp;
                break;
            }
            runner = runner->getNext();
        }
        if (runner == current) {
            previous = current;
            current = current->getNext();
        }
    }
}

//2.2
int nthToLast(list<int> head, int n) {
     if(head.empty() || n < 1) {
        return {};
    }

    list<int>::iterator it1;
    list<int>::iterator it2;
    
    it1 = head.begin();
    it2 = head.begin();
    
    for (int j = 0; j < n; ++j) {
        if(it2 == head.end()) {
            return {};
        }
        it2++;
    }

    while(it2 != head.end()) {
        it2++;
        it1++;
    }
    return *it1;
}

//2.3
//skipped because of 'void LinkedList::remove(int val)'

//2.4
Node * addLists(Node *l1, Node *l2, int carry)
{
    if(l1 == nullptr && l2 == nullptr) {
        return nullptr;
    }
    
    Node *result = new Node(carry);
    int value = carry;
    if(l1 != nullptr) {
        value += l1->getValue();
    }
    if(l2 != nullptr) {
        value += l2->getValue();
    }
    result->setValue(value % 10);
    
    Node * more = addLists(l1 == nullptr? nullptr : l1->getNext(),
                         l2 == nullptr? nullptr : l2->getNext(),
                         value >= 10? 1: 0);

    result->setNext(more);
    return result;
}

//2.5
Node * FindBeginning(Node *head) {
    Node *n1 = head;
    Node *n2 = head;
    
    while (n2->getNext() != nullptr) {
        n1 = n1->getNext();
        n2 = n2->getNext()->getNext();
        if (n1 == n2) {
            break;
        }
    }
    
    if (n2->getNext() == nullptr) {
        return nullptr;
    }
    
    n1 = head;
    while (n1 != n2) {
        n1 = n1->getNext();
        n2 = n2->getNext();
    }
    return n2;
}
