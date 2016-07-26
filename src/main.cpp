#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QtGui/QSurfaceFormat>
#include "TriangleWindow.h"

int main(int argc, char *argv[]) {

//    QApplication app(argc, argv);
//
//    QWidget window;
//
//    window.resize(250, 150);
//    window.setWindowTitle("Hello Qt");
//    window.show();
//
//    return app.exec();


    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();



}