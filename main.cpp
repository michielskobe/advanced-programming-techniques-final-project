#include "mainwindow.h"
#include "world.h"
#include <iostream>

#include <QApplication>
#include <QtDebug>
#include <QtLogging>
#include <QMetaObject>

int main(int argc, char *argv[])
{
    // debug stuff
    qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec(); // Qt Event loop!
}
