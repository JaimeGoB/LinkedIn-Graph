#ifndef VECTORDATA_H
#define VECTORDATA_H
#include <iostream>
#include <fstream>
#include <string>
#include "catch.hpp"


using namespace std;

template <typename T>
class VectorData
{
public:
    VectorData();
    VectorData(const VectorData<T>& t);
    ~VectorData();
    T &operator[](const int index);
    VectorData<T>& operator=(const VectorData<T>& rightObj);
    void increaseSize();
    void increaseNumOfElements();
    int getNumOfElements();//elements inside vector
    void push_back(T t);
    void pop_back();

private:
    int numOfElements;
    int size;
    T* dataPtr;
    bool isEmpty;
};

template <typename T>
VectorData<T>::VectorData() {

    numOfElements = 0;
    size =2;//default size of vector
    dataPtr =new T[size];
    isEmpty = true;//if true there is nothing inside vector
}

template <typename T>
VectorData<T>::~VectorData() {

    delete[] dataPtr;
}

template <typename T>//copy constructor
VectorData<T>::VectorData(const VectorData<T>& rightObj)//populate items of rhs to lfh(empty obj)
{
    this->isEmpty = rightObj.isEmpty;
    this->numOfElements = rightObj.numOfElements;
    this->size = rightObj.size;

    this->dataPtr =new T[size];//creating temp pointer

    for(int i = 0; i < numOfElements; i++){//copying everything
        this->dataPtr[i] = rightObj.dataPtr[i];
    }


}

template<typename T>
VectorData<T>& VectorData<T>::operator=(const VectorData<T>& rightObj)
{
    if(this == &rightObj){
        return *this;
    }

    this->isEmpty = rightObj.isEmpty;
    this->numOfElements = rightObj.numOfElements;
    this->size = rightObj.size;

    delete[] this->dataPtr;//delete lhs pointer
    this->dataPtr =new T[size];//creating temp pointer

    for(int i = 0; i < numOfElements; i++){//copying everything
        this->dataPtr[i] = rightObj.dataPtr[i];
    }

    return *this;
}

template<typename T>
T &VectorData<T>::operator[](const int index) {


    if(index > numOfElements-1 || index < 0){//check for out of bounds
        throw out_of_range("Location out of bounds, Inside subscript operator.");
    }

    return dataPtr[index];
}

template <typename T>
void VectorData<T>::increaseSize()
{
    T* tempPtr =new T[size *2];//creating temp pointer

    for(int i = 0; i < numOfElements; i++){//copying everything
        tempPtr[i] = dataPtr[i];
    }

    size *=2;//changing size of vectorData
    delete [] dataPtr;//deleting previous pointer
    dataPtr = tempPtr;//dataPtr = larger pointer

}

template <typename T>
void VectorData<T>::increaseNumOfElements()
{
    numOfElements++;
}

template <typename T>
int VectorData<T>::getNumOfElements()
{
    return numOfElements;
}

template <typename T>
void VectorData<T>::push_back(T t)
{
    if(numOfElements == 0){
        isEmpty = false;
    }

    if(numOfElements == (size-1)){//make vector bigger if full
        increaseSize();
    }

    dataPtr[numOfElements++] = t;
}

template <typename T>
void VectorData<T> ::pop_back()
{
    if( numOfElements == 0 ){//check if empty
        throw logic_error("You cannot delete an item in empty vector. Inside pop_back.");
    }else{//erase last element by
        numOfElements--;//delete last element
    }
}

#endif // VECTORDATA_H

