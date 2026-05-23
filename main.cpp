#include "mainwindow.h"

#include <QPen>
#include <QFont>
#include <QtMath>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
