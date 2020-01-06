#include "mainwindow.h"

#include <iostream>
#include <filesystem>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QDialog>
#include <QMenuBar>
#include <QMessageBox>

#include "compare_popup.h"
#include "loop_view.h"
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

    createView();

    createActions();

    connections();
}

void MainWindow::createView()
{
    QDesktopWidget dw;
    int screenWidth = dw.width()*0.7;
    int screenHeight = dw.height()*0.7;
    setMinimumSize(screenWidth, screenHeight);

    m_loopWindow = new LoopView(this, m_scopybioController);
    m_comparePopup = new ComparePopup(this, m_scopybioController);

    m_mainLayout = new QGridLayout();
    m_leftLayout = new QGridLayout();
    m_centerLayout = new QGridLayout();
    m_rightLayout = new QGridLayout();
    m_pileLayerLayout = new QGridLayout();
    m_buttonLayout = new QGridLayout();

    m_zoomView = new Zoom_View(this, m_scopybioController);
    m_zoomView->setFixedSize(screenWidth*0.20, screenHeight*0.45);

    m_tools = new Menu_Draw_Button(this, m_scopybioController);
    m_tools->setFixedSize(screenWidth*0.20, 100);

    m_options = new menu_option(this, m_scopybioController);
    m_options->setFixedSize(screenWidth*0.20, screenHeight*0.47 - 100);

    m_leftLayout->addWidget(m_zoomView, 0, 0);
    m_leftLayout->addWidget(m_tools, 1, 0);
    m_leftLayout->addWidget(m_options, 2, 0);

    m_imageView = new Image_View(this, m_scopybioController);
    m_imageView->setFixedSize(screenWidth*0.50, screenHeight*0.95);

    m_centerLayout->addWidget(m_imageView, 0, 0);

    m_dataView = new Data_View(this, m_scopybioController);
    m_dataView->setFixedSize(screenWidth*0.25, screenHeight*0.45);

    m_pileView = new Pile_View(this, m_scopybioController);
    m_pileView->setFixedSize(screenWidth*0.15, screenHeight*0.45);

    m_layerView = new LayerView(this, m_scopybioController);
    m_layerView->setFixedSize(screenWidth*0.1, screenHeight*0.45);

    m_pileLayerLayout->addWidget(m_pileView, 0, 0);
    m_pileLayerLayout->addWidget(m_layerView, 0, 1);

    m_layer = new QGroupBox("Layers", this);
    m_layer->setLayout(m_pileLayerLayout);

    m_rightLayout->addWidget(m_dataView, 0, 0);
    m_rightLayout->addWidget(m_layer, 1, 0);

    m_mainLayout->addLayout(m_leftLayout, 0, 0);
    m_mainLayout->addLayout(m_centerLayout, 0, 1);
    m_mainLayout->addLayout(m_rightLayout, 0, 2);

    m_window = new QWidget();
    m_window->setLayout(m_mainLayout);
    setCentralWidget(m_window);

    m_options->setEnabled(false);
    m_tools->setEnabled(false);
    m_imageView->setEnabled(false);
    m_zoomView->setEnabled(false);
    m_dataView->setEnabled(false);
    m_layer->setEnabled(false);
}

