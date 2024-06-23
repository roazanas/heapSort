#include "heapsort.h"
#include <QDebug>

HeapSort::HeapSort(QObject* parent) : QObject(parent), n_(0), i_(0),
    iterations_(0), comparisons_(0), arrayAccesses_(0) {
    connect(&timer_, &QTimer::timeout, this, &HeapSort::heapSortStep);
    qDebug() << "HeapSort::HeapSort - Объект HeapSort создан";
}

void HeapSort::sort(std::vector<int>& data) {
    data_ = data;
    n_ = data_.size();
    i_ = n_ - 1;

    iterations_ = 0;
    comparisons_ = 0;
    arrayAccesses_ = 0;

    emit statusBarUpdated(n_, iterations_, comparisons_, arrayAccesses_);

    qDebug() << "HeapSort::sort - Начало сортировки";
    emit messageSent(QString("Начало сортировки"));

    for (int j = n_ / 2 - 1; j >= 0; j--) {
        qDebug() << "HeapSort::sort - Построение кучи, элемент:" << j;
        heapify(data_, n_, j);
    }

    qDebug() << "HeapSort::sort - Куча построена, начало сортировки";
    emit messageSent(QString("Куча построена, начало сортировки"));
    emit dataChanged(data_);

    timer_.start(200);
}

void HeapSort::heapSortStep() {
    if (i_ < 0) {
        qDebug() << "HeapSort::heapSortStep - Сортировка завершена";
        emit messageSent(QString("Сортировка завершена"));
        timer_.stop();
        emit sortEnded();
        return;
    }

    qDebug() << "HeapSort::heapSortStep - Шаг сортировки, итерация:" << iterations_;
    emit messageSent(QString("Шаг сортировки, итерация: %1").arg(iterations_));

    swap(data_, 0, i_);
    heapify(data_, i_, 0);
    emit sortedIndex(i_);
    i_--;

    emit dataChanged(data_);
    iterations_++;
    emit statusBarUpdated(n_, iterations_, comparisons_, arrayAccesses_);
}

void HeapSort::heapify(std::vector<int>& data, int n, int i) {
    qDebug() << "HeapSort::heapify - Вызов heapify для элемента:" << i;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {comparisons_++; arrayAccesses_ += 2;}
    if (left < n && data[left] > data[largest]) {
        largest = left;
        qDebug() << "HeapSort::heapify - Левый дочерний элемент больше, largest = " << largest;
    }

    if (left < n) {comparisons_++; arrayAccesses_ += 2;}
    if (right < n && data[right] > data[largest]) {
        largest = right;
        qDebug() << "HeapSort::heapify - Правый дочерний элемент больше, largest = " << largest;
    }

    if (largest != i) {
        qDebug() << "HeapSort::heapify - Обмен элементов " << i << " и " << largest;
        emit messageSent(QString("Обмен элементов с индексами %1 и %2").arg(i).arg(largest));
        swap(data, i, largest);
        arrayAccesses_ += 3;
        heapify(data, n, largest);
    }
    emit statusBarUpdated(n_, iterations_, comparisons_, arrayAccesses_);
}


void HeapSort::swap(std::vector<int>& data, int i1, int i2) {
    emit indexesToSwap(i1, i2);
    qDebug() << "HeapSort::swap - Обмен элементов" <<i1 <<"и" <<i2;
    int temp = data[i1];
    data[i1] = data[i2];
    data[i2] = temp;
}
