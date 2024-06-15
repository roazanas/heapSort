#include "heapsort.h"
#include <algorithm> // для std::swap

HeapSort::HeapSort() {}

void HeapSort::heapify(QVector<int>& data, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && data[left] > data[largest])
        largest = left;

    if (right < n && data[right] > data[largest])
        largest = right;

    if (largest != i) {
        std::swap(data[i], data[largest]);
        heapify(data, n, largest);
    }
}

void HeapSort::sort(QVector<int>& data) {
    int n = data.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(data[0], data[i]);
        heapify(data, i, 0);
    }
}

void HeapSort::doStep(QVector<int>& data, int currentStep) {
    if (currentStep < data.size()) {
        heapify(data, data.size(), currentStep);
    }
}