void MainWindow::connections()
{
    //Envoi du chemin d'une image tif pour charger la pile
    QObject::connect(this, &MainWindow::sendPath, m_pileView, &Pile_View::openFile);

    //Envoi du chemin d'une image tif pour charger la pile
    QObject::connect(this, &MainWindow::sendPathProjet, this, &MainWindow::openProject);

    //Fin de chargement de pile donc affichage de la première image
    QObject::connect(m_pileView, &Pile_View::pileInitDone, this, &MainWindow::showFirstInPile);

    //Demande d'affichage dans la fenêtre principale
    QObject::connect(this, &MainWindow::changeMainPicture, m_imageView, &Image_View::setNewPicture);

    //Demande d'affichage dans la fenêtre de zoom
    QObject::connect(m_imageView, &Image_View::changeZoomedPicture, m_zoomView, &Zoom_View::setNewPicture);
    QObject::connect(this, &MainWindow::changeZoomedPicture, m_zoomView, &Zoom_View::setPictureFromFile);

    //Gestion du changement dans la liste
    QObject::connect(m_pileView, &Pile_View::currentRowChanged, this, &MainWindow::changeActualItem);

    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_imageView, &Image_View::processResults, m_dataView, &Data_View::processingResults);

    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_zoomView, &Zoom_View::processResultsFromZoom, m_imageView, &Image_View::askProcessFromZoom);

    //Demande d'affichage de l'image principale depuis menuOption
    QObject::connect(m_options, &menu_option::refreshMainDisplay, m_imageView, &Image_View::setNewPicture);

    //Demande de modification dans la liste depuis le graphique
    QObject::connect(m_dataView, &Data_View::graphClic, m_pileView, &Pile_View::changeToElement);

    //Prise en compte du prochain clic dans le zoom
    QObject::connect(m_tools, &Menu_Draw_Button::waitingForZoomClick, m_zoomView, &Zoom_View::readyForClick);

    //Prise en compte du prochain clic dans l'image view
    QObject::connect(m_tools, &Menu_Draw_Button::waitingForZoomClick, m_imageView, &Image_View::readyForPipetteClick);

    //Prise en compte des clics dans l'imageView pour le dessin au crayon
    QObject::connect(m_tools, &Menu_Draw_Button::readyToDrawPen, m_imageView, &Image_View::readyForPenDraw);

    //Prise en compte des clics dans l'imageView pour le dessin au crayon
    QObject::connect(m_tools, &Menu_Draw_Button::penCanceled, m_imageView, &Image_View::cancelPenDraw);

    //Changement curseur quand bouton pipette actif
    QObject::connect(m_tools, &Menu_Draw_Button::waitingForZoomClick, this, &MainWindow::setCursorPipetteActive);

    //Pipette annulée
    QObject::connect(m_tools, &Menu_Draw_Button::pipetteCanceled, this, &MainWindow::setCursorPipetteDisabled);

    //Changement curseur quand clic pipette
    QObject::connect(m_imageView, &Image_View::pipetteClicked, this, &MainWindow::setCursorPipetteDisabled);

    //Changement curseur quand clic pipette
    QObject::connect(m_zoomView, &Zoom_View::pipetteClicked, this, &MainWindow::setCursorPipetteDisabled);

    //Refresh du zoom sans sélection par l'utilisateur
    QObject::connect(m_imageView, &Image_View::userAnalyseReady, m_zoomView, &Zoom_View::enableDisplay);
    QObject::connect(m_imageView, &Image_View::userAnalyseReady, m_dataView, &Data_View::enableDisplay);

    //Gestion premier clic
    QObject::connect(m_imageView, &Image_View::changeZoomPicture, m_zoomView, &Zoom_View::setPictureFromFile);
    QObject::connect(m_imageView, &Image_View::changeGraphPicture, m_dataView, &Data_View::setGraphFromFile);

    //Mise a jour graph au clic sur le zoom
    QObject::connect(m_zoomView, &Zoom_View::changeGraphPicture, m_dataView, &Data_View::setGraphFromFile);

    //Clear de la vue du Zoom
    QObject::connect(this, &MainWindow::clearZoomView, m_zoomView, &Zoom_View::resetZoomView);

    //Clear de la vue du Data
    QObject::connect(this, &MainWindow::clearDataView, m_dataView, &Data_View::resetDataView);
    QObject::connect(m_imageView, &Image_View::clearDataView, m_zoomView, &Zoom_View::resetZoomView);

    //Démarrage d'une analyse complete
    QObject::connect(m_options, &menu_option::askFullAnalysis, this, &MainWindow::startFullAnalysis);

    //Démarrage d'une analyse de selection
    QObject::connect(m_options, &menu_option::askForUserAnalyse, m_imageView, &Image_View::startUserAnalysis);

    //Mise à jour du bouton d'analyse locale
    QObject::connect(m_imageView, &Image_View::activateLocalAnalyse, m_options, &menu_option::activateLocalAnalyse);
    QObject::connect(m_imageView, &Image_View::desactivateLocalAnalyse, m_options, &menu_option::desactivateLocalAnalyse);

    // Met à jour la vue des options en fonction de l'outil sélectionné
    QObject::connect(m_tools, &Menu_Draw_Button::penClicked, m_options, &menu_option::pen);
    QObject::connect(m_tools, &Menu_Draw_Button::shapesClicked, m_options, &menu_option::shapes);
    QObject::connect(m_tools, &Menu_Draw_Button::textClicked, m_options, &menu_option::text);
    QObject::connect(m_tools, &Menu_Draw_Button::eraserClicked, m_options, &menu_option::eraser);
    QObject::connect(m_tools, &Menu_Draw_Button::pipetteClicked, m_options, &menu_option::pipette);
    QObject::connect(m_tools, &Menu_Draw_Button::filtersClicked, m_options, &menu_option::filters);
    QObject::connect(m_tools, &Menu_Draw_Button::analysisClicked, m_options, &menu_option::analysis);

    // Met à jour les calques en fonction de l'image sélectionnée
    QObject::connect(m_pileView, &Pile_View::rowClicked, m_layerView, &LayerView::loadLayers);

    // Met à jour l'affichage de l'image après chaque action effectuée dans le layer_view (suppression, création, affichage)
    QObject::connect(m_layerView, &LayerView::actionDoneWithLayer, this, &MainWindow::recreateMainDisplay);

    //Mise à jour de l'interface lorsque les thread d'analyse ont terminé leurs actions
    QObject::connect(m_scopybioController, &ScopyBio_Controller::userAnalysisEnded, this, &MainWindow::userAnalysisEnded);
    QObject::connect(m_scopybioController, &ScopyBio_Controller::fullAnalysisEnded, this, &MainWindow::fullAnalysisEnded);
}

