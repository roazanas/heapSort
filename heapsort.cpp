#include "heapsort.h"

void HeapSort::heapify(QVector<int> &data, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && data[left] > data[largest])
        largest = left;

    if (right < n && data[right] > data[largest])
        largest = right;

    if (largest != i) {
        std::swap(data[i], data[largest]);
        emit elementsSwapped(i, largest);
        heapify(data, n, largest);
    }
}

void HeapSort::buildHeap(QVector<int> &data, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(data, n, i);
    }
}

void HeapSort::doStep(QVector<int> &data, int currentStep) {
    int n = data.size();
    if (currentStep == 0) {
        buildHeap(data, n);
    } else {
        std::swap(data[0], data[n - currentStep]);
        emit elementsSwapped(0, n - currentStep);
        heapify(data, n - currentStep, 0);
    }
    emit dataChanged(data);
}
