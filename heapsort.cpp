#include "heapSort.h"

HeapSort::HeapSort(std::vector<int>& data) : data_(data), size_(data.size()), currentIdx_(0), sortedIdx_(data.size()), heapifyIdx_(0), heapifyStep_(true) {
    qDebug() << "HeapSort::HeapSort - Created HeapSort object with data:" << data_;
}

void HeapSort::sort() {
    qDebug() << "HeapSort::sort - Starting sort";
    reset();
    while (step()) {
        qDebug() << "HeapSort::sort - Sort step completed, data:" << data_;
    }
    qDebug() << "HeapSort::sort - Sorting finished, data:" << data_;
}

const std::vector<int>& HeapSort::getData() const {
    return data_;
}

void HeapSort::heapify(int n, int i) {
    qDebug() << "HeapSort::heapify - Heapifying at index" << i << "with size" << n;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && data_[left] > data_[largest]) {
        largest = left;
    }
    if (right < n && data_[right] > data_[largest]) {
        largest = right;
    }
    if (largest != i) {
        qDebug() << "HeapSort::heapify - Swapping elements at" << i << "and" << largest;
        swap(data_[i], data_[largest]);
        heapify(n, largest);
    }
}

void HeapSort::swap(int& a, int& b) {
    qDebug() << "HeapSort::swap - Swapping" << a << "and" << b;
    int temp = a;
    a = b;
    b = temp;
}

bool HeapSort::step() {
    qDebug() << "HeapSort::step - Performing step";
    if (heapifyStep_) {
        qDebug() << "HeapSort::step - Heapify step";
        if (heapifyIdx_ < size_ / 2 - 1) {
            heapify(size_, heapifyIdx_);
            heapifyIdx_++;
        } else {
            qDebug() << "HeapSort::step - Heapify phase finished";
            heapifyStep_ = false;
            heapifyIdx_ = size_ - 1;
        }
    } else {
        qDebug() << "HeapSort::step - Sorting step";
        if (heapifyIdx_ >= 0) {
            swap(data_[0], data_[heapifyIdx_]);
            heapify(heapifyIdx_, 0);
            heapifyIdx_--;
        } else {
            qDebug() << "HeapSort::step - Sorting finished";
            return false;
        }
    }
    return true;
}

void HeapSort::reset() {
    qDebug() << "HeapSort::reset - Resetting HeapSort";
    size_ = data_.size();
    currentIdx_ = 0;
    sortedIdx_ = data_.size();
    heapifyIdx_ = 0;
    heapifyStep_ = true;
}
