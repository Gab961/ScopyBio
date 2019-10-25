#include <cstdio>
#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include <QWidget>


int main(int argc, char* argv[])
{
    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return scopyBio.exec();
}
