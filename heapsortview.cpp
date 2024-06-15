#include "HeapSortView.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsRectItem>

HeapSortView::HeapSortView(QWidget *parent) : QGraphicsView(parent), currentStep(0) {
    scene = new QGraphicsScene(this);
    setScene(scene);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HeapSortView::doStep);
}

void HeapSortView::setData(const QVector<int>& data) {
    this->data = data;
    currentStep = 0; // Сброс шагов при установке новых данных

    // ... инициализация элементов сцены на основе данных data
}

void HeapSortView::doStep() {
    if (currentStep < data.size()) {
        heapSort.doStep(data, currentStep);

        // Обновление элементов сцены на основе текущего состояния data
        // ...

        currentStep++;
    } else {
        timer->stop();
        qDebug() << "Sorting complete!";
    }
}
