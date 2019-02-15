#ifndef NODE_H
#define NODE_H

template <typename T>
class Node{

private:
    //linkedlist has now access to the private variables in node class
    template <typename U> friend class LinkedList;
    //iterator class has now access to the private variables in node class
    template <typename V> friend class iteratorPtr;
    //variable that would be stored in node
    T data;
    //pointer to next node;
    Node* nextPtr;
    //pointer to previous node
    Node* previousPtr;
public:
    //Constructor for each node
    Node(T d, Node* previousPtr, Node* nextPtr);
    //Constructor for head doesnt contain any data
    Node(Node* prevPtr= nullptr, Node* nexPtr= nullptr);

};

template <typename T>
Node<T> :: Node(T d, Node* prevPtr, Node* nexPtr)
{
    data = d;
    previousPtr = prevPtr;
    nextPtr = nexPtr;
}

template <typename T>
//Parameters set to null were initiliazed on function prototypes
Node<T> :: Node(Node* prePtr, Node* nexPtr)
{
    previousPtr = prePtr;
    nextPtr = nexPtr;
}

#endif // NODE_H
