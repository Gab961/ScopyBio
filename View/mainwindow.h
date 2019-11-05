#pragma once

#include <iostream>
#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>
#include <QGridLayout>
#include <QListWidgetItem>

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


//    protected:
//        resizeEvent(QResizeEvent *event);

    signals:
        void sendPath(std::string path);
        void changeMainPicture();
        void changeZoomedPicture();

    private slots:
        void open();
        void save();
        void saveAs();
        void aboutUs();
        void howToUse();
        void showFirstInPile();
        void changeActualItem();

    private:
        void createActions();
        void updateSaveAs();
        void updateSave();
        void nouveauClicCreerRectangle(QPoint pos1, QPoint pos2);
        void resizeEvent(QResizeEvent* event);

        QGridLayout *m_leftLayout;
        Pile_View *m_pileView;
        menu_option *m_options;
        Menu_Draw_Button *m_tools;

        QGridLayout *m_centerLayout;
        Image_View *m_imageView;

        QGridLayout *m_rightLayout;
        Data_View *m_dataView;
        Zoom_View *m_zoomView;

        QAction *m_loadFile;
        QAction *m_saveFile;
        QAction *m_saveAs;
        QAction *m_aboutUs;
        QAction *m_howToUse;

        QWidget *m_window;
        QGridLayout *m_mainLayout;

        ScopyBio_Controller *m_scopybioController;
};

