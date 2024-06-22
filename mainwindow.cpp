#include "mainWindow.h"
#include "heapSortView.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <vector>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), heapSortView_(new HeapSortView(this)) {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QPushButton* sortButton = new QPushButton("Сортировать", this);
    QPushButton* setDataButton = new QPushButton("Задать данные", this);
    QPushButton* generateRandomDataButton = new QPushButton("Случайные данные", this);

    connect(sortButton, &QPushButton::clicked, this, &MainWindow::onSortButtonClicked);
    connect(setDataButton, &QPushButton::clicked, this, &MainWindow::onSetDataButtonClicked);
    connect(generateRandomDataButton, &QPushButton::clicked, this, &MainWindow::onGenerateRandomDataButtonClicked);

    layout->addWidget(heapSortView_);
    layout->addWidget(sortButton);
    layout->addWidget(setDataButton);
    layout->addWidget(generateRandomDataButton);

    setCentralWidget(centralWidget);
    setMinimumSize(800, 600);
}

void MainWindow::onSortButtonClicked() {
    qDebug() << "MainWindow::onSortButtonClicked - Sort button clicked";
    std::vector<int> data = heapSortView_->getData();
    if (data.empty()) {
        qDebug() << "MainWindow::onSortButtonClicked - Data is empty, skipping sort";
        return;
    }

    heapSortView_->visualize();
    heapSortView_->startAnimation();
}

void MainWindow::onSetDataButtonClicked() {
    qDebug() << "MainWindow::onSetDataButtonClicked - Set data button clicked";
    bool ok;
    QString text = QInputDialog::getText(this, tr("Задать данные"),
                                         tr("Введите числа, разделенные пробелами:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList stringList = text.split(' ');
        std::vector<int> data;
        for (const QString& str : stringList) {
            data.push_back(str.toInt());
        }

        qDebug() << "MainWindow::onSetDataButtonClicked - New data set:" << data;

        heapSortView_->setData(data);
        heapSortView_->visualize();
    }
}

void MainWindow::onGenerateRandomDataButtonClicked() {
    bool ok;
    int n = QInputDialog::getInt(this, tr("Случайные данные"),
                                 tr("Введите количество элементов:"), 10, 1, 100, 1, &ok);
    if (ok) {
        heapSortView_->generateRandomData(n);
    }
}
