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
        void setPipetteActive(bool state);

    public slots:
        void activatePenAnnotation();
        void activatePipetteWaiting();

    signals:
        void waitingForZoomClick();
        void pipetteCanceled();
        void readyToDrawPen();
        void penCanceled();

    private:
        QGridLayout *m_gridTools;

        bool isPipetteButtonActive = false;
        bool isPenButtonActive = false;
        QPushButton *m_eraser;
        QPushButton *m_pipette;
        QPushButton *m_pen;
        QPushButton *m_selectSquare;
        QPushButton *m_selectCircle;
        QPushButton *m_selectDraw;

        ScopyBio_Controller *m_scopybioController;
};
