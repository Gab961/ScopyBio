#include "mainwindow.h"

#include <iostream>
#include <iostream>
#include <cstdlib>

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>

#include "boost/filesystem.hpp"
#include "Model/save_model.h"

using namespace std;

int main(int argc, char* argv[])
{
    std::string tmp = "tmp";
    boost::filesystem::create_directory(tmp);
    tmp += separator;
    tmp += std::string("mainDisplay");
    boost::filesystem::create_directory(tmp.c_str());

    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-mainWindow.width()) / 2;
    int y = (screenGeometry.height()-mainWindow.height()) / 2;
    mainWindow.move(x, y);

    mainWindow.show();

    return scopyBio.exec();
}

