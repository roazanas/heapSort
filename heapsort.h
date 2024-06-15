#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <QVector>

class HeapSort {
public:
    void sort(QVector<int>& data);

private:
    void heapify(QVector<int>& data, int n, int i);
};

#endif // HEAPSORT_H
