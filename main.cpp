#include <cstdio>
#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include <QWidget>
#include <cstdlib>

// include pour jsoncpp
#include <json/json.h>
#include <fstream>

#include <scopybio_controller.h>

using namespace std;

int main(int argc, char* argv[])
{
    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return scopyBio.exec();
}
