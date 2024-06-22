#ifndef HEAPSORTVIEW_H
#define HEAPSORTVIEW_H

#include <QGraphicsView>
#include <vector>
#include "heapSort.h"
#include <QTimer>

class HeapSortView : public QGraphicsView {
    Q_OBJECT
public:
    HeapSortView(QWidget* parent = nullptr);
    void setData(const std::vector<int>& data);
    const std::vector<int>& getData() const;
    void visualize();

    // Публичные методы для управления таймером
    void startAnimation();
    void stopAnimation();

    void generateRandomData(int n);

private slots:
    void animateSort();

private:
    std::vector<int> data_;
    HeapSort* heapSorter_;
    QTimer* timer_;
};

#endif // HEAPSORTVIEW_H
