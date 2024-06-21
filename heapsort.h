#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <QDebug>

class HeapSort {
public:
    HeapSort(std::vector<int>& data);
    void sort();
    const std::vector<int>& getData() const;

    // Методы для анимации
    bool step();
    void reset();

private:
    void heapify(int n, int i);
    void swap(int& a, int& b);
    std::vector<int>& data_;
    int size_;
    int currentIdx_;
    int sortedIdx_;
    int heapifyIdx_;
    bool heapifyStep_;
};

#endif // HEAPSORT_H
