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

public slots: // startVisualization() теперь публичный слот
    void startVisualization();

private:
    std::vector<int> data_;
    QTimer* timer_;
};

#endif // HEAPSORTVIEW_H
