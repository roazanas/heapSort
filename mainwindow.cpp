#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<int> data = {5, 2, 8, 1, 9, 3};
    ui->graphicsView->setData(data);
}

MainWindow::~MainWindow()
{
    delete ui;
}
