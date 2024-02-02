//Jason Siecienski

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <vector>
#include "graph.h"

using namespace std;

//default constructor
Graph::Graph() {
	maxSize = MAX_SIZE;
	gSize = 0;
	
}

//destructor
Graph::~Graph() {
	clearGraph();
}

int Graph::getSize() {
	return gSize;
}
bool Graph::isEmpty() {
	return (gSize == 0);
}

void Graph::clearGraph() {
	for (int index = 0; index < gSize; index++)
		//graph[index] is an STL list
		graph[index].clear();
	gSize = 0;
}


// this crashes by runtime
//read from a file and populate the array of adjacency lists
void Graph::readGraph(string fileName, int sentinel)
{
	ifstream infile;
	int vertex;
	int adjacentVertex;
	double cost; // variable to store the cost

	// if the graph is not empty, make it empty
	if (gSize != 0)
		clearGraph();

	infile.open(fileName.c_str(), ios::in);
	if (!infile)
	{
		cerr << "Cannot open the input file." << fileName << endl;
		return;
	}

	// first read the number of vertices
	infile >> gSize;

	// Resize the adjacency lists array to match the number of vertices
	for (int i = 0; i < gSize; ++i)
	{
		graph[i].clear(); // Clear any existing data
	}

	cout << "Graph size: " << gSize << endl; // Debugging output

	// for each vertex, read and store its adjacency list
	for (int index = 0; index < gSize; index++)
	{
		infile >> vertex;
		infile >> adjacentVertex;

		cout << "Reading vertex " << vertex << ", adjacentVertex " << adjacentVertex << endl; // Debugging output

		// Resize the adjacency list for the current vertex
		graph[vertex].resize(0);

		// the sentinel in the example files is -999)
		while (infile >> adjacentVertex && adjacentVertex != sentinel)
		{
			cout << "Adjacent: " << adjacentVertex << endl; // Debugging output

			// check if there is a cost specified
			if (adjacentVertex >= 0)
			{
				// graph[vertex] is an STL list
				graph[vertex].push_back(adjacentVertex);

				// Read the cost
				if (!(infile >> cost))
				{
					cerr << "Error reading cost for vertex " << vertex << endl;
					// Handle the error (e.g., break the loop or return)
					break;
				}

				cout << "Cost: " << cost << endl; // Debugging output

				// add the cost to the adjacency list
				// assuming that the cost is the last entry in the adjacency list
				graph[vertex].push_back(cost);
			}
			else
			{
				// graph[vertex] is an STL list
				graph[vertex].push_back(adjacentVertex);
			}
		}
	} // end for

	infile.close();
} // end readGraph



//Print the adjacency lists
void Graph::printGraph() {
	cout << "Graph size " << gSize << endl << endl;
	for (int index = 0; index < gSize; index++)
	{
		cout << "Vertex " << index << ": ";
		list<int>::iterator pos;
		for (pos = graph[index].begin();
			pos != graph[index].end(); pos++)
			cout << *pos << " ";
		cout << endl;
	}
	cout << endl;
}//end printGraph

void Graph::breadthFirstTraversal() {

	bool* visited = new bool[gSize];
	for (int ind = 0; ind < gSize; ind++)
		//initialy no vertex is visited                                 
		visited[ind] = false;

	int* adjacencyList;
	adjacencyList = new int[gSize];

	queue<int> q;
	for (int index = 0; index < gSize; index++)
		if (!visited[index])
		{
			q.push(index);
			visited[index] = true;
			cout << " " << index << " ";

			while (q.size() > 0)
			{
				int u = q.front();
				q.pop();
				int adjLstLngth; //will be passed by reference
				getAdjacentVertices(u, adjacencyList, adjLstLngth);

				for (int w = 0; w < adjLstLngth; w++)
					if (!visited[adjacencyList[w]])
					{
						q.push(adjacencyList[w]);
						visited[adjacencyList[w]] = true;
						cout << " " << adjacencyList[w] << " ";
					} //end if
			} //end while
		} //end if

	delete[] visited;
	delete[] adjacencyList;
} //end breadthFirstTraversal

void Graph::getAdjacentVertices(int vIndex, int adjacencyList[],
	int& length)
{
	list<int>::iterator pos;
	length = 0;
	for (pos = graph[vIndex].begin(); pos != graph[vIndex].end();
		pos++)
		adjacencyList[length++] = *pos;
} //end getAdjacentVertices

