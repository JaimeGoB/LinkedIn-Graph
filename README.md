# LinkedIn-Graph
This algorithm to determine the shortest path in graph using an exhaustive iterative backtracking Depth-first search (DFS). 


Here is an example of a data input file (this is the graph):
![alt text](https://github.com/JaimeGoB/LinkedIn-Graph/blob/master/graph.png)

4
Bob Smith|Sally Simpson

Sally Simpson|Daniel Davidson

Sally Simpson|Susan Jackson

Susan Jackson|Daniel Davidson


The first line of the file will contain an integer indicating how many rows of data will
be in the file. Each subsequent row will contain two individual’s names separated
with a pipe (shift-\ on most keyboards).

Requested Distance Data File

3
Bob Smith|Daniel Davidson

Sally Simpson|Daniel Davidson

Bob Smith|Bob Smith

Output File

A sample input file for requested minimum connection distance is shown below. .
The first line will contain an integer indicating the number of input lines in this file.
The subsequent lines will contain a pipe-delimited list of individual pairs separated
by a pipe. 


The output file should have n + m lines of output where n is the number
of unique individuals in the system (the number of nodes) and m is the number of
requested pairs for which min distance is requested.


The program will run command line with the
following arguments:
./linkedin -r <ConnectionsDatafile> <RequestedConnections>
<OutputFile>

Alternatively, the program will run the Tests for dynamic memory allocation of they LinkedList, Stack, and Adjacency List if is is called with the following argument:
./linkedin -t
