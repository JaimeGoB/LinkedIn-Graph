#include "LinkedInManager.h"
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

LinkedInManager::LinkedInManager()
{

}

void LinkedInManager ::  readFiles(char* FirstFile, char* SecondFile)
{
    //pipe and new line delimeter used to parce files
    string delimiter = "|", delimiter2 = "\n";
    //temp values to read file
    string numOfUsers = "0";
    //creating file obj
    ifstream File1(FirstFile);
    //error statement
    if(!File1){
        cerr << "File could not be read." << endl;
        exit(EXIT_FAILURE);
    }
    //reading in firstline
    getline(File1, numOfUsers, '\n');
    //reading whole file into a string
    string firstFile( (istreambuf_iterator<char>(File1) ),(istreambuf_iterator<char>() ) );
    //closing file
    File1.close();
    //replacing all \n with pipes so we only have one delimeter to parce from
    replace(firstFile.begin(), firstFile.end(), '\n', '|');

    //temp postion to iterate through string
    size_t currentPosOfString = 0;
    //temp string to hold userName
    string UserName;
    //loop until end of , looping
    while ((currentPosOfString = firstFile.find(delimiter)) != string::npos) {
        //user name equals the substring until pipe
        UserName = firstFile.substr(0, currentPosOfString);
        //adding the user names to be stored in a vector
        Users.push_back(UserName);
        //erasing this username and including the delimiter (whatever size it could be)
        firstFile.erase(0, currentPosOfString + delimiter.length());
    }

    //creating graph
    for(int a = 0; a < Users.getNumOfElements(); a+=2){
        LinkedInGraph.addEdge(Users[a], Users[a+1]);
    }


    LinkedInGraph.displayGraph();

    //creating file obj
    ifstream File2(SecondFile);
    //error statement
    if(!File2){
        cerr << "File could not be read." << endl;
        exit(EXIT_FAILURE);
    }
    //reading in firstline
    getline(File2, numOfUsers, '\n');
    //reading whole file into a string
    string secondFile( (istreambuf_iterator<char>(File2) ),(istreambuf_iterator<char>() ) );
    //closing file
    File2.close();
    //replacing all \n with pipes so we only have one delimeter to parce from
    replace(secondFile.begin(), secondFile.end(), '\n', '|');

    //temp postion to iterate through string
    size_t currentPosOfString2 = 0;
    //temp string to hold userName
    string User = "\0";
    //loop until end of , looping
    while ((currentPosOfString2 = secondFile.find(delimiter)) != string::npos) {
        //user name equals the substring until pipe
        User = secondFile.substr(0, currentPosOfString2);
        //adding the user names to be stored in a vector
        VectorOfPairToFindPaths.push_back(User);
        //erasing this username and including the delimiter (whatever size it could be)
        secondFile.erase(0, currentPosOfString2 + delimiter.length());
    }
}

int LinkedInManager :: iterativeBackTrackingThroughGraph(string begOfPath, string endOfPath)
{
    //creating an iterator for each linkedlist inside linkedlist
    VectorData<iteratorPtr<string> > GraphIterators;
    //creating a vector of stacks
    VectorData<Stack<string> > VectorOfStackPaths;
    //creating a stack that containg paths
    Stack<string> StackPaths;
    //pushing beginnin on to stack
    StackPaths.push(begOfPath);
    //creating an iterating for each linkedlist inside llist of llists
    for(int i = 0 ; i < LinkedInGraph.getVertices(); i ++){
        iteratorPtr<string> start(LinkedInGraph[i].getHead());
        GraphIterators.push_back(start);
    }
    iteratorPtr<string> position; //main iterator
    iteratorPtr<string> end; //nullptr

    // until stack is empty
    while(!StackPaths.isEmpty()){
        //check if top is the destitation
        if(StackPaths.peek() == endOfPath){
            //push stack onto vector of stacks
            VectorOfStackPaths.push_back(StackPaths);
            //pop value from stack
            StackPaths.pop();
        }else{
            int index = LinkedInGraph.findVertex( StackPaths.peek() );
            GraphIterators[index]++;

            //loop until found or no more connections
            while( GraphIterators[index] != end  && StackPaths.find( *(GraphIterators[index]) ) ){
                //move to next connection
                GraphIterators[index]++;
            }

            if( GraphIterators[index] != end ){
                StackPaths.push( *(GraphIterators[index]) );
            }else{
                //reset iterators ONLY SUBINDEX
                iteratorPtr<string> start(LinkedInGraph[index].getHead());
                GraphIterators[index] = start;
                StackPaths.pop();
            }

        }
    }
    //return the shortest stack-int
    return findShortestStack(VectorOfStackPaths);
}

int LinkedInManager :: findShortestStack(VectorData<Stack<string> > AllPaths)
{
    //initializing min to a big num
    int min = 1000;
    //looking for shortest stack
    for(int i = 0; i < AllPaths.getNumOfElements(); i++){
        if( min >= AllPaths[i].getNumOfElements() ){
            min = AllPaths[i].getNumOfElements();
        }
    }
    for(int i = 0; i < AllPaths.getNumOfElements(); i++){
            while(!AllPaths[i].isEmpty()) {
                cout << AllPaths[i].pop() << endl;
            }
            cout <<endl;
        }
        cout <<endl;

    //return shortest stack
    return min-1;
}

void LinkedInManager :: calculateConnectionsOfConnections()
{
    int tempIndex = 0;
    int connectionOfConnectionTotal = 0;
    //traversing through each vertex in this for loop
    for(int a = 0; a < LinkedInGraph.getVertices(); a++){
        //gettin the connections of a vertex in this for loop
        for(int b = 1; b < LinkedInGraph[a].getNumOfElements(); b++){
            //this index will be used to find a connection of the vertex
            tempIndex = LinkedInGraph.findVertex(LinkedInGraph[a][b]);
            //adding connectios of a connection of a vertex
            connectionOfConnectionTotal += LinkedInGraph[tempIndex].getNumOfElements();
        }
        //push total number of all the connections of connections on to vector
        outPutConnectionsVector.push_back( connectionOfConnectionTotal );
        //reseting counter for next vertex
        connectionOfConnectionTotal = 0;
    }
}

void LinkedInManager :: createOutPutFile(char* outFile)
{

    //creating output file
    ofstream output(outFile);
    //checking if file could not be open
    if(!output){
        cerr << "Final file could not be open." << endl;
        exit(EXIT_FAILURE);
    }
    /*
    PartI of output file will write each LinkedIn User
    followedby the integer containing connections and indirect connections (max level is 2)
    */
    calculateConnectionsOfConnections();
    //output results
    for(int b = 0; b < LinkedInGraph.getVertices(); b++){
        output << LinkedInGraph[b][0] << " " << outPutConnectionsVector[b] << endl;
    }
    /*
    PartII of output file will print the name pair, followed by the minimum distance between
    those calculated by an exhaustive iterative backtracking solution.
    */
    for(int c = 0; c < VectorOfPairToFindPaths.getNumOfElements()-1; c += 2){
        output << VectorOfPairToFindPaths[c]   << " "
               << VectorOfPairToFindPaths[c+1] << " "
               << iterativeBackTrackingThroughGraph(VectorOfPairToFindPaths[c], VectorOfPairToFindPaths[c+1])
               << endl;
    }
    //close file
    output.close();
}
