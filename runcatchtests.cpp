#include <iostream>
#include <string>
#include <cstring>
#include <Graph.h>
#include <linkedlist.h>
#include <node.h>
#include <stack.h>
#include <VectorData.h>
#include "catch.hpp"

using namespace std;

TEST_CASE("Testing Data structures used in Program4",
          "[LinkedList], [Stack], [Iterator], [Graph], [Vector]")
{
    LinkedList<int> Testing123;//int vector
    LinkedList<string>stringTest;//string vector
    LinkedList<char>charTest;//char vector

    //constant stuff goes here, things we will be testing
    for(int i = 0; i < 10; i++){
        Testing123.insertBack(i);
    }

    stringTest.insertBack("a");
    stringTest.insertBack("b");
    stringTest.insertBack("c");
    stringTest.insertBack("d");


    charTest.insertBack('a');
    charTest.insertBack('b');
    charTest.insertBack('c');
    charTest.insertBack('d');

    //Testing assignment operator
    LinkedList<int> Testing123A;//int vector
    Testing123A = Testing123;
    //making B = A
    LinkedList<int> Testing123B;//int vector
    Testing123B = Testing123A;
    //making C = B
    LinkedList<int> Testing123C;//int vector
    Testing123C = Testing123B;
    SECTION("Testing operator= ")
    {
        REQUIRE(Testing123[0] == 0);
        REQUIRE(Testing123A[0] == 0);
        REQUIRE(Testing123B[0] == 0);
        REQUIRE(Testing123C[0] == 0);

    }

    SECTION("Testing insertBack ")
    {
        REQUIRE(Testing123[0] == 0);
        REQUIRE(Testing123[1] == 1);
        REQUIRE(Testing123[2] == 2);
        REQUIRE(Testing123[3] == 3);
        REQUIRE(Testing123[4] == 4);
    }

    SECTION("Testing operator[] ")
    {
        REQUIRE(stringTest[0] == "a");
        REQUIRE(stringTest[1] == "b");
        REQUIRE(stringTest[2] == "c");
        REQUIRE(stringTest[3] == "d");
        REQUIRE(charTest[0] == 'a');

    }

    //Testing copy constructor
    LinkedList<int> Testing123E(Testing123);
    LinkedList<int> Testing123F(Testing123);
    LinkedList<int> Testing123G(Testing123);
    LinkedList<int> Testing123H(Testing123);
    SECTION("Testing copyLL, note this function is only called on overloaded = and copy constructor ")
    {
        REQUIRE(Testing123E[0] == 0);
        REQUIRE(Testing123F[9] == 9);
        REQUIRE(Testing123G[9] == 9);
        REQUIRE(Testing123H[9] == 9);
    }

    SECTION("Testing getNumOfElements ")
    {
        REQUIRE(Testing123E.getNumOfElements() == 10);
        REQUIRE(Testing123F.getNumOfElements() == 10);
        REQUIRE(Testing123G.getNumOfElements() == 10);
        REQUIRE(Testing123H.getNumOfElements() == 10);
    }

    Testing123E.clearLL();
    Testing123F.clearLL();
    Testing123G.clearLL();
    Testing123H.clearLL();
    SECTION("Testing clearLL ")
    {
        REQUIRE(Testing123E.getNumOfElements() == 0);
        REQUIRE(Testing123F.getNumOfElements() == 0);
        REQUIRE(Testing123G.getNumOfElements() == 0);
        REQUIRE(Testing123H.getNumOfElements() == 0);
    }

    SECTION("Testing isEmpty ")
    {
        REQUIRE(Testing123E.empty() == 1);
        REQUIRE(Testing123F.empty() == 1);
        REQUIRE(Testing123G.empty() == 1);
        REQUIRE(Testing123H.empty() == 1);
    }

    stringTest.removeBack();
    stringTest.removeBack();
    stringTest.removeBack();
    stringTest.removeBack();
    SECTION("Testing removeBack ")
    {
        REQUIRE(stringTest.getNumOfElements() == 0);
        REQUIRE(stringTest.empty() == 1);

    }

    SECTION("Testing find ")
    {
        REQUIRE(charTest.find('a') == 1);
        REQUIRE(charTest.find('b') == 1);
        REQUIRE(charTest.find('c') == 1);
        REQUIRE(charTest.find('d') == 1);

    }

    //Starting Tests for Stack class here
    Stack<int> S;
    Stack<int> S1;
    Stack<int> S2;
    S.push(1);
    S1.push(1);
    S1.push(2);
    S2.push(1);
    S2.push(2);
    S2.push(3);

    SECTION("Testing push ")
    {
        REQUIRE(S.peek() == 1);
        REQUIRE(S1.peek() == 2);
        REQUIRE(S2.peek() == 3);
    }

    S.pop();
    SECTION("Testing pop ")
    {
        REQUIRE(S.isEmpty() == true);
        REQUIRE(S1.pop() == 2);
        REQUIRE(S2.pop() == 3);
        REQUIRE(S2.pop() == 2);
    }

    SECTION("Testing getNumOfElements")
    {
        REQUIRE(S.getNumOfElements() == 0);
        REQUIRE(S1.getNumOfElements() == 2);
        REQUIRE(S2.getNumOfElements() == 3);
    }

    SECTION("empty ")
    {
        REQUIRE(S.isEmpty() == true);
        REQUIRE(S1.isEmpty() == false);
        REQUIRE(S2.isEmpty() == false);
    }

    S.push(11);
    S.push(12);
    S.push(13);
    S.push(14);//last element added on stack
    S1.push(14);//last element added on stack
    S2.push(14);//last element added on stack
    SECTION("Testing peek ")
    {
        REQUIRE(S.peek() == 14);
        REQUIRE(S1.peek() == 14);
        REQUIRE(S2.peek() == 14);
    }

    SECTION("Testing find")
    {
        REQUIRE(S.find(14) == 1);
        REQUIRE(S1.find(14) == 1);
        REQUIRE(S2.find(14) == 1);
    }

    //running tests for graph:

    //The only function that will not be tested is the addVertex function since this
    //function is only used when an Edge is added. It is not used outside of the object.

    Graph<string> Graph;
    Graph.addEdge("A", "B");
    Graph.addEdge("A", "C");
    Graph.addEdge("A", "D");

    SECTION("Testing addEdge")
    {
        REQUIRE(Graph.findVertex("A") != -1);
        REQUIRE(Graph.findVertex("B") != -1);
        REQUIRE(Graph.findVertex("C") != -1);
    }

    SECTION("Testing []")
    {
        REQUIRE(Graph[0][0] == "A");
        REQUIRE(Graph[1][0] == "B");
        REQUIRE(Graph[2][0] == "C");
    }

    SECTION("Testing find vertex")
    {
        REQUIRE(Graph.findVertex("A") != -1 );
        REQUIRE(Graph.findVertex("B") != -1 );
        REQUIRE(Graph.findVertex("C") != -1 );
    }

    SECTION("Testing getVertices")
    {
        REQUIRE(Graph.getVertices() == 4 );

    }

    SECTION("Testing checkConnections")
    {
        REQUIRE(Graph.checkConnections(0,"B") != -1 );
        REQUIRE(Graph.checkConnections(0,"C") != -1 );
        REQUIRE(Graph.checkConnections(1,"A") != -1 );
    }

    SECTION("Testing getConnections")
    {
        REQUIRE(Graph.getConnections(0) == 3 );
        REQUIRE(Graph.getConnections(1) == 1 );
        REQUIRE(Graph.getConnections(2) == 1 );

    }

    //Testing iterator class here
    LinkedList<int> LL11;
    LL11.insertBack(1);
    LL11.insertBack(2);
    LL11.insertBack(3);
    LL11.insertBack(4);
    LL11.insertBack(5);

    iteratorPtr<int> start(LL11.getHead());
    iteratorPtr<int> position; //main iterator
    iteratorPtr<int> end; //nullptr

    SECTION("Testing overloaded *")
    {
        REQUIRE(*(start) == 1 );
    }

    start++;

    SECTION("Testing overloaded ++ and !=")
    {
        REQUIRE(*(start) == 2 );
    }
    //testing vector class here
    VectorData<int> T123;//int vector
    VectorData<string>stringT;//string vector
    VectorData<char>charT;//char vector


    //constant stuff goes here, things we will be testing
    for(int i = 0; i < 10; i++){
        T123.push_back(i);
    }

    stringT.push_back("a");
    stringT.push_back("b");
    stringT.push_back("c");
    stringT.push_back("d");

    charT.push_back('a');
    charT.push_back('b');
    charT.push_back('c');
    charT.push_back('d');

    SECTION("Testing operator[] ")
    {
        REQUIRE(stringT[0] == "a");
        REQUIRE(stringT[1] == "b");
        REQUIRE(stringT[2] == "c");
        REQUIRE(stringT[3] == "d");
    }
}

