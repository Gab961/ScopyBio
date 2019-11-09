#include "mainwindow.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>

#define _ITERATOR_DEBUG_LEVEL 1

using namespace std;

int main(int argc, char* argv[])
{
    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-mainWindow.width()) / 2;
    int y = (screenGeometry.height()-mainWindow.height()) / 2;
    mainWindow.move(x, y);

    mainWindow.show();

    return scopyBio.exec();
}

