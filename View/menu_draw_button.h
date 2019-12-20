#pragma once

#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QColorDialog>

class ScopyBio_Controller;

class Menu_Draw_Button: public QGroupBox
{
    Q_OBJECT

    public:
        Menu_Draw_Button(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void connections();
        void setPipetteActive(bool state);
        void changePipetteStyleWhenUsed();

    public slots:
        void activatePenAnnotation();
        void activatePipetteWaiting();
        void pen();
        void shapes();
        void text();
        void eraser();
        void pipette();
        void filters();
        void analysis();
        void askForAnalysis();

    signals:
        void waitingForZoomClick();
        void pipetteCanceled();
        void readyToDrawPen();
        void penCanceled();
        //TODO
        void startFullAnalysis();
        void penClicked();
        void shapesClicked();
        void textClicked();
        void eraserClicked();
        void pipetteClicked();
        void filtersClicked();
        void analysisClicked();

    private:
        QGridLayout *m_gridTools;

        bool isPipetteButtonActive = false;
        bool isPenButtonActive = false;
        QPushButton *m_eraser;
        QPushButton *m_pipette;
        QPushButton *m_pen;
        QPushButton *m_shapes;
        QPushButton *m_text;
        QPushButton *m_analysis;
        QPushButton *m_filters;

        ScopyBio_Controller *m_scopybioController;
};
