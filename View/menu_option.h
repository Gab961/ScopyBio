#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class ScopyBio_Controller;

class menu_option: public QGroupBox
{
    Q_OBJECT

    public:
        /**
         * @brief menu_option
         * @param parent
         * @param scopybioController
         */
        menu_option(QWidget *parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief createView : Create the empty view.
         */
        void createView();

        /**
         * @brief clearLayout : Remove all the element of the view
         * @param layout
         * @param deleteWidgets
         */
        void clearLayout(QLayout* layout, bool deleteWidgets = true);

        /**
         * @brief closeMessageBox
         */
        void closeMessageBox();

    signals:
        void refreshMainDisplay();
        void askFullAnalysis();
        void askForUserAnalyse();
        void sendTextBack(QString content);
        void switchToIndex(int newIndex);
        void reloadLayers(int newIndex);

    public slots:
        /**
         * @brief pen : Create the pen view and manage buttons activation
         */
        void pen();

        /**
         * @brief shapes : Create the shapes view and manage buttons activation
         */
        void shapes();

        /**
         * @brief text : Create the text view and manage buttons activation
         */
        void text();

        /**
         * @brief eraser : Create the eraser view and manage buttons activation
         */
        void eraser();

        /**
         * @brief pipette : Create the pipette view and manage buttons activation
         */
        void pipette();

        /**
         * @brief filters : Create the filters view and manage buttons activation
         */
        void filters();

        /**
         * @brief analysis : Create the analysis view and manage buttons activation
         */
        void analysis();

        /**
         * @brief newLayer : Create the new layer view and manage buttons activation
         */
        void newLayer();

        /**
         * @brief selection : Create the selection and manage buttons activation
         */
        void selection();

        /**
         * @brief launchAnalysis : Send the datas to the controller and ask for full analysis
         */
        void launchAnalysis();

        /**
         * @brief onPenSizeValueChanged : Set the pen size
         * @param value : Value from the QSlider
         */
        void onPenSizeValueChanged(int value);

        /**
         * @brief onShapeSizeValueChanged : Set the shapes size
         * @param value : Value from the QSlider
         */
        void onShapeSizeValueChanged(int value);

        /**
         * @brief onTextSizeValueChanged : Set the text size
         * @param value : Value from the QSlider
         */
        void onTextSizeValueChanged(int value);

        /**
         * @brief onEraserSizeValueChanged : Set the eraser size
         * @param value : Value from the QSlider
         */
        void onEraserSizeValueChanged(int value);

        /**
         * @brief onAccuracyValueChanged : Set the accuracy value
         * @param value : Value from the QSlider
         */
        void onAccuracyValueChanged(int value);

        /**
         * @brief onFilterToggled : Set the green filter on the image view
         * @param checked
         */
        void onFilterToggled(bool checked);

        /**
         * @brief onHistoToggled : Set the histogram equalization filter on the image view
         * @param checked
         */
        void onHistoToggled(bool checked);

        /**
         * @brief onCircleToggled : Manage the checkbox state and send to the controller
         *                          the circle is selected
         * @param checked
         */
        void onCircleToggled(bool checked);

        /**
         * @brief onSquareToggled : Manage the checkbox state and send to the controller
         *                          the circle is not selected ( = the square is selected)
         * @param checked
         */
        void onSquareToggled(bool checked);

        /**
         * @brief launchAnalysisFromSelection : Send the datas to the controller and ask for local analysis
         */
        void launchAnalysisFromSelection();

        /**
         * @brief activateLocalAnalyse : Enable local analysis
         */
        void activateLocalAnalyse();

        /**
         * @brief desactivateLocalAnalyse : Disable local analysis
         */
        void desactivateLocalAnalyse();

        /**
         * @brief onCreateLayer : Create a new layer on the first to last pictures specified
         */
        void onCreateLayer();

        /**
         * @brief askForTextContent : Send the text to write
         */
        void askForTextContent();

    private:
        QMessageBox *m_processMsg;

        QGridLayout *m_gridOptions;
        QLabel *m_message;

        // Pen view
        QGridLayout *m_gridPenSize;
        QLabel *m_penSize;
        QLabel *m_penSizeMin;
        QLabel *m_penSizeMax;
        QSlider *m_penSizeSlider;
        int m_penSizeValue;

        // Shape view
        QGridLayout *m_gridShapeSize;
        QLabel *m_shapeSize;
        QLabel *m_shapeSizeMin;
        QLabel *m_shapeSizeMax;
        QSlider *m_shapeSizeSlider;
        int m_shapeSizeValue;

        QCheckBox *m_circle;
        QCheckBox *m_square;
        // 1 circle, 0 square
        bool m_isCircle;

        // Text view
        QLabel *m_textTitle;
        QLineEdit *m_textContent;
        QGridLayout *m_gridTextSize;
        QLabel *m_textSize;
        QLabel *m_textSizeMin;
        QLabel *m_textSizeMax;
        QSlider *m_textSizeSlider;
        int m_textSizeValue;

        // Eraser view
        QGridLayout *m_gridEraserSize;
        QLabel *m_eraserSize;
        QLabel *m_eraserSizeMin;
        QLabel *m_eraserSizeMax;
        QSlider *m_eraserSizeSlider;
        int m_eraserSizeValue;

        // Pipette view
        QLabel *m_pipette;

        // Select view
        QLabel *m_select;

        // Filters view
        QGridLayout *m_gridFilter;
        QCheckBox *m_histogramEqualization;
        QCheckBox *m_greenFilter;
        bool m_histoChecked;
        bool m_greenChecked;

        // Analysis view
        QGridLayout *m_gridAnalysis;
        QLabel *m_lineLabel;
        QLineEdit *m_lines;

        QLabel *m_columnLabel;
        QLineEdit *m_columns;

        QLabel *m_whiteLevelLabel;
        QLineEdit *m_whiteLevel;

        QGridLayout *m_gridAccuracy;
        QLabel *m_accuracy;
        QLabel *m_accuracyMin;
        QLabel *m_accuracyMax;
        QSlider *m_accuracySlider;
        int m_accuracyValue;

        QPushButton *m_launchSelect;
        QPushButton *m_launch;

        // New layer view
        QGridLayout *m_gridNewLayer;
        QLabel *m_firstLayerLabel;
        QLineEdit *m_firstLayer;

        QLabel *m_lastLayerLabel;
        QLineEdit *m_lastLayer;

        QPushButton *m_createLayer;

        ScopyBio_Controller *m_scopybioController;        

        bool analysisPanelActive;
        bool activateUserAnalyse;
        bool penIsActive;
        bool eraserIsActive;
        bool textIsActive;
        bool shapesIsActive;
        bool selectIsActive;
};
