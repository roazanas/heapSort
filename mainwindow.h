#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "heapsort.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onSortButtonClicked();
    void onSetDataButtonClicked();
    void onGenerateRandomDataButtonClicked();
    void onMessageSent(const QString &message);
    void updateStatusBar(int arraySize, int iterations, int comparisons, int arrayAccesses);
    void onSortedIndexChanged(int index);
    void on_animationDelaySlider_valueChanged(int value);
    void onSortEnded();

private:
    Ui::MainWindow* ui;
    HeapSort* heapSorter_;
};

#endif // MAINWINDOW_H
