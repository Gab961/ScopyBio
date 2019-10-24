#pragma once

#include <QWidget>
#include <QMenuBar>
#include <QMainWindow>


class MainWindow: public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        bool loadFile(const QString &);

    private slots:
        void open();
        void saveAs();
        void aboutUs();
        void howToUse();

    private:
        void createActions();
        void updateActions();

        QAction *m_loadFile;
        QAction *m_saveFile;
        QAction *m_saveAs;
        QAction *m_aboutUs;
        QAction *m_howToUse;
};

