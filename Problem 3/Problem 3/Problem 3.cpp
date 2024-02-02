// main.cpp
//Jason Siecienski
#include "heap.h"
#include "heap.cpp"
#include <iostream>
#include <string>

// User-defined class
#include "heap.h"
#include <iostream>

class MyClass {
public:
    int value;

    MyClass() : value(0) {}
    MyClass(int v) : value(v) {}

    // Comparison operator is required for the heap
    bool operator<(const MyClass& other) const {
        return value < other.value;
    }
};

int main() {

        // Welcome Message
        std::cout << "Welcome to the Heap Test Program!\n";
        std::cout << "This program demonstrates the usage of a generic heap implementation in C++.\n\n";

        // Test with User-defined class objects
        std::cout << "Testing with user-defined class objects:\n";
        Heap<MyClass> myClassHeap;

        // Creating instances of MyClass
        MyClass obj1(5);
        MyClass obj2(3);
        MyClass obj3(7);

        // Pushing MyClass objects into the heap
        myClassHeap.push(obj1);
        myClassHeap.push(obj2);
        myClassHeap.push(obj3);

        // Displaying the top element in myClassHeap
        std::cout << "Top element in myClassHeap: " << myClassHeap.top().value << "\n\n";

        // End of Program
        std::cout << "Thank you for using the Heap Test Program!\n";

        return 0;
    }