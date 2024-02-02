#pragma once
// heap.h

#ifndef HEAP_H
#define HEAP_H

#include <vector>

template <typename T>
class Heap {
public:
    Heap();
    void push(const T& new_element);
    T top() const;
    void pop();
    int size() const;

private:
    void fix_heap();
    int get_left_child_index(int index);
    int get_right_child_index(int index);
    int get_parent_index(int index);
    T get_left_child(int index);
    T get_right_child(int index);
    T get_parent(int index);

    std::vector<T> elements;
};

#endif // HEAP_H