QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += main.cpp \
        mainWindow.cpp \
        heapSort.cpp \
        heapSortView.cpp

HEADERS += mainWindow.h \
        heapSort.h \
        heapSortView.h

FORMS += \
    mainWindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
