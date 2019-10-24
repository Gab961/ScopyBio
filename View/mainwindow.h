#pragma once

#include <QWidget>
#include <QMenuBar>


class MainWindow: public QWidget
{
    public:
        MainWindow();

    private:
        QMenuBar *m_menu;
};

