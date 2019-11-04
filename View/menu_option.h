#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QSlider>

class menu_option: public QGroupBox
{
    Q_OBJECT

    public:
        menu_option(QWidget *parent);

    private:
        QGridLayout *m_gridOptions;
        QGridLayout *m_gridContrast;

        QLabel *m_contrast_title;
        QLabel *m_contrast_min;
        QLabel *m_contrast_max;
        QSlider *m_contrast;

        QCheckBox *m_notes;
        QCheckBox *m_filter;
        QCheckBox *m_drawOnAllLayers;
        QCheckBox *m_shape;
};
