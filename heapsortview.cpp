#include "heapSortView.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <algorithm>
#include <QDebug>

HeapSortView::HeapSortView(QWidget* parent) : QGraphicsView(parent), timer_(new QTimer(this)), highlightedIndex1_(-1), highlightedIndex2_(-1) {
    setScene(new QGraphicsScene(this));
}

void HeapSortView::setIndexesToSwap(int index1, int index2){
    qDebug() << "HeapSortView::setIndexesToSwap - Обмен элементов" <<index1 <<"и" <<index2;
    highlightedIndex1_ = index1;
    highlightedIndex2_ = index2;
    visualize();
}

void HeapSortView::resetColors() {
    highlightedIndex1_ = -1;
    highlightedIndex2_ = -1;
    for (auto item : scene()->items()) {
        if (auto bar = qgraphicsitem_cast<QAbstractGraphicsShapeItem*>(item)) {
            QLinearGradient gradient(width(), 0, 0, height());
            gradient.setColorAt(0, QColor(237, 145, 191));
            gradient.setColorAt(0.5, QColor(237, 208, 145));
            gradient.setColorAt(1, QColor(144, 238, 144));
            bar->setBrush(QBrush(gradient));
            scene()->update();
        }
    }
    finished = true;
}

void HeapSortView::setData(const std::vector<int>& data) {
    finished = false;
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
        if (i == highlightedIndex1_ || i == highlightedIndex2_) {
            bar->setBrush(QBrush(QColor(237, 145, 191)));
        } else if (0 <= sortedIndex_ && sortedIndex_ <= i) {
            bar->setBrush(QBrush(QColor(144, 238, 144)));
        } else {
            bar->setBrush(QBrush(QColor(237, 208, 145)));
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

void HeapSortView::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);
    if (finished) visualize();
    resetColors();
}
