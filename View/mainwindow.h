#pragma once

#include <iostream>
#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QPushButton>
#include <QGroupBox>

class LayerView;
class Pile_View;
class menu_option;
class Image_View;
class Zoom_View;
class Menu_Draw_Button;
class Data_View;
class ScopyBio_Controller;
class LoopView;
class ComparePopup;
class AnalysisPopup;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void createView();
    void connections();
    void wheelEvent(QWheelEvent *ev);

signals:
    void sendPath(std::string path);
    void sendPathProjet(std::string path);
    void changeMainPicture();
    void changeZoomedPicture();
    void clearZoomView();
    void clearDataView();
public slots:
    void open();
    void save();
    void undo();
    void redo();
    void saveAs();
    void aboutUs();
    void howToUse();
    void showFirstInPile();
    void changeActualItem();
    void openProject(std::string path);
    void startFullAnalysis();
    void userAnalysisEnded();
    void fullAnalysisEnded();

protected:
    void closeEvent(QCloseEvent* e) override;

private:
    void createActions();
    void updateSaveAs();
    void updateSave();
    void nouveauClicCreerRectangle(QPoint pos1, QPoint pos2);
    void resizeEvent(QResizeEvent* event);
    void setCursorPipetteActive();
    void setCursorPipetteDisabled();

    QGridLayout *m_leftLayout;
    Zoom_View *m_zoomView;
    Menu_Draw_Button *m_tools;
    menu_option *m_options;

    QGridLayout *m_centerLayout;
    QGridLayout *m_buttonLayout;
    Image_View *m_imageView;
    LoopView *m_loopWindow;
    ComparePopup *m_comparePopup;

    QGridLayout *m_rightLayout;
    QGridLayout *m_pileLayerLayout;
    QGroupBox *m_layer;
    Data_View *m_dataView;
    Pile_View *m_pileView;
    LayerView *m_layerView;

    QAction *m_loadFile;
    QAction *m_saveFile;
    QAction *m_saveAs;
    QAction *m_aboutUs;
    QAction *m_howToUse;
    QAction *m_compare;
    QAction *m_loop;
    QAction *m_undo;
    QAction *m_redo;

    AnalysisPopup *m_analysisPopup;

    QWidget *m_window;
    QGridLayout *m_mainLayout;

    ScopyBio_Controller *m_scopybioController;
};

