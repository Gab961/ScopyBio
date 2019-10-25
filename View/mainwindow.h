#pragma once

#include "pile_view.h"

#include <iostream>
#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>


class MainWindow: public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

    signals:
        void sendPath(std::string path);

    private slots:
        void open();
        void save();
        void saveAs();
        void aboutUs();
        void howToUse();

    private:
        void createActions();
        void updateSaveAs();
        void updateSave();

        Pile_View *m_pileView;
        QAction *m_loadFile;
        QAction *m_saveFile;
        QAction *m_saveAs;
        QAction *m_aboutUs;
        QAction *m_howToUse;
};

