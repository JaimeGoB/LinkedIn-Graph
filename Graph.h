#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
#include <node.h>
#include <linkedlist.h>
#include <stack.h>
#include <stdexcept>

using namespace std;
template <typename T>
class Graph{

public:
    Graph();
    LinkedList<T> & operator[](int index);
    int findVertex(T anyType);
    void addVertex(T anyType);
    int checkConnections(int index, T anyType);
    void addConnections(int index, T anyType);
    void addEdge(T firstEdgeType,T secondEdgeType);
    int getVertices();
    int getConnections(int index);
    void displayGraph();

private:
    LinkedList<LinkedList<T> > AdjencyLinkedInList;
    int numberOfVertices;
};

//default constructor
template <typename T>
Graph<T> :: Graph()
{
    //initializing the number of vertices to 0
    numberOfVertices = 0;
}

template <typename T>
LinkedList<T> &Graph<T> :: operator[](int index)
{
    if(numberOfVertices == 0 || index >= numberOfVertices)
        throw std::out_of_range("Going out of bounds inside [] operator A-List.");
    //return linked list inside linked list of linked lists
    return AdjencyLinkedInList[index];
}

template <typename T>
int Graph<T> :: findVertex(T anyType)
{
    //checking if list not empty
    if(numberOfVertices != 0){
        //loop through all vertices
        for(int a = 0; a < numberOfVertices; a++){
            //comparing every vertex in a-list to the one that will be added.
            if(AdjencyLinkedInList[a][0] == anyType){
                //we will not add if it already exists
                return a;
            }
        }
    }
    //vertex is not found
    return -1;
}

//This function will check if a certain connection already exists (used in addEdge)
template <typename T>
int Graph<T> :: checkConnections(int index, T anyType)
{
    //creating temp value
    int sizeOfThisLL = AdjencyLinkedInList[index].getNumOfElements();
    //checking if list not empty
    if(sizeOfThisLL > 0){
        //loop through all vertices in this specific ll
        for(int d = 0; d < sizeOfThisLL; d++){
            //comparing neighbors at current index, d is will be neighbors inside linked list
            if(AdjencyLinkedInList[index][d] == anyType){
                //return index of the connection
                return d;
            }
        }
    }
    //connection is not found
    return -1;
}

template <typename T>
void Graph<T> :: addConnections(int index, T anyType)
{
    /*
        adjecnyList:
        [0] is first linkedlist, in this list we will insert the connection for this person
        [1] is second linkedlist
        ...
    */
    //insert template parameter inside the index of the linked list
    AdjencyLinkedInList[index].insertBack(anyType);
}

//this just addes a vertex to graph
template <typename T>
void Graph<T> :: addVertex(T anyType)
{
    //creating temp ll obj
    LinkedList<T> TempList;
    //adding the first element as vertex
    TempList.insertBack(anyType);
    //add vertex to a-list
    AdjencyLinkedInList.insertBack(TempList);
    //increase vertices counter
    numberOfVertices++;
}

//this function will connect two vertices, it checks if they exist if they donot they will be created
template <typename T>
void Graph<T> :: addEdge(T firstVertexType,T secondVertexType)
{
    //creating temp value to get index of template parameters
    int tempIndexFirst = findVertex(firstVertexType);
    //checking if first vertix exists, -1 means it doesnt
    if(tempIndexFirst == -1){
        //add vertex
        addVertex(firstVertexType);
        //now we look for the index again and store it
        tempIndexFirst = findVertex(firstVertexType);
        //check if second exists in first, checkConnect will return -1 if it doesnt
        if(checkConnections(tempIndexFirst, secondVertexType) == -1 ){
            //add connection
            addConnections(tempIndexFirst, secondVertexType);
        }
    }else{//first is a vertix
        //check if second exists in first, checkConnect will return -1 if it doesnt
        if(checkConnections(tempIndexFirst, secondVertexType) == -1 ){
            //add connection
            addConnections(tempIndexFirst, secondVertexType);
        }
    }

    //creating temp value to get index of template parameters
    int tempIndexSecond = findVertex(secondVertexType);
    if(tempIndexSecond == -1){
        //add vertex
        addVertex(secondVertexType);
        //now we look for the index again and store it
        tempIndexSecond = findVertex(secondVertexType);
        //check if first exists in second, checkConnect will return -1 if it doesnt
        if(checkConnections(tempIndexSecond, firstVertexType) == -1 ){
            //add connection
            addConnections(tempIndexSecond, firstVertexType);
        }
    }else{
        //check if first exists in second, checkConnect will return -1 if it doesnt
        if(checkConnections(tempIndexSecond,firstVertexType) == -1 ){
            //add connection
            addConnections(tempIndexSecond,firstVertexType);
        }
    }
    //reset temp values
    tempIndexFirst = tempIndexSecond = -2;
}

template <typename T>
int Graph<T> :: getVertices()
{
    return numberOfVertices;
}

template <typename T>
int Graph<T> :: getConnections(int index)
{
    if(numberOfVertices == 0 || index >= numberOfVertices)
        throw std::out_of_range("Going out of bounds inside [] operator A-List.");
    //return linked list inside linked list of linked lists
    return AdjencyLinkedInList[index].getNumOfElements()-1;
}

template <typename T>
void Graph<T> :: displayGraph()
{
    //check if list is empty
    if(numberOfVertices == 0){
        cout << "The list is empty." <<endl;
        return;
    }
    //display list
    for(int c = 0; c < numberOfVertices; c++){
        AdjencyLinkedInList[c].displayList();
        cout << "\n";
    }
}

#endif // GRAPH_H
