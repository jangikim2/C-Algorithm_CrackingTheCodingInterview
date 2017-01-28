//
//  main.cpp
//  Chapter3_StacksAndQueues
//
//  Created by JaeYoon Kim on 26/01/2017.
//  Copyright © 2017 JaeYoon Kim. All rights reserved.
//

#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std;

//3.1.1
#define stackSizeD 10

int stackSize = stackSizeD;//jangikim
int buffer[stackSizeD * 3] = {0,};
int stackPointer[3] = {0,};

//3.1.2
int indexUsed = 0;
int stackPointer2[3] = {-1,-1,-1};

class StackNode {
public:
    int previous;
    int value;
public:
    
    StackNode() = default;//jangikim
    StackNode(int p, int v){
        value = v;
        previous = p;
    }
};

StackNode buffer2[stackSizeD * 3];
void push2(int stackNum, int value){
    int lastIndex  = stackPointer2[stackNum];
    stackPointer2[stackNum] = indexUsed;
    indexUsed++;
    buffer2[stackPointer2[stackNum]] = StackNode(lastIndex, value);
}


int pop2(int stackNum) {
    int value = buffer2[stackPointer2[stackNum]].value;
    int lastIndex = stackPointer2[stackNum];
    stackPointer2[stackNum] = buffer2[stackPointer2[stackNum]].previous;
    buffer2[lastIndex].previous = 0;//jangikim
    buffer2[lastIndex].value = 0;//jangikim
    indexUsed--;//This causes a bug in terms of assiging a new item to the buffer
    return value;
}

int peek2(int stack) {return buffer2[stackPointer2[stack]].value;}
bool isEmpty2(int stackNum) {return stackPointer2[stackNum] == -1;}

//3.1.1
void push(int stackNum, int value) {
    int index = stackNum * stackSize + stackPointer[stackNum] + 1;
    stackPointer[stackNum]++;
    buffer[index] = value;
}

int pop(int stackNum) {
    int index = stackNum * stackSize + stackPointer[stackNum];
    stackPointer[stackNum]--;
    int value = buffer[index];
    buffer[index] = 0;
    return value;
}

int peek(int stackNum) {
    int index  = stackNum * stackSize + stackPointer[stackNum];
    return buffer[index];
}

bool isEmpty(int stackNum) {
    return stackPointer[stackNum] == stackNum*stackSize;
}

//3.2.1

class NodeWithMin {
public:
    int value;
    int min;
public:
    NodeWithMin(int v, int min){
        value = v;
        this->min = min;
    }
};

class StackWithMin: public stack<NodeWithMin>{
public:
    void push(int value) {
        int newMin = std::min(value, min());
        stack<NodeWithMin>::push(NodeWithMin(value, newMin));//jangikim
    }
    
    //jangikim
    int min() {
        if (this->empty()) {
            return INT_MAX;
        } else {
            NodeWithMin tmp = this->top();
            return tmp.min;
        }
    }
    
};

//3.2.2
//jangikim
class StackWithMin2 : public stack<int>{
private:
    stack<int> * s2;
public:
    StackWithMin2() {
        s2 = new stack<int>();
    }
    
    void push(int value) {
        if(value <= min()) {
            s2->push(value);
        }
        stack<int>::push(value);
    }
    
    int pop(){
        int value = stack<int>::top();//jangikim
        stack<int>::pop();//jangikim
        
        if(value == min()) {
            s2->pop();
        }
        return value;
    }
    
    int min(){
        if(s2->empty()){
            return INT_MAX;
        } else {
            return s2->top();
        }
        
    }
    
    
};

//3.3
class Node {
public:
    Node *above;
    Node *below;
    int value;
    
    Node(int value) {
        this->value = value;
    }
};

class Stack {
private:
    int capacity;
public:
    Node *top, *bottom;
    int size = 0;
    
    Stack(int capacity) {
        this->capacity = capacity;
    }
    bool isAtCapacity() {
        return capacity == size;
    }
    
    void join(Node *above, Node *below) {
        if(below != nullptr) below->above = above;
        if(above != nullptr) above->below = below;
    }
    
    bool push(int v) {
        if(size >= capacity) return false;
        size++;
        Node *n = new Node(v);
        if(size == 1) bottom = n;
        join(n, top);
        top = n;
        return true;
    }
    
    int pop() {
        Node *t = top;
        top = top->below;
        size--;
        return t->value;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    int removeBottom() {
        Node *b = bottom;
        bottom = bottom->above;
        if(bottom != nullptr) bottom->below = nullptr;
        size--;
        return b->value;
    }
};

class SetOfStacks {
private:
    vector<Stack *> *stacks = new vector<Stack *>();
public:
    int capacity;
    SetOfStacks(int capacity) {
        this->capacity = capacity;
    }
    
