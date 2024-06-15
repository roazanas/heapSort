#ifndef HEAPSORTVIEW_H
#define HEAPSORTVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QResizeEvent>
#include "heapsort.h"

class HeapSortView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit HeapSortView(QWidget *parent = nullptr);
    void setData(const QVector<int>& data);

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void doStep();

private:
    void updateRectangles(QSize deltaSize = QSize(0, 0));
    QGraphicsScene *scene;
    QTimer *timer;
    HeapSort heapSort;
    QVector<int> data;
    QList<QGraphicsRectItem*> visualData;
    int currentStep;
    static QSize globalDeltaSize;
};

#endif // HEAPSORTVIEW_H