//Depth-first traversa starting at node 0
// Override the depthFirstTraversal function
double Graph::depthFirstTraversal() {
	resetTotalTraversalCost(); // Reset total cost before traversal

	// Array to keep track of visited vertices
	bool* visited = new bool[gSize];
	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false;

	// Perform depth-first traversal starting at each non-visited vertex
	for (int index = 0; index < gSize; index++) {
		if (!visited[index]) {
			dft(index, visited);
			// Additional check to handle unexpected situations
			if (index >= gSize) {
				cerr << "Error in depthFirstTraversal: Unexpected situation (Index out of bounds)" << endl;
				// Handle the error (e.g., break the loop or return)
				break;
			}
		}
	}

	delete[] visited; // Clean up the visited array

	return totalTraversalCost; // Return the total cost
}
// end depthFirstTraversal
// 
//Private recursive function 
//for depth-first traversal of a component
void Graph::dft(int v, bool visited[]) {
	// mark v as visited 
	visited[v] = true;
	// process the vertex, in this example just by printing
	cout << " " << v << " ";
	// Recursively call the function for each adjacent vertex
	int* adjacencyList = new int[gSize]; // dynamic array 
										// to retrieve the 
										// adjacent vertices	 
	int adjLstLength;      // to be set to the length of
						   // the retrieved adjacency list

	// Retrieve the adjacent vertices into adjacencyList
	// and set adjLstLength to its length
	getAdjacentVertices(v, adjacencyList, adjLstLength);

	// Sort the adjacency list based on edge costs
	sortAdjacencyListByCost(adjacencyList, adjLstLength, v);

	// for each vertex adjacent from v
	for (int index = 0; index < adjLstLength; index++) {
		int adjacent = adjacencyList[index];
		// if it is not visited
		if (!visited[adjacent]) {
			// call dft recursively
			dft(adjacent, visited);
			totalTraversalCost += getEdgeCost(v, adjacent); // Update total cost
		}
	}// end for

	delete[] adjacencyList;
}// end dft

// Helper function to sort the adjacency list based on edge costs
void Graph::sortAdjacencyListByCost(int adjacencyList[], int length, int fromVertex) {
	// Assuming that adjacencyList is an array of vertices
	// and there's a separate array edgeCosts storing edge costs

	// Create a vector of pairs where the first element is the vertex
	// and the second element is the corresponding edge cost
	std::vector<std::pair<int, double>> vertexCostPairs;

	for (int i = 0; i < length; ++i) {
		int adjacentVertex = adjacencyList[i];
		double cost = getEdgeCost(fromVertex, adjacentVertex);
		vertexCostPairs.push_back(std::make_pair(adjacentVertex, cost));
	}

	// Use std::sort to sort the vector of pairs based on the edge cost
	std::sort(vertexCostPairs.begin(), vertexCostPairs.end(),
		[](const auto& a, const auto& b) {
			return a.second < b.second;
		});

	// Copy the sorted vertices back to the adjacencyList
	for (int i = 0; i < length; ++i) {
		adjacencyList[i] = vertexCostPairs[i].first;
	}
}
//depth-first traversal of a component starting at a given vertex

// Helper function to get the edge cost between two vertices
double Graph::getEdgeCost(int fromVertex, int toVertex) const {
	// Assuming that costs are stored directly in the adjacency list
	// For simplicity, assuming that costs are the last entry in the adjacency list

	list<int>::const_iterator pos;
	for (pos = graph[fromVertex].begin(); pos != graph[fromVertex].end(); ++pos) {
		int vertex = *pos;
		++pos; // Move to the next entry (the cost)

		if (pos != graph[fromVertex].end()) {
			// Assuming the cost is the last entry in the adjacency list
			return static_cast<double>(*pos); // Convert to double if necessary
		}
		else {
			// Handle the case where the cost is missing or invalid
			// You might want to throw an exception or return a default value
			return 0.0;
		}
	}

	// Return a default value or handle the case where the edge doesn't exist
	return 0.0;
}
void Graph::dftAtVertex(int vertex)
{
	bool* visited;
	visited = new bool[gSize];

	for (int index = 0; index < gSize; index++)
		visited[index] = false;

	dft(vertex, visited);

	// Additional code to ensure complete traversal
	for (int index = 0; index < gSize; index++) {
		if (!visited[index])
			dft(index, visited);
	}

	delete[] visited;
} //end dftAtVertex

void Graph::resetTotalTraversalCost() {
	totalTraversalCost = 0.0;
}

