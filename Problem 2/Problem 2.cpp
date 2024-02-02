//Jason Siecienski
#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

int main()
{
	// Introduction to the Graph Traversal Program
	std::cout << "Welcome to the Graph Traversal Program!\n";
	std::cout << "This program demonstrates depth-first and breadth-first traversal of a graph.\n\n";

	// Creating a Graph
	Graph myGraph;

    // Reading Graph Data
    std::cout << "Reading graph data from files...\n";
    //myGraph.readGraph("C:\\Temp\\dataG3.txt", -999);
    //myGraph.readGraph("C:\\Temp\\test.txt", -999);
     
     
    
    //This was mine. I had to use it for my end to use for the homework
   myGraph.readGraph("C:\\Programing Class\\CS2212023\\Assignment 2\\Problem 2\\dataG3.txt", -999);
   //myGraph.readGraph("C:\\Programing Class\\CS2212023\\Assignment 2\\Problem 2\\test.txt", -999);



    // Displaying the Graph
    std::cout << "\nGraph Details:\n";
    myGraph.printGraph();
    std::cout << "\n";

    // Depth-First Traversal
    std::cout << "Depth-First Traversal: ";
    myGraph.depthFirstTraversal();
    std::cout << "\n\n";

    // Breadth-First Traversal
    std::cout << "Breadth-First Traversal: ";
    myGraph.breadthFirstTraversal();
    std::cout << "\n";

    // End of Program
    std::cout << "\nThank you for using the Graph Traversal Program!\n";

    return 0;
}