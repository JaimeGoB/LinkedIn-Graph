#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <node.h>
#include <linkedlist.h>

using namespace std;

template <typename T>
class Stack{

public:
    Stack();
    void push(T d);
    T pop();
    T peek();//last element in stack
    bool isEmpty();
    bool find(T d);
    int getNumOfElements();

private:
    //creating a list ptr
    LinkedList<T> LLStack;
};

//default constructor
template <typename T>
Stack<T> :: Stack()
{

}

//adding items on the stack
template <typename T>
void Stack<T> :: push(T d)
{
    //inserting in the back
    LLStack.insertBack(d);
}

//stack is LIFO type therefore all the items deleted are from the back.
template <typename T>
T Stack<T> :: pop()
{
    //checking if ll is empty
    if(LLStack.empty())
        throw out_of_range("Error trying to pop from empty stack, inside pop function.");
    //remove from list and return templated value
    return LLStack.removeBack();
}

//getting the last element added on stack
template <typename T>
T Stack<T> :: peek()
{
    if(LLStack.empty())
        throw std::out_of_range("Error trying to peek from empty stack or out of bounds, inside peek function.");

    return LLStack[LLStack.getNumOfElements()-1];
}

//getter to check if stack is empty
template <typename T>
bool Stack<T> :: isEmpty()
{
    return LLStack.empty();
}

//getter to check the number of elements in stack
template <typename T>
int Stack<T> :: getNumOfElements()
{
    return LLStack.getNumOfElements();
}

template <typename T>
bool Stack<T> :: find(T d)
{
    return LLStack.find(d);
}

#endif // STACK_H
