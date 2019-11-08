#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QCloseEvent>

class ScopyBio_Controller;

class LoopView: public QWidget
{
    Q_OBJECT

    public:
        LoopView(QWidget *parent, ScopyBio_Controller *scopybioController);    
        void createView();
        void connections();
        void launchTimer();
        void loop();



    private:
        void closeEvent(QCloseEvent *ev);

        QGridLayout *m_mainLayout;
        QLabel *m_loop;

        QTimer *timer;
        int value = -1;

        ScopyBio_Controller *m_scopybioController;
};
