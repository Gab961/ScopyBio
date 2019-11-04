#pragma once

#include <iostream>
#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>
#include <QGridLayout>

class Pile_View;
class menu_option;
class Image_View;
class Zoom_View;

class MainWindow: public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

    signals:
        void sendPath(std::string path);
        void changeMainPicture(std::string path);
        void changeZoomedPicture(std::string path);

    private slots:
        void open();
        void save();
        void saveAs();
        void aboutUs();
        void howToUse();
        void showFirstInPile();

    private:
        void createActions();
        void updateSaveAs();
        void updateSave();

        Pile_View *m_pileView;
        Image_View *m_imageView;
        Zoom_View *m_zoomView;
        menu_option *m_options;

        QAction *m_loadFile;
        QAction *m_saveFile;
        QAction *m_saveAs;
        QAction *m_aboutUs;
        QAction *m_howToUse;

        QWidget *m_window;
        QGridLayout *m_mainLayout;

        //TODO Voir si on les garde
        std::string pathOfMainDisplay = "tmp/mainDisplay.bmp";
        std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";
};

