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
        void activateShapesAnnotation();
        void activateTextAnnotation();
        void activateEraserAnnotation();
        void activatePipetteWaiting();
        void activateAnalysisTool();
        void activateFiltersTool();
        void activateNewLayerTool();
        void activateSelectionAnnotation();
        void pen();
        void shapes();
        void text();
        void eraser();
        void pipette();
        void filters();
        void analysis();
        void selectButton();
        void askForAnalysis();
        void newLayer();
        void hideButton();

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
        void newLayerClicked();
        void selectClicked();
        void hideClicked();

    private:
        QGridLayout *m_gridTools;

        bool isPipetteButtonActive = false;
        bool isPenButtonActive = false;
        bool isEraserButtonActive = false;
        bool isShapesButtonActive = false;
        bool isTextButtonActive = false;
        bool isAnalysisButtonActive = false;
        bool isFiltersButtonActive = false;
        bool isLayerButtonActive = false;
        bool isSelectionButtonActive = false;

        QPushButton *m_eraser;
        QPushButton *m_pipette;
        QPushButton *m_pen;
        QPushButton *m_shapes;
        QPushButton *m_text;
        QPushButton *m_analysis;
        QPushButton *m_filters;
        QPushButton *m_newLayer;
        QPushButton *m_select;
        QPushButton *m_hide;

        ScopyBio_Controller *m_scopybioController;
};
