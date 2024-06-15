#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <QObject>
#include <QVector>

class HeapSort : public QObject {
    Q_OBJECT

public:
    void heapify(QVector<int> &data, int n, int i);
    void buildHeap(QVector<int> &data, int n);
    void doStep(QVector<int> &data, int currentStep);

signals:
    void dataChanged(const QVector<int> &data);
    void elementsSwapped(int index1, int index2);  // Добавим этот сигнал
};

#endif // HEAPSORT_H
