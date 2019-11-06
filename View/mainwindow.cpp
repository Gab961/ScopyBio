#include "mainwindow.h"

#include <iostream>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QDialog>
#include <QMenuBar>
#include <QMessageBox>

#include "layer_view.h"
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

    buildView();

    createActions();

    connections();
}

void MainWindow::buildView()
{
    QDesktopWidget dw;
    int screenWidth = dw.width()*0.7;
    int screenHeight = dw.height()*0.7;
    setMinimumSize(screenWidth, screenHeight);

    m_mainLayout = new QGridLayout();
    m_leftLayout = new QGridLayout();
    m_centerLayout = new QGridLayout();
    m_rightLayout = new QGridLayout();
    m_pileLayerLayout = new QGridLayout();
    m_buttonLayout = new QGridLayout();

    m_zoomView = new Zoom_View(this, m_scopybioController);
    m_zoomView->setFixedSize(screenWidth*0.20, screenHeight*0.45);

    m_tools = new Menu_Draw_Button(this);
    m_tools->setFixedSize(screenWidth*0.20, screenHeight*0.17);

    m_options = new menu_option(this, m_scopybioController);
    m_options->setFixedSize(screenWidth*0.20, screenHeight*0.30);

    m_leftLayout->addWidget(m_zoomView, 0, 0);
    m_leftLayout->addWidget(m_tools, 1, 0);
    m_leftLayout->addWidget(m_options, 2, 0);


    //Affichage principal des images
    m_imageView = new Image_View(this, m_scopybioController);
    m_imageView->setFixedSize(screenWidth*0.50, screenHeight*0.95);

    m_openLoop = new QPushButton("Open loop", this);
    m_openLoop->setMaximumWidth(screenWidth*0.15);

    m_openCompare = new QPushButton("Compare", this);
    m_openCompare->setMaximumWidth(screenWidth*0.15);

    m_buttonLayout->addWidget(m_openLoop, 0, 0);
    m_buttonLayout->addWidget(m_openCompare, 0, 1);

    m_centerLayout->addWidget(m_imageView, 0, 0);
    m_centerLayout->addLayout(m_buttonLayout, 1, 0);

    // Datas graph
    m_dataView = new Data_View(this, m_scopybioController);
    m_dataView->setFixedSize(screenWidth*0.25, screenHeight*0.45);

    m_pileView = new Pile_View(this, m_scopybioController);
    m_pileView->setFixedSize(screenWidth*0.15, screenHeight*0.45);

    m_layerView = new LayerView(this, m_scopybioController);
    m_layerView->setFixedSize(screenWidth*0.1, screenHeight*0.45);

    m_pileLayerLayout->addWidget(m_pileView, 0, 0);
    m_pileLayerLayout->addWidget(m_layerView, 0, 1);

    m_rightLayout->addWidget(m_dataView, 0, 0);
    m_rightLayout->addLayout(m_pileLayerLayout, 1, 0);

    m_mainLayout->addLayout(m_leftLayout, 0, 0);
    m_mainLayout->addLayout(m_centerLayout, 0, 1);
    m_mainLayout->addLayout(m_rightLayout, 0, 2);

    m_window = new QWidget();
    m_window->setLayout(m_mainLayout);
    setCentralWidget(m_window);
}

void MainWindow::connections()
{
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

    //Demande d'affichage de l'image principale depuis menuOption
    QObject::connect(m_options,&menu_option::refreshMainDisplay,m_imageView,&Image_View::setNewPicture);

    //Demande de modification dans la liste depuis le graphique
    QObject::connect(m_dataView,&Data_View::graphClic,m_pileView,&Pile_View::changeToElement);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "../../Data",
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
    m_scopybioController->saveCurrent(indiceEnCours);
    m_scopybioController->saveAsMainDisplay(indiceEnCours);
    emit changeMainPicture();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    int screenWidth = size().width();
    int screenHeight = size().height();

    m_zoomView->setFixedSize(screenWidth*0.20, screenHeight*0.45);

    m_tools->setFixedSize(screenWidth*0.20, screenHeight*0.17);

    m_options->setFixedSize(screenWidth*0.20, screenHeight*0.30);

    m_imageView->setFixedSize(screenWidth*0.50, screenHeight*0.95);

    m_dataView->setFixedSize(screenWidth*0.25, screenHeight*0.45);

    m_layerView->setFixedSize(screenWidth*0.1, screenHeight*0.45);

    m_pileView->setFixedSize(screenWidth*0.15, screenHeight*0.45);


    if (m_scopybioController->fileReady())
    {
        emit changeMainPicture();
        emit changeZoomedPicture();
    }

    update();
}
