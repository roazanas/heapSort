#ifndef HEAPSORTVIEW_H
#define HEAPSORTVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QResizeEvent>
#include "heapsort.h"

class HeapSortView : public QGraphicsView {
    Q_OBJECT

public:
    explicit HeapSortView(QWidget *parent = nullptr);
    void setData(const QVector<int>& data);

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void doStep();
    void onDataChanged(const QVector<int>& data);
    void onElementsSwapped(int index1, int index2);

private:
    void updateRectangles(QSize deltaSize = QSize(0, 0));
    void updateRectangle(int index);
    void resetRectangleColors();
    void resetRectangleColor(int index); // Новый метод
    QGraphicsScene *scene;
    QTimer *timer;
    HeapSort heapSort;
    QVector<int> data;
    QList<QGraphicsRectItem*> visualData;
    int currentStep;
    static QSize globalDeltaSize;
    QSet<int> swappedIndices;
};

#endif // HEAPSORTVIEW_H
