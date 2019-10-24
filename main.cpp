#include <cstdio>
#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include <QWidget>

#define cimg_use_tiff
#define cimg_use_png
#include "CImg.h"

int main(int argc, char* argv[])
{
    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    std:: cout << "gab il a une maitr yi op" << std::endl;
    return scopyBio.exec();
}
