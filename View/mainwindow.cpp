#include "mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow()
{
    QDesktopWidget dw;

    int screenWidth = dw.width();
    int screenHeight = dw.height();

    setMinimumSize(screenWidth*0.7, screenHeight*0.7);
}

