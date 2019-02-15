#define CATCH_CONFIG_RUNNER
#define TEST true
#include <iostream>
#include <string>
#include <node.h>
#include <linkedlist.h>
#include <stack.h>
#include <Graph.h>
#include <catch.hpp>
#include <VectorData.h>
#include <LinkedInManager.h>
#include <iteratorPtr.h>

using namespace std;

int main(int argc, char * argv[])
{
    VectorData<string> Test;
    //This will let the Test, be able to test functions from Vector Class
        if(strcmp(argv[2], "-t")==0){
            Catch::Session().run();
        }else
        if(strcmp(argv[2],"-r") ==0)
        {//This will create an object in Driver class (PArcer)
            LinkedInManager Manager;
            Manager.readFiles(argv[3],argv[4]);
            Manager.createOutPutFile(argv[5]);

        }

    return 0;
}

