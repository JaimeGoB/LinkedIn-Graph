#ifndef LINKEDINMANAGER_H
#define LINKEDINMANAGER_H
#include <iostream>
#include <string>
#include <fstream>
#include <node.h>
#include <linkedlist.h>
#include <stack.h>
#include <Graph.h>
#include <VectorData.h>
#include <iteratorPtr.h>

using namespace std;

class LinkedInManager
{
public:
    LinkedInManager();
    void readFiles(char* FirstFile, char* SecondFile);
    int iterativeBackTrackingThroughGraph(string beg, string end);
    int findShortestStack(VectorData<Stack<string> > StackPaths);
    void calculateConnectionsOfConnections();
    void createOutPutFile(char* outFile);
private:
    int numberOfUsers;
    int numOfPaths;
    Graph<string> LinkedInGraph;
    //this vector will contain the minimum distance between paths
    VectorData<int> outPutPathVector;
    //this vector will contain the connections of connections
    VectorData<int> outPutConnectionsVector;
    //this vector will contain pair to find paths
    VectorData<string> VectorOfPairToFindPaths;
    //this vector will contain the users of LinkedIn and will be used to create edges in graph
    VectorData<string> Users;
};

#endif // LINKEDINMANAGER_H