    Stack *getLastStack() {
        if(stacks->size() == 0) return NULL;
        return stacks->at(stacks->size() - 1);
    }
    
    void push(int v) {
        Stack *last = getLastStack();
        if(last != nullptr && !last->isAtCapacity()) {
            last->push(v);
        } else {
            Stack *stack = new Stack(capacity);
            stack->push(v);
            stacks->push_back(stack);
        }
    }
    
    int pop() {
        Stack *last = getLastStack();
        int v = last->pop();
        if(last->isEmpty() == 0) stacks->erase(stacks->end()-1);//jangikim
        return v;
    }
    
    int popAt(int index) {
        return leftShift(index , true);
    }
    
    int leftShift(int index, bool removeTop) {
        Stack *stack = stacks->at(index);
        int removed_item;
        if (removeTop) removed_item = stack->pop();
        else removed_item = stack->removeBottom();
        if (stack->isEmpty()) {
            stacks->erase(stacks->begin() + index);
        } else if(stacks->size() > index + 1) {
            int v = leftShift(index + 1, false);
            stack->push(v);
        }
        return removed_item;
    }
};

//3.5
template <typename T>
class MyQueue {
private:
    std::stack<T> *s1, *s2;
public:
    MyQueue() {
        s1 = new std::stack<T>();
        s2 = new std::stack<T>();
    }
    
    int size() {
        return s1->size() + s2->size();
    }
    
    void add(T value) {
        s1->push(value);
    }
    
    T peek() {
        if (!s2->empty()) return s2->top();
        while (!s1->empty())
        {
            s2->push(s1->top());
            s1->pop();
        }
        return s2->top();
    }
    
    T remove() {
        int top;
        if (!s2->empty())
        {
            top = s2->top();
            s2->pop();
            return top;
        }
        while (!s1->empty())
        {
            s2->push(s1->top());
            s1->pop();
        }
        
        top = s2->top();
        s2->pop();
        return top;
    }
};

//3.6
std::stack<int> * sort(stack<int> *s) {
    std::stack<int> *r = new stack<int>();
    while (!s->empty()) {
        int tmp = s->top();
        s->pop();
        while (!r->empty() && r->top() > tmp) {
            s->push(r->top());
            r->pop();
        }
        r->push(tmp);
    }
    return r;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //3.1.1
    push(0, 123);
    push(1, 234);
    push(2, 345);
    push(0, 124);
    push(1, 235);
    push(2, 346);
    
    int popint = pop(0);
    popint = pop(1);
    popint = pop(2);
    
    int peekint = peek(0);
    peekint = peek(1);
    peekint = peek(2);
    
    if(isEmpty(0))
        std::cout << "Stack, Empty!\n";
    else
        std::cout << "Stack, not Empty!\n";
    
    //3.1.2
    push2(0,1);//0
    push2(0,2);//1
    push2(0,3);//2
    push2(0,4);//3
    push2(1,11);//4
    push2(1,12);//5
    push2(1,13);//6
    push2(1,14);//7
    push2(0,5);//8
    push2(0,6);//9
    push2(1,15);//10
    push2(1,16);//11
    push2(2,21);//12
    push2(2,22);//13
    push2(1,17);//14
    push2(1,18);//15
    
    int popint2 = pop2(0);//9
    popint2 = pop2(1);//15
    popint2 = pop2(2);//13
    
    push2(0,7);
    push2(1,19);//A index bug happens!!!
    push2(2,23);
    
    int peekint2 = peek2(0);
    if(isEmpty(2))
        std::cout << "Stack2, Empty!\n";
    else
        std::cout << "Stack2, not Empty!\n";
    
    //3.2.1
    StackWithMin mintest;
    int minimum = mintest.min();
    mintest.push(10);
    minimum = mintest.min();
    mintest.push(9);
    minimum = mintest.min();
    mintest.push(19);
    minimum = mintest.min();
    
    //3.2.2
    StackWithMin2 mintest2;
    mintest2.push(5);
    mintest2.push(2);
    mintest2.push(7);
    mintest2.push(9);
    int minimum2 = mintest2.min();
    int poptest = mintest2.pop();
    
    //3.3
    SetOfStacks test(3);
    test.push(1);
    test.push(2);
    test.push(3);
 
    test.push(4);
    int testpop = test.pop();
    test.push(5);
    test.push(6);
    test.push(7);
    test.push(8);
    
    int popatint = test.popAt(0);
    
    return 0;
}