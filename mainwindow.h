#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "heapSortView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void onSortButtonClicked();
    void onSetDataButtonClicked();
    void onGenerateRandomDataButtonClicked();

private:
    HeapSortView* heapSortView_;
};

#endif // MAINWINDOW_H
