#ifndef H_GRAPH
#define H_GRAPH

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
using namespace std;
const int MAX_SIZE = 20;

class Graph
{
public:
	//Default constructor
	//The graph size is set to 0, that is,
	//gSize = 0; maxSize = size.
	Graph();

	//Destructor
	//The storage occupied by the graph 
	//               is deallocated.
	~Graph();

	//Determine whether the graph is empty.
	//Returns true if the graph is empty; 
	//               otherwise, returns false.
	bool isEmpty();

	//Create the graph by reading from a file   
	//and using the adjacency list representation.
	//The graph is created in the form of
	//               adjacenty lists.
	virtual void readGraph(string fileName, int sentinel);

	//Deallocate the memory occupied by the linked 
	//lists in the array of adjacency lists
	void clearGraph();

	//Print the graph as a sequence of adjacency lists.
	void printGraph();

	//Perform the breadth first traversal of the entire graph.
	void breadthFirstTraversal();

	//Perform the depth first traversal of the entire graph
	//For each component delegates the work 
	//to recursive function dtf 
	double depthFirstTraversal();

	double getEdgeCost(int fromVertex, int toVertex) const;

	//Perform the depth first traversal of a component 
	//starting at a vertex specified by the parameter vertex.
	void dftAtVertex(int vertex);

	//Retrieve the vertices adjacent from a given vertex
	//in the parameter array adjacencyList. 
	//Parameter vIndex: vertex index in the array graph
	//Parameter length: set to the number of vertices adjacent 
	//from the vertex at index vIndex.
	void getAdjacentVertices(int vIndex, int adjacencyList[],
		int& length);

	//Return the size of the graph (number of vertices)
	int getSize();

	void resetTotalTraversalCost();

protected:
	int maxSize;         //maximum number of vertices
	int gSize;           //current number of vertices
	list<int> graph[MAX_SIZE]; //array of adjacency lists

private:
	//The actual recursibve function 
	//performing the depth first traversal of a graph component 
	//starting at a particular vertex.
	void dft(int v, bool visited[]);
	void sortAdjacencyListByCost(int adjacencyList[], int length, int fromVertex);
	double totalTraversalCost; // Declare totalTraversalCost as a private member variable

};

#endif