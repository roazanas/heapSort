#include "HeapSortView.h"
#include <QDebug>
#include <QResizeEvent>
#include <algorithm>

QSize HeapSortView::globalDeltaSize = QSize(0, 0);

HeapSortView::HeapSortView(QWidget *parent) : QGraphicsView(parent), currentStep(0) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setSceneRect(0, 0, width() - 2, height() - 2);

    timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &HeapSortView::doStep);
}

void HeapSortView::setData(const QVector<int>& data) {
    this->data = data;
    currentStep = 0;
    visualData.clear();
    scene->clear();

    updateRectangles(QSize(0, 0));

    setSceneRect(scene->itemsBoundingRect());
    timer->start();
}

void HeapSortView::doStep() {
    if (currentStep < data.size()) {
        heapSort.sort(data);
        updateRectangles();
        currentStep = data.size();
        qDebug() << "Sorting complete!";
        timer->stop();
    }
}

void HeapSortView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    updateRectangles(event->size()-event->oldSize());
    setSceneRect(scene->itemsBoundingRect());
}

void HeapSortView::updateRectangles(QSize deltaSize) {
    globalDeltaSize += deltaSize;
    // Удаляем предыдущие элементы сцены, если они есть
    for (auto *item : visualData) {
        scene->removeItem(item);
        delete item;
    }
    visualData.clear();

    // Расчет параметров расположения
    int spacing = 1;
    int numRects = data.size();
    int availableWidth = width() - (numRects + 1) * spacing;
    int rectWidth = availableWidth / numRects;

    // Находим максимальное значение для расчета пропорций
    int maxValue = *std::max_element(data.begin(), data.end());

    // Создание и добавление прямоугольников в сцену
    for (int i = 0; i < data.size(); ++i) {
        int rectHeight = data[i] * (height() - spacing) / maxValue;
        QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, rectWidth, rectHeight);
        rect->setBrush(Qt::blue);
        rect->setPen(QPen(Qt::transparent));
        visualData.append(rect);
        rect->setPos((i * (rectWidth + spacing)) + spacing - globalDeltaSize.width()/2,
                     height() - rectHeight - spacing - globalDeltaSize.height()/2);
        scene->addItem(rect);
    }

    // Обновление сцены
    scene->update();
}
