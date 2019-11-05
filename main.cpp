#include <cstdio>
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <cstdlib>

#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return scopyBio.exec();
}

