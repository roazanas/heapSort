
#include "heapSortView.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <algorithm>
#include <QDebug>

HeapSortView::HeapSortView(QWidget* parent) : QGraphicsView(parent), heapSorter_(nullptr), timer_(new QTimer(this)) {
    setScene(new QGraphicsScene(this));
    connect(timer_, &QTimer::timeout, this, &HeapSortView::animateSort);
    setMinimumSize(800, 600);
}

void HeapSortView::setData(const std::vector<int>& data) {
    qDebug() << "HeapSortView::setData - Setting data:" << data;
    data_ = data;
    delete heapSorter_;
    heapSorter_ = new HeapSort(data_);
}

const std::vector<int>& HeapSortView::getData() const {
    return data_;
}

void HeapSortView::visualize() {
    scene()->clear();

    int width = static_cast<int>(this->width());
    int height = static_cast<int>(this->height());
    scene()->setSceneRect(0, 0, width, height);

    qDebug() << "HeapSortView::visualize - Scene width:" << width << ", height:" << height;

    if (data_.empty()) {
        qDebug() << "HeapSortView::visualize - Data is empty, nothing to visualize";
        return;
    }

    int barWidth = width / static_cast<int>(data_.size());
    qDebug() << "HeapSortView::visualize - Bar width:" << barWidth;

    for (size_t i = 0; i < data_.size(); ++i) {
        int barHeight = static_cast<int>(height * (static_cast<double>(data_[i]) / *std::max_element(data_.begin(), data_.end())));
        qDebug() << "HeapSortView::visualize - Drawing bar" << i << "with height" << barHeight;
        QGraphicsRectItem* bar = new QGraphicsRectItem(i * barWidth, height - barHeight, barWidth, barHeight);
        bar->setBrush(QBrush(Qt::blue));
        scene()->addItem(bar);
    }
}

void HeapSortView::animateSort() {
    qDebug() << "HeapSortView::animateSort - Performing sort step";
    if (!heapSorter_->step()) {
        qDebug() << "HeapSortView::animateSort - Sorting finished";
        stopAnimation();
        return;
    }
    qDebug() << "HeapSortView::animateSort - Current data:" << data_;
    visualize();
}

void HeapSortView::startAnimation() {
    qDebug() << "HeapSortView::startAnimation - Starting animation";
    timer_->start(500);
}

void HeapSortView::stopAnimation() {
    qDebug() << "HeapSortView::stopAnimation - Stopping animation";
    timer_->stop();
}
