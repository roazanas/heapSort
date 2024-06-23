#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <QObject>
#include <QDebug>
#include <QTimer>

class HeapSort : public QObject {
    Q_OBJECT
public:
    explicit HeapSort(QObject* parent = nullptr);
    void setTimerDelay(int ms) { timerDelay = ms;};

public slots:
    void sort(std::vector<int>& data);

signals:
    void dataChanged(const std::vector<int>& data);
    void messageSent(const QString& message);
    void statusBarUpdated(int arraySize, int iterations, int comparisons, int arrayAccesses);
    void sortedIndex(int index);
    void indexesToSwap(int index1, int index2);
    void sortEnded();

private slots:
    void heapSortStep();

private:
    void heapify(std::vector<int>& data, int n, int i);
    void swap(std::vector<int>& data, int i1, int i2);

    std::vector<int> data_;
    int n_;
    int i_;
    QTimer timer_;
    int timerDelay = 200;

    int iterations_;
    int comparisons_;
    int arrayAccesses_;
};

#endif // HEAPSORT_H