void MainWindow::closeEvent(QCloseEvent* e)
{
    std::filesystem::remove_all(std::filesystem::path("tmp"));
    QMainWindow::closeEvent(e);
}

void MainWindow::open()
{
    std::string path = "";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "../../Resources/Data",
                                                    tr("Images (*.tiff *.tif *.scb)"));
    path = fileName.toLocal8Bit().constData();

    if(path != "") {
        //Ouverture d'un fichier projet
        if (path.substr(path.size()-3, path.size()) == "scb")
        {
            //TODO Adapter pour séparateur
            //std::string directoryPath = path.substr(0,path.find_last_of('/'));

            m_scopybioController->changeSavePaths(path.substr(0,path.find_last_of(separator)));
            m_saveFile->setEnabled(true);


            std::string tifPath = path.substr(0, path.size()-3) + "tif";
            emit sendPath(tifPath);

            //TODO Gerer séparator multi os
            emit sendPathProjet(path);
        }
        else
            emit sendPath(path);

        m_options->setEnabled(true);
        m_tools->setEnabled(true);
        m_imageView->setEnabled(true);
        m_zoomView->setEnabled(true);
        m_dataView->setEnabled(true);
        m_layer->setEnabled(true);
        m_loop->setEnabled(true);
        m_compare->setEnabled(true);
        m_saveAs->setEnabled(true);
    }
}

void MainWindow::saveAs()
{
    std::string path = "";
    QString directoryName = QFileDialog::getExistingDirectory(this, tr("Save Directory"),
                                                              "../../Resources/Data",
                                                              QFileDialog::ShowDirsOnly
                                                              | QFileDialog::DontResolveSymlinks);
    if (directoryName != "")
    {
        path = directoryName.toLocal8Bit().constData();

        m_scopybioController->save_as(path);
    }
}

void MainWindow::save()
{
    m_scopybioController->save();
}

void MainWindow::aboutUs()
{
    QMessageBox::about(this, tr("About ScopyBio"),
                       tr("<p><b>ScopyBio</b> is a software developed by Mouget Gabriel, Saout Thomas,"
                          " Pigache Bastien and Mohr Anaïs from the UFR des Sciences, Angers."
                          " It allows to do some operations on .tiff files to compare the different"
                          " images with some options."
                          " This program was developed with Qt and C++ language."
                          ""
                          "Icons made by Freepik, Pixel Perfect from www.flaticon.com.</p>"));
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

    m_saveAs = new QAction(tr("Sa&ve as..."), this);
    QObject::connect(m_saveAs, &QAction::triggered, this, &MainWindow::saveAs);
    m_saveAs->setEnabled(false);
    fileMenu->addAction(m_saveAs);

    ////

    //TODO faire attention si y a plus d'action faut griser
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    m_undo = new QAction(tr("&Undo..."), this);
    m_undo->setShortcut(tr("&Ctrl+Z"));
    QObject::connect(m_undo, &QAction::triggered, this, &MainWindow::undo);
    editMenu->addAction(m_undo);

    m_redo = new QAction(tr("&Redo"), this);
    QObject::connect(m_redo, &QAction::triggered, this, &MainWindow::redo);
    m_redo->setShortcut(tr("&Ctrl+Y"));
    editMenu->addAction(m_redo);

    /////

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    m_aboutUs = new QAction(tr("&About us..."), this);
    QObject::connect(m_aboutUs, &QAction::triggered, this, &MainWindow::aboutUs);
    helpMenu->addAction(m_aboutUs);

    m_howToUse = new QAction(tr("&How to use..."), this);
    QObject::connect(m_howToUse, &QAction::triggered, this, &MainWindow::howToUse);
    helpMenu->addAction(m_howToUse);

    QMenu *imageMenu = menuBar()->addMenu(tr("&Image"));

    m_compare = new QAction(tr("&Compare"), this);
    QObject::connect(m_compare, &QAction::triggered, m_comparePopup, &ComparePopup::createComparePopup);
    imageMenu->addAction(m_compare);
    m_compare->setEnabled(false);

    m_loop = new QAction(tr("&Loop"), this);
    QObject::connect(m_loop, &QAction::triggered, m_loopWindow, &LoopView::createLoopView);
    imageMenu->addAction(m_loop);
    m_loop->setEnabled(false);
}

