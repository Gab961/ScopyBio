#include "definition.h"
#include "mainwindow.h"

#include <iostream>
#include <iostream>
#include <cstdlib>

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QIcon>

#include "Model/save_model.h"

#include <filesystem>

using namespace std;

int main(int argc, char* argv[])
{
    //test
    string tmp = "tmp";
    filesystem::create_directory(tmp);
    tmp += separator;
    tmp += std::string("mainDisplay");
    filesystem::create_directory(tmp.c_str());

    string analysePath = "tmp";
    analysePath += separator;
    analysePath += "saveAnalyse";
    filesystem::create_directories(analysePath);

    string pileDisplayPath = "tmp";
    pileDisplayPath += separator;
    pileDisplayPath += "pileDisplay";
    filesystem::create_directories(pileDisplayPath);

    string userAnalysePath = "tmp";
    userAnalysePath += separator;
    userAnalysePath += "saveAnalyse";
    userAnalysePath += separator;
    userAnalysePath += "resultDisplay";
    userAnalysePath += separator;
    userAnalysePath += "user";
    filesystem::create_directories(userAnalysePath);

    QApplication scopyBio(argc, argv);

    MainWindow mainWindow;
    std::string pathOfIcon = "..";
    pathOfIcon += separator;
    pathOfIcon += "..";
    pathOfIcon += separator;
    pathOfIcon += "Resources";
    pathOfIcon += separator;
    pathOfIcon += "Icons";
    pathOfIcon += separator;
    pathOfIcon += "Logo_Scopy.png";

    mainWindow.setWindowIcon(QIcon(pathOfIcon.c_str()));

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-mainWindow.width()) / 2;
    int y = (screenGeometry.height()-mainWindow.height()) / 2;
    mainWindow.move(x, y);

    mainWindow.show();

    return scopyBio.exec();
}
