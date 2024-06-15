#ifndef HEAPSORTVIEW_H
#define HEAPSORTVIEW_H

#include <QGraphicsView>
#include "heapsort.h"

class QGraphicsScene;
class QTimer;

class HeapSortView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit HeapSortView(QWidget *parent = nullptr);
    void setData(const QVector<int>& data);

public slots:
    void doStep();

private:
    QGraphicsScene *scene;
    QTimer *timer;
    HeapSort heapSort;
    QVector<int> data;
    int currentStep;
};

#endif // HEAPSORTVIEW_H
