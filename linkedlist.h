#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <node.h>
#include <iteratorPtr.h>

using namespace std;

template <typename T>
class LinkedList
{
public:

    LinkedList();
    LinkedList(const LinkedList<T>& t);
    ~LinkedList();
    LinkedList<T> & operator=(const LinkedList<T>& rightObj);
    T & operator[](const int index);
    //THESE OVERLOADED OPERATORS ARE ONLY USED TO COMPARE THE SIZE OF LISTS AND NOT VALUES WITHIN LISTS!
    void copyLL(const LinkedList<T>& rightLL);
    void clearLL();
    int getNumOfElements();//elements inside vector
    bool empty();//check if ll is empty
    void insertBack(T d);
    T removeBack();
    void displayList();
    bool find(T d);
    Node<T>* getHead();

private:
    //iterator class has now access to the private variables in node class
    template <typename V> friend class iteratorPtr;
    Node<T>* head;
    Node<T>* tail;
    Node<T>* iterator;
    int NumOfElements;
    bool isEmpty;
    void insertBack(Node<T>* temp);
};

//default constructor
template <typename T>
LinkedList<T> :: LinkedList()
{
    //initializing empty list
    head = nullptr;
    tail= nullptr;
    iterator = nullptr;
    NumOfElements = 0;
    isEmpty = true;
}

template <typename T>//copy constructor
LinkedList<T> :: LinkedList(const LinkedList<T>& rightHandSideObj)
{
    /*example Obj a; //rightHandSideObj
              Obj b(a);// b is this obj
    */
    //copying private variables from LL
    this->NumOfElements = rightHandSideObj.NumOfElements;
    this->isEmpty = rightHandSideObj.isEmpty;
    //Everything from rightHandSideObj is now copied into this obj.
    copyLL(rightHandSideObj);
}

template <typename T>
LinkedList<T>  :: ~LinkedList()
{
    //call the clear linked list function to delete all dynamic memory.
    clearLL();
}

template<typename T>
LinkedList<T> &LinkedList<T> :: operator=(const LinkedList<T>& rightHandSideObj)
{

    //checking if we are copying the same object
    if(this == &rightHandSideObj){
        return *this;
    }
    /*example Obj a;
              Obj b;
              b = a;
    */
    //deleting previously delclared private data and nodes from this LL.In this case everything in b will be deleted.
    clearLL();
    //copying private variables from LL
    this->NumOfElements = rightHandSideObj.NumOfElements;
    this->isEmpty = rightHandSideObj.isEmpty;
    //now we copy everything from right object to left.
    copyLL(rightHandSideObj);

    return *this;
}

template<typename T>
T &LinkedList<T> :: operator[](const int index)
{
    int tempIndex = index;
    //check if head is null
    if(head == nullptr || index >= NumOfElements || index < 0)
        throw std::out_of_range("Trying to access empty list or going out of bounds. Inside operator[] function.");
    //check if index is 0,if it is return the data head points to
    if(index == 0)
        return head->data;
    else//check if the index is last element
    if(index == NumOfElements-1)
        return tail->data;
    else{
        //create a ptr that begins in head and iterate through the ll
        Node<T>* iteratorSubscript = head;
        //iterate through end of list or the index is found
        while(iteratorSubscript != nullptr && tempIndex > 0){
            //moving to the next node
            iteratorSubscript = iteratorSubscript->nextPtr;
            //decreasing the counter
            tempIndex--;
        }
        //the ptr shoud be pointing to the correct node, so we return the data inside the node
        return  iteratorSubscript->data;
    }
}

template <typename T>
void LinkedList<T> :: copyLL(const LinkedList<T>& rightHandSideObj)
{
    //checking if the Linked List is empty
    if(rightHandSideObj.head == nullptr){
        //Initializing lhs private data to an empty list
        this->head == nullptr;
        this->tail == nullptr;
    }else{
        //creating a templated temp variable to get the head
        T getHeadData = rightHandSideObj.head->data;
        //creating a new node that head will point to with the templated data type
        /*
          [nullptr |t | nullptr]

          this head / this tail /leftHandSideNode
          NOTE: if we point this head to rightHandSide head this is shallow copy.
        */
        //all of these pointers point to the same node
        Node<T>* leftHandSideNode = this->tail = this->head = new Node<T>(getHeadData, nullptr, nullptr);
        //This pointer will point to the LL that is being copied.
        Node<T>* Iterator = rightHandSideObj.head;
        //Moving to next element in ll. If there is none it wont go into while loop.
        Iterator = Iterator->nextPtr;
        //iterating through the ll and copying every node from rightHandSide to this obj
        while(Iterator != nullptr){
            //creating a templated temp variable to get the data from ll
            T getRightObjData = Iterator->data;
            /*
              [nullptr |t | nullptr]
              tempNode
            */
            Node<T>* tempNode = new Node<T>(getRightObjData, nullptr, nullptr);
            /*
              [nullptr |t | nullptr]  <-[tail |t | nullptr]
              head / tail               tempNode
            */
            tempNode->previousPtr = this->tail;
            /*
              [nullptr |t | tempNode]-> <-[tail |t | nullptr]
              head / tail               tempNode
            */
            this->tail->nextPtr = tempNode;
            /*
              [nullptr |t | tempNode]-> <-[tail |t | nullptr]
              head                       tempNode / tail
            */
            this->tail = tempNode;
            //Moving to next element in ll. If there is none it wont go into while loop.
            Iterator = Iterator->nextPtr;
        }
    }
}