void MainWindow::updateSaveAs()
{
    m_saveAs->setEnabled(true);
}

void MainWindow::updateSave()
{
    m_saveFile->setEnabled(true);
}


void MainWindow::undo()
{
    m_scopybioController->undoAction();
    recreateMainDisplay();
}


void MainWindow::redo()
{
    m_scopybioController->redoAction();
    recreateMainDisplay();
}

void MainWindow::openProject(std::string path)
{
    m_scopybioController->openProject(path);
}

void MainWindow::showFirstInPile()
{
    m_scopybioController->saveAsMainDisplay(0);
    m_layerView->loadLayers(0);
    emit changeMainPicture();

    update();
}

void MainWindow::changeActualItem()
{
    int indiceEnCours = m_pileView->currentRow();
    m_scopybioController->saveCurrent(indiceEnCours);

    if (m_scopybioController->areaIsSelected())
    {
        m_scopybioController->saveZoomOfCurrentArea();
        m_imageView->updateZoomOnly();
    }
    if (m_scopybioController->userAreaIsSelected())
    {
        m_scopybioController->saveZoomOfUserArea();
        m_imageView->updateZoomOnly();
    }
    m_scopybioController->DisplayResultImage(indiceEnCours);
    emit changeMainPicture();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    int screenWidth = size().width();
    int screenHeight = size().height();

    m_zoomView->setFixedSize(screenWidth*0.20, screenHeight*0.45);

    m_tools->setFixedSize(screenWidth*0.20, 100);

    m_options->setFixedSize(screenWidth*0.20, screenHeight*0.47 - 100);

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

void MainWindow::setCursorPipetteActive()
{
    m_zoomView->setCursor(Qt::UpArrowCursor);
    m_imageView->setCursor(Qt::UpArrowCursor);

    m_options->setEnabled(false);
    m_dataView->setEnabled(false);
    m_layer->setEnabled(false);
}

void MainWindow::setCursorPipetteDisabled()
{
    m_tools->changePipetteStyleWhenUsed();
    m_tools->setPipetteActive(false);
    m_zoomView->setCursor(Qt::ArrowCursor);
    m_imageView->setCursor(Qt::CrossCursor);

    m_options->setEnabled(true);
    m_dataView->setEnabled(true);
    m_layer->setEnabled(true);
}

void MainWindow::startFullAnalysis()
{
    emit clearZoomView();
    emit clearDataView();

    m_scopybioController->processResults();
    emit changeMainPicture();
}

void MainWindow::wheelEvent(QWheelEvent *ev)
{
    if(m_scopybioController->fileReady())
    {
        //Cas initial. Permet la comparaison avec un unsigned int
        if (m_pileView->currentRow() == -1)
            m_pileView->setCurrentRow(0);

        //Si la molette monte
        if (ev->delta() > 0)
        {
            if (m_pileView->currentRow() > 0)
            {
                m_pileView->setCurrentRow(m_pileView->currentRow()-1);
                changeActualItem();
            }
        }
        else
        {
            if (m_pileView->currentRow() < (int)m_scopybioController->getLoadedTiffList().size()-1)
            {
                m_pileView->setCurrentRow(m_pileView->currentRow()+1);
                changeActualItem();
            }
        }
    }

    ev->accept();
}

void MainWindow::recreateMainDisplay() {
    int indiceEnCours = m_pileView->currentRow();
    m_scopybioController->DisplayResultImage(indiceEnCours);
    emit changeMainPicture();
}

void MainWindow::fullAnalysisEnded()
{
    QMessageBox::information(this, "", "Full analysis completed");
    emit changeMainPicture();
}

void MainWindow::userAnalysisEnded()
{
    QMessageBox::information(this, "", "User analysis completed");
    m_scopybioController->saveZoomOfUserArea();
    emit changeZoomedPicture();
}
