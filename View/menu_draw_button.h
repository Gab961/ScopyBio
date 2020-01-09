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
        /**
         * @brief Menu_Draw_Button
         * @param parent
         * @param scopybioController
         */
        Menu_Draw_Button(QWidget *parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief createView : Create all the buttons of the view
         */
        void createView();

        /**
         * @brief connections
         */
        void connections();

        /**
         * @brief setPipetteActive : Manage the buttons activation when the pipette button
         *                           is (not) activated
         * @param state
         */
        void setPipetteActive(bool state);

        /**
         * @brief changePipetteStyleWhenUsed
         */
        void changePipetteStyleWhenUsed();

    public slots:
        /**
         * @brief activatePenAnnotation : Manage the buttons style when the pen button is (not) activated
         */
        void activatePenAnnotation();

        /**
         * @brief activateShapesAnnotation : Manage the button style when the shapes button is (not) activated
         */
        void activateShapesAnnotation();

        /**
         * @brief activateTextAnnotation : Manage the buttons style when the text button is (not) activated
         */
        void activateTextAnnotation();

        /**
         * @brief activateEraserAnnotation : Manage the buttons style when the eraser button is (not) activated
         */
        void activateEraserAnnotation();

        /**
         * @brief activatePipetteWaiting : Manage the buttons style when the pipette button is (not) activated
         */
        void activatePipetteWaiting();

        /**
         * @brief activateAnalysisTool : Manage the buttons style when the analysis button is (not) activated
         */
        void activateAnalysisTool();

        /**
         * @brief activateFiltersTool : Manage the buttons style when the filters button is (not) activated
         */
        void activateFiltersTool();

        /**
         * @brief activateNewLayerTool : Manage the buttons style when the new layer button is (not) activated
         */
        void activateNewLayerTool();

        /**
         * @brief activateSelectionAnnotation : Manage the buttons style when the selection button is (not) activated
         */
        void activateSelectionAnnotation();

        /**
         * @brief pen : Send a signal to the menu option view to build the pen view
         */
        void pen();

        /**
         * @brief shapes : Send a signal to the menu option view to build the shapes view
         */
        void shapes();

        /**
         * @brief text : Send a signal to the menu option view to build the text view
         */
        void text();

        /**
         * @brief eraser : Send a signal to the menu option view to build the eraser view
         */
        void eraser();

        /**
         * @brief pipette : Send a signal to the menu option view to build the pipette view
         */
        void pipette();

        /**
         * @brief filters : Send a signal to the menu option view to build the filters view
         */
        void filters();

        /**
         * @brief analysis : Send a signal to the menu option view to build the analysis view
         */
        void analysis();

        /**
         * @brief selectButton : Send a signal to the menu option view to build the selection view
         */
        void selectButton();

        /**
         * @brief askForAnalysis : Send the signal to start the full analysis
         */
        void askForAnalysis();

        /**
         * @brief newLayer : Send a signal to the menu option view to build the new layer view
         */
        void newLayer();

        /**
         * @brief hideButton : Send a signal to the menu option view to build the hide view
         */
        void hideButton();

    signals:
        void waitingForZoomClick();
        void pipetteCanceled();
        void readyToDrawPen();
        void penCanceled();
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
