#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<int> data = generateRandomData(100, 1, 10000);
    ui->graphicsView->setData(data);
    ui->statusbar->showMessage(QString("Массив из %1 значений").arg(data.length()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<int> MainWindow::generateRandomData(int size, int minValue, int maxValue) {
    QVector<int> data(size);
    for (int &value : data) {
        value = QRandomGenerator::global()->bounded(minValue, maxValue);
    }
    return data;
}