template <typename T>
void LinkedList<T> :: clearLL()
{
    //checking if the linked list is empty, if it is we dont do anything.
    if(head == nullptr)
        return;
    //creating a temp node called current
    Node<T>* currentNode = head;
    //iterating through the LL
    while(currentNode->nextPtr != nullptr){
        //temp node equal to the the node after current
        Node<T>* afterCurrentNode = currentNode->nextPtr;
        //deleting current Node
        delete currentNode;
        //currentnode points to next node
        currentNode = afterCurrentNode;
        //
        NumOfElements--;
    }
    //deleting the last node in linke
    delete currentNode;
    //
    NumOfElements--;
    //making sure head and tail do not point to anything
    tail = head = nullptr;
    //updating empty flag
    isEmpty = true;
}

template <typename T>
int LinkedList<T> :: getNumOfElements()
{
    //return the number of elements in linkedlist
    return NumOfElements;
}

template <typename T>
void LinkedList<T> :: insertBack(T t)
{
    /*
      [nullptr |t | nullptr]
      tempNode
    */
    Node<T>* temp = new Node<T>(t, nullptr, nullptr);
    //calling private function
    insertBack(temp);
}

template <typename T>
void LinkedList<T> :: insertBack(Node<T>* tempNode)
{
    //checking if we are adding first element in LL
    if(head == nullptr){
        /*
          [nullptr |t | nullptr]
          tempNode / head / tail point here
        */
        head = tempNode;
        tail = tempNode;
        isEmpty = false;
    }else{
    //There is more than 1 Node<T>* LinkedList<T> :: getIterator()item on LL
        /*
          [nullptr |t | nullptr]  <-[tail |t | nullptr]
          head / tail               tempNode
        */
        tempNode->previousPtr = tail;
        /*
          [nullptr |t | tempNode]-> <-[tail |t | nullptr]
          head / tail               tempNode
        */
        tail->nextPtr = tempNode;
        /*
          [nullptr |t | tempNode]-> <-[tail |t | nullptr]
          head                       tempNode / tail
        */
        tail = tempNode;
    }
    //increase the number of elements
    NumOfElements++;
}

template <typename T>
T LinkedList<T> :: removeBack()
{
    if(NumOfElements == 0)
        throw std::out_of_range("Error trying to delete from empty list, inside rmBack.");
    //creating a temp value if no exception
    T dataInsideNode;
    //checking if there is only one element in list
    if(NumOfElements == 1){
        /*
          [nullptr |t | nullptr]
        rmNodePtr / head / tail points here only when numOfE ==1
        */
        //create a node ptr and set equal to head, because head/tail point to the same node
        Node<T>* removeNodePtr = head;
        //getting templated value from node
        dataInsideNode = removeNodePtr->data;
        //delete the dynamic memory rmNodeptr points to
        delete removeNodePtr;
        //set head and tail to nullptr
        head = tail= nullptr;
        isEmpty = true;

    }else{
        /*
               [pos tail -2 |t | tail]->  <-[pos tail-1 |t | pos2]
               position tail-1              tail/removeNodePtr
        */
        //create a node ptr that points to tail
        Node<T>* removeNodePtr = tail;
        //getting templated value from node
        dataInsideNode = removeNodePtr->data;
        /*
               [pos tail -2 |t | nullptr]  <-[pos tail-1 |t | pos2]
               position tail-1              tail/removeNodePtr
        */
        //making the nextPtr in the previous node before tail point to null
        tail->previousPtr->nextPtr = nullptr;
        /*
               [pos tail -2 |t | nullptr]  <-[pos tail-1 |t | pos2]
               tail                           removeNodePtr
        */
        //moving tail to point to previous node
        tail = tail->previousPtr;
        /*
               [pos tail -2 |t | nullptr]  [nullptr|t | pos2]
               tail                         removeNodePtr
        */
        //removeNodeptr doesnt point anyhwere now
        removeNodePtr->previousPtr = nullptr;
        /*
               [pos tail -2 |t | nullptr]
               tail
        */
        //removeNodeptr is now deleted
        delete removeNodePtr;
    }
    //decrease list
    NumOfElements--;

    //returing templated value that was inside of the deleted node
    return dataInsideNode;
}

template <typename T>
bool LinkedList<T> :: empty()
{
    //this flag will change depending on the items on the linked list
    return isEmpty;
}

template <typename T>
void LinkedList<T> :: displayList()
{
    Node<T>* curr = head;

    if(curr == nullptr){
        cout << "\nThe list is empty." <<endl;
        return;
    }

    while (curr != nullptr){
        if(curr == head)
            cout << "Head: ";
        else
        if(curr == tail)
            cout << "Tail: ";
        cout << curr->data << endl;
        curr = curr->nextPtr;
    }
}

template <typename T>
bool LinkedList<T> :: find(T d)
{
    //Temprorary Node pointer
    Node<T>* temp;
    //This for loop will initialize the ptr to head
    //it will iterate through the LL until last element
    for(temp = head; temp != nullptr; temp = temp->nextPtr){
        //check if the value is found
        if(temp->data == d){
            return true;
        }
    }
 return false;
}

template <typename T>
Node<T>* LinkedList<T> :: getHead()
{
    //checking if head is null
    if(head == nullptr){
        throw std::out_of_range("Error trying to get nullptr. Inside getHead.");
    }

    return head;
}


#endif // LINKEDLIST_H
