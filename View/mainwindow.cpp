#include "mainwindow.h"

#include <iostream>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QDialog>
#include <QMenuBar>
#include <QMessageBox>

#include "data_view.h"
#include "pile_view.h"
#include "menu_option.h"
#include "zoom_view.h"
#include "image_view.h"
#include "menu_draw_button.h"
#include "Controler/scopybio_controller.h"

MainWindow::MainWindow(QWidget *parent)
{
    m_scopybioController = new ScopyBio_Controller();

    QDesktopWidget dw;
    int screenWidth = dw.width()*0.7;
    int screenHeight = dw.height()*0.7;
    setMinimumSize(screenWidth, screenHeight);

    createActions();

    m_mainLayout = new QGridLayout();
    m_leftLayout = new QGridLayout();
    m_centerLayout = new QGridLayout();
    m_rightLayout = new QGridLayout();

    m_pileView = new Pile_View(this, m_scopybioController);
    // m_pileView->setFixedSize(screenWidth*0.25, screenHeight*0.5);

    m_options = new menu_option(this);
    // m_options->setFixedSize(screenWidth*0.25, screenHeight*0.25);

    m_tools = new Menu_Draw_Button(this);
    // m_tools->setFixedSize(screenWidth*0.25, screenHeight*0.25);

    m_dataView = new Data_View(this, m_scopybioController);
    m_dataView->setFixedHeight(200);
    m_dataView->setFixedWidth(300);
    m_dataView->setStyleSheet("QLabel { background-color : green;}");

    m_leftLayout->addWidget(m_tools, 0, 0);
    m_leftLayout->addWidget(m_options, 1, 0);
    m_leftLayout->addWidget(m_pileView, 2, 0);

    //Affichage principal des images
    m_imageView = new Image_View(this, m_scopybioController);
    m_imageView->setFixedHeight(476);
    m_imageView->setFixedWidth(514);
    m_imageView->setStyleSheet("QLabel { background-color : blue;}");

    m_centerLayout->addWidget(m_imageView, 0, 0);

    //Affichage de la partie sélectionnée zoomée
    m_zoomView = new Zoom_View(this, m_scopybioController);
    m_zoomView->setFixedHeight(476);
    m_zoomView->setFixedWidth(514);
    m_zoomView->setStyleSheet("QLabel { background-color : red;}");

    m_rightLayout->addWidget(m_dataView, 0, 0);
    m_rightLayout->addWidget(m_zoomView, 1, 0);

    m_mainLayout->addLayout(m_leftLayout, 0, 0);
    m_mainLayout->addLayout(m_centerLayout, 0, 1);
    m_mainLayout->addLayout(m_rightLayout, 0, 2);

    m_window = new QWidget();
    m_window->setLayout(m_mainLayout);
    setCentralWidget(m_window);

    //Envoi du chemin d'une image tif pour charger la pile
    QObject::connect(this, &MainWindow::sendPath, m_pileView, &Pile_View::openFile);

    //Fin de chargement de pile donc affichage de la première image
    QObject::connect(m_pileView, &Pile_View::pileInitDone, this, &MainWindow::showFirstInPile);

    //Demande d'affichage dans la fenêtre principale
    QObject::connect(this,&MainWindow::changeMainPicture,m_imageView,&Image_View::setNewPicture);

    //Demande d'affichage dans la fenêtre de zoom
    QObject::connect(m_imageView,&Image_View::changeZoomedPicture,m_zoomView,&Zoom_View::setNewPicture);

    //Gestion du changement dans la liste
    QObject::connect(m_pileView,&Pile_View::currentRowChanged,this,&MainWindow::changeActualItem);

    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_imageView,&Image_View::processResults,m_dataView,&Data_View::processingResults);
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

void MainWindow::showFirstInPile()
{
    m_scopybioController->saveAsMainDisplay(0);
    emit changeMainPicture();

    update();
}

void MainWindow::changeActualItem()
{
    int indiceEnCours = m_pileView->currentRow();
    m_scopybioController->saveAsMainDisplay(indiceEnCours);
    emit changeMainPicture();
}
