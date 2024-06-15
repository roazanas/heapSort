#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <QVector>

class HeapSort {
public:
    HeapSort();
    void sort(QVector<int>& data);
    void doStep(QVector<int>& data, int currentStep);

private:
    void heapify(QVector<int>& data, int n, int i);
};

#endif // HEAPSORT_H
