#include "mainwindow.h"

#include <iostream>
#include <iostream>
#include <cstdlib>

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QFontDatabase>

#define _ITERATOR_DEBUG_LEVEL 1

using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
    create_directory("tmp/mainDisplay");

    //test
    std::string tmp = "tmp";
    boost::filesystem::create_directory(tmp);
    tmp += separator;
    tmp += std::string("mainDisplay");
    boost::filesystem::create_directory(tmp.c_str());

    QApplication scopyBio(argc, argv);

    QFontDatabase database;

    database.addApplicationFont("fonts/dejavu-fonts-ttf-2.37/ttf/DejaVuSerif.ttf");

    QFont f = database.font("DejaVuSerif", "normal", 12);
    scopyBio.setFont(f);

    MainWindow mainWindow;

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-mainWindow.width()) / 2;
    int y = (screenGeometry.height()-mainWindow.height()) / 2;
    mainWindow.move(x, y);

    mainWindow.show();

    return scopyBio.exec();
}

