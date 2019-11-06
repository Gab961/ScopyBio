#pragma once

#include <iostream>
#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QPushButton>

class LayerView;
class Pile_View;
class menu_option;
class Image_View;
class Zoom_View;
class Menu_Draw_Button;
class Data_View;
class ScopyBio_Controller;

class MainWindow: public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

    signals:
        void sendPath(std::string path);
        void changeMainPicture();
        void changeZoomedPicture();

    public slots:
        void open();
        void save();
        void saveAs();
        void aboutUs();
        void howToUse();
        void showFirstInPile();
        void changeActualItem();

    private:
        void buildView();
        void connections();
        void createActions();
        void updateSaveAs();
        void updateSave();
        void nouveauClicCreerRectangle(QPoint pos1, QPoint pos2);
        void resizeEvent(QResizeEvent* event);

        QGridLayout *m_leftLayout;
        Zoom_View *m_zoomView;
        Menu_Draw_Button *m_tools;
        menu_option *m_options;

        QGridLayout *m_centerLayout;
        QGridLayout *m_buttonLayout;
        Image_View *m_imageView;
        QPushButton *m_openLoop;
        QPushButton *m_openCompare;

        QGridLayout *m_rightLayout;
        QGridLayout *m_pileLayerLayout;
        Data_View *m_dataView;
        Pile_View *m_pileView;
        LayerView *m_layerView;

        QAction *m_loadFile;
        QAction *m_saveFile;
        QAction *m_saveAs;
        QAction *m_aboutUs;
        QAction *m_howToUse;

        QWidget *m_window;
        QGridLayout *m_mainLayout;

        ScopyBio_Controller *m_scopybioController;
};

