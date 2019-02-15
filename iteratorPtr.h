#ifndef ITERATORPTR_H
#define ITERATORPTR_H
#include <node.h>
#include <stdexcept>

template <typename T>
class iteratorPtr
{
public:
    iteratorPtr(Node<T>* beginingOfList = nullptr);
    iteratorPtr<T> & operator=(const Node<T>& rightObj);
    T & operator*();//derefence operator to retun data in Node
    iteratorPtr operator++(int);//post-fix operator
    bool operator!=(const iteratorPtr<T>& rightObj);
private:
    //this pointer will iterate through each node
    Node<T>* current;
};

template <typename T>
iteratorPtr<T> :: iteratorPtr(Node<T>* beginingOfList)
{
    //this is null unless initialized
    current = beginingOfList;
}

template <typename T>
iteratorPtr<T> & iteratorPtr<T>:: operator=(const Node<T>& rightObj)
{
    this->current = rightObj->current;
}

template <typename T>
T &iteratorPtr<T>  :: operator*()//derefence operator to retun data in Node
{
    //check if the ptr is null
    if(current == nullptr)
        throw std::out_of_range("Error trying to derefence a null pointer. Inside operator*.");
    //this will return the data inside of the node where the pointer points to.
    return current->data;
}

template <typename T>
iteratorPtr<T> iteratorPtr<T>:: operator++(int )//prefix operator
{
    //creating a temp obj passing in where current points too
    iteratorPtr<T> nodePtr(current);
    //updating current
    current = current ->nextPtr;

    //return copy of the object (where current previously pointed)
    return nodePtr;
}

template <typename T>
bool iteratorPtr<T>:: operator!=(const iteratorPtr<T>& rightObj)
{
    //returns bool
    return current != rightObj.current;
}

#endif // ITERATORPTR_H
