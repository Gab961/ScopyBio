#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include <QWidget>

// commande pour build
// conan install .. --build protobuf --build openexr --build opencv

int main(int argc, char* argv[])
{
    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    std:: cout << "gab il a une maitr yi op" << std::endl;
    return scopyBio.exec();
}
