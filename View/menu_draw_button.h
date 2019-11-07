#pragma once

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>

class ScopyBio_Controller;

class Menu_Draw_Button: public QGroupBox
{
    Q_OBJECT

    public:
        Menu_Draw_Button(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void connections();

    public slots:
        void activatePipetteWaiting();

    signals:
        void waitingForZoomClick();

    private:
        QGridLayout *m_gridTools;

        QPushButton *m_eraser;
        QPushButton *m_pipette;
        QPushButton *m_pen;
        QPushButton *m_selectSquare;
        QPushButton *m_selectCircle;
        QPushButton *m_selectDraw;

        ScopyBio_Controller *m_scopybioController;
};
