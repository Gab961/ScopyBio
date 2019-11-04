#include "mainwindow.h"

#include <iostream>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QDialog>
#include <QMenuBar>
#include <QMessageBox>

#include "pile_view.h"
#include "menu_option.h"
#include "menu_draw_button.h"

MainWindow::MainWindow(QWidget *parent)
{
    QDesktopWidget dw;
    int screenWidth = dw.width()*0.7;
    int screenHeight = dw.height()*0.7;
    setMinimumSize(screenWidth, screenHeight);

    createActions();

    m_mainLayout = new QGridLayout();

    m_pileView = new Pile_View(this);
   // m_pileView->setFixedSize(screenWidth*0.25, screenHeight*0.5);

    m_options = new menu_option(this);
   // m_options->setFixedSize(screenWidth*0.25, screenHeight*0.25);

    m_tools = new Menu_Draw_Button(this);

    m_mainLayout->addWidget(m_tools, 0, 0);
    m_mainLayout->addWidget(m_options, 1, 0);
    m_mainLayout->addWidget(m_pileView, 2, 0);

    m_window = new QWidget();
    m_window->setLayout(m_mainLayout);
    setCentralWidget(m_window);

    QObject::connect(this, &MainWindow::sendPath, m_pileView, &Pile_View::openFile);
}


void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.tiff *.tif)"));
    std::string path = fileName.toLocal8Bit().constData();

    emit sendPath(path);
}

void MainWindow::saveAs()
{
    //TODO
}

void MainWindow::save()
{

}

void MainWindow::aboutUs()
{
    QMessageBox::about(this, tr("About ScopyBio"),
            tr("<p><b>ScopyBio</b> is a software developed by Mouget Gabriel, Saout Thomas,"
               " Pigache Bastien and Mohr Anaïs from the UFR des Sciences, Angers."
               " It allows to do some operations on .tiff files to compare the different"
               " images with some options."
               " This program was developed with Qt and C++ language.</p>"));
}

void MainWindow::howToUse()
{
    // TODO
    QMessageBox::about(this, tr("How to use ScopyBio"),
            tr("<p>Blibloup</p>"));
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    m_loadFile = new QAction(tr("&Open..."), this);
    m_loadFile->setShortcut(tr("&Ctrl+N"));
    QObject::connect(m_loadFile, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(m_loadFile);

    // TODO
    m_saveFile = new QAction(tr("&Save"), this);
    QObject::connect(m_saveFile, &QAction::triggered, this, &MainWindow::save);
    m_saveFile->setEnabled(false);
    m_saveFile->setShortcut(tr("&Ctrl+S"));
    fileMenu->addAction(m_saveFile);

    m_saveAs = new QAction(tr("&Save as..."), this);
    QObject::connect(m_saveAs, &QAction::triggered, this, &MainWindow::saveAs);
    m_saveAs->setEnabled(false);
    fileMenu->addAction(m_saveAs);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    m_aboutUs = new QAction(tr("&About us..."), this);
    QObject::connect(m_aboutUs, &QAction::triggered, this, &MainWindow::aboutUs);
    helpMenu->addAction(m_aboutUs);

    m_howToUse = new QAction(tr("&How to use..."), this);
    QObject::connect(m_howToUse, &QAction::triggered, this, &MainWindow::howToUse);
    helpMenu->addAction(m_howToUse);
}

void MainWindow::updateSaveAs()
{
    m_saveAs->setEnabled(true);
}

void MainWindow::updateSave()
{
    m_saveFile->setEnabled(true);
}
