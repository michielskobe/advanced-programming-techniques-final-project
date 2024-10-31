#include "mainwindow.h"
#include "world.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    World world;

    QString str = ":/images/test.jpg";
    world.createWorld(str,1,1,0.25f);
    // World::createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio);

    return a.exec();
}
