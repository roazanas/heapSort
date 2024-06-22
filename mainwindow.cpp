#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>
#include <vector>
#include "heapSort.h"
#include <random>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    heapSorter_(new HeapSort(this)) {
    ui->setupUi(this);

    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::onSortButtonClicked);
    connect(ui->setDataButton, &QPushButton::clicked, this, &MainWindow::onSetDataButtonClicked);
    connect(ui->generateRandomDataButton, &QPushButton::clicked, this, &MainWindow::onGenerateRandomDataButtonClicked);
    connect(heapSorter_, &HeapSort::dataChanged, ui->graphicsView, &HeapSortView::setData);
    connect(heapSorter_, &HeapSort::messageSent, this, &MainWindow::onMessageSent);

    qDebug() << "MainWindow::MainWindow - Главное окно инициализировано";
}

MainWindow::~MainWindow() {
    delete ui;
    qDebug() << "MainWindow::~MainWindow - Главное окно уничтожено";
}

void MainWindow::onSortButtonClicked() {
    qDebug() << "MainWindow::onSortButtonClicked - Нажата кнопка сортировки";
    if (ui->graphicsView->getData().empty()) {
        qDebug() << "MainWindow::onSortButtonClicked - Данные пусты, пропуск сортировки";
        return;
    }

    std::vector<int> data = ui->graphicsView->getData();
    heapSorter_->sort(data);
}

void MainWindow::onSetDataButtonClicked() {
    qDebug() << "MainWindow::onSetDataButtonClicked - Нажата кнопка задания данных";
    bool ok;
    QString text = QInputDialog::getText(this, tr("Ввод данных"),
                                         tr("Введите числа, разделенные пробелами:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        QStringList stringList = text.split(' ');
        std::vector<int> data;
        for (const QString& str : stringList) {
            data.push_back(str.toInt());
        }

        qDebug() << "MainWindow::onSetDataButtonClicked - Новые данные установлены:" << data;

        ui->graphicsView->setData(data);
        ui->graphicsView->visualize();
    }
}

void MainWindow::onGenerateRandomDataButtonClicked() {
    qDebug() << "MainWindow::onGenerateRandomDataButtonClicked - Нажата кнопка генерации случайных данных";
    bool ok;
    int n = QInputDialog::getInt(this, tr("Генерация случайных данных"),
                                 tr("Введите количество элементов:"), 20, 1, 200, 1, &ok);
    if (ok) {
        std::vector<int> data(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1000, 10000);

        for (int& val : data) {
            val = dis(gen);
        }

        qDebug() << "MainWindow::onGenerateRandomDataButtonClicked - Сгенерированы случайные данные:" << data;

        ui->graphicsView->setData(data);
        ui->graphicsView->visualize();
    }
}

void MainWindow::onMessageSent(const QString& message) {
    ui->listWidget->addItem(message);
}
