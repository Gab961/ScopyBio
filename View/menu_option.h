#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>

class ScopyBio_Controller;

class menu_option: public QGroupBox
{
    Q_OBJECT

    public:
        menu_option(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void clearLayout(QLayout* layout, bool deleteWidgets = true);

    signals:
        void refreshMainDisplay();

    public slots:
        void pen();
        void shapes();
        void text();
        void eraser();
        void pipette();
        void filters();
        void analysis();
        void launchAnalysis();
        void onPenSizeValueChanged(int value);
        void onShapeSizeValueChanged(int value);
        void onTextSizeValueChanged(int value);
        void onEraserSizeValueChanged(int value);
        void onAccuracyValueChanged(int value);
        void onFilterToggled(bool checked);
        void onHistoToggled(bool checked);
        void onCircleToggled(bool checked);
        void onSquareToggled(bool checked);

    private:
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

        QPushButton *m_launch;

        ScopyBio_Controller *m_scopybioController;
};
