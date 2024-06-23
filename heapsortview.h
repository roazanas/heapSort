#ifndef HEAPSORTVIEW_H
#define HEAPSORTVIEW_H

#include <QGraphicsView>
#include <vector>
#include <QTimer>

class HeapSortView : public QGraphicsView {
    Q_OBJECT
public:
    explicit HeapSortView(QWidget* parent = nullptr);
    void setData(const std::vector<int>& data);
    const std::vector<int>& getData() const;
    void visualize();

public slots:
    void startVisualization();
    void onSortedIndexChanged(int index);
    void setIndexesToSwap(int index1, int index2);
    void resetColors();

private:
    std::vector<int> data_;
    QTimer* timer_;

    size_t sortedIndex_;
    int highlightedIndex1_;
    int highlightedIndex2_;

};

#endif // HEAPSORTVIEW_H
