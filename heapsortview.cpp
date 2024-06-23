#include "heapSortView.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <algorithm>
#include <QDebug>

HeapSortView::HeapSortView(QWidget* parent) : QGraphicsView(parent), timer_(new QTimer(this)) {
    setScene(new QGraphicsScene(this));
}

void HeapSortView::setData(const std::vector<int>& data) {
    data_ = data;
    qDebug() << "HeapSortView::setData - Установлены данные:" << data_;
    visualize();
}

const std::vector<int>& HeapSortView::getData() const {
    return data_;
}

void HeapSortView::visualize() {
    scene()->clear();

    int width = this->width();
    int height = this->height();
    scene()->setSceneRect(0, 0, width, height);

    qDebug() << "HeapSortView::visualize - Ширина сцены:" << width << ", высота:" << height;

    if (data_.empty()) {
        qDebug() << "HeapSortView::visualize - Данные пусты, нечего визуализировать";
        return;
    }

    int barWidth = std::floor(static_cast<double>(width) / data_.size());
    qDebug() << "HeapSortView::visualize - Ширина полосы:" << barWidth;

    for (size_t i = 0; i < data_.size(); ++i) {
        int barHeight = static_cast<int>(height * (static_cast<double>(data_[i]) / *std::max_element(data_.begin(), data_.end())));
        QGraphicsRectItem* bar = new QGraphicsRectItem(i * barWidth, height - barHeight, barWidth-5, barHeight-5);
        if (0 <= sortedIndex_ && sortedIndex_ <= i) {
            bar->setBrush(QBrush(QColor(144, 238, 144)));
        } else {
            bar->setBrush(QBrush(QColor(142, 45, 197)));
        }
        scene()->addItem(bar);
    }
    setSceneRect(scene()->itemsBoundingRect());
}

void HeapSortView::startVisualization() {
    qDebug() << "HeapSortView::startVisualization - Запуск визуализации";
    visualize();
}

void HeapSortView::onSortedIndexChanged(int index) {
    sortedIndex_ = index;
    visualize();
}
