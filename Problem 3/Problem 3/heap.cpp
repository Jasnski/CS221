// heap.cpp

// heap.cpp

#include "heap.h"

template <typename T>
Heap<T>::Heap() {
    elements.push_back(T());
}

template <typename T>
void Heap<T>::push(const T& new_element) {
    // Add a new leaf
    elements.push_back(T());
    int index = size();

    // Promote parents that are smaller than the new element
    while (index > 1 && get_parent(index) < new_element) {
        elements[index] = get_parent(index);
        index = get_parent_index(index);
    }

    // Store the new element into the vacant slot
    elements[index] = T(new_element); // Use copy constructor
}

template <typename T>
T Heap<T>::top() const {
    return elements[1];
}

template <typename T>
void Heap<T>::pop() {
    if (size() > 1) {
        // Swap the top element with the last element
        std::swap(elements[1], elements[size()]);

        // Remove the last element
        elements.pop_back();

        // Restore the heap property by fixing the heap
        fix_heap();
    }
    else if (size() == 1) {
        // If there is only one element, remove it
        elements.pop_back();
    }
    // If the heap is empty, do nothing
}

template <typename T>
int Heap<T>::size() const {
    return elements.size() - 1;
}

template <typename T>
void Heap<T>::fix_heap() {
    int root = elements[1];
    int last_index = size();

    // Promote children of the moved root while they are larger than the last element
    int index = 1;
    bool more = true;
    while (more) {
        int child_index = get_left_child_index(index);
        if (child_index <= last_index) {
            // Get larger child

            // Get left child first
            T child = get_left_child(index);

            // Use right child instead if it is larger
            if (get_right_child_index(index) <= last_index && get_right_child(index) > child) {
                child_index = get_right_child_index(index);
                child = get_right_child(index);
            }

            // Check if the smaller child is larger than the root
            if (child > root) {
                // Promote child
                elements[index] = child;
                index = child_index;
            }
            else {
                // Root is larger than both children
                more = false;
            }
        }
        else {
            // No children
            more = false;
        }
    }

    // Store the moved root element in the vacant slot
    elements[index] = root;
}

template <typename T>
int Heap<T>::get_left_child_index(int index) {
    return 2 * index;
}

template <typename T>
int Heap<T>::get_right_child_index(int index) {
    return 2 * index + 1;
}

template <typename T>
int Heap<T>::get_parent_index(int index) {
    return index / 2;
}

template <typename T>
T Heap<T>::get_left_child(int index) {
    return elements[2 * index];
}

template <typename T>
T Heap<T>::get_right_child(int index) {
    return elements[2 * index + 1];
}

template <typename T>
T Heap<T>::get_parent(int index) {
    return elements[index / 2];
}

