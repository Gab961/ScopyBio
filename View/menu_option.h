#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QSlider>

class ScopyBio_Controller;

class menu_option: public QGroupBox
{
    Q_OBJECT

public slots:
    void onFilterToggled(bool checked);

signals:
    void refreshMainDisplay();

public:
    menu_option(QWidget *parent, ScopyBio_Controller *scopybioController);

private:
    QGridLayout *m_gridOptions;
    QGridLayout *m_gridContrast;
    QGridLayout *m_gridSlider;

    QLabel *m_marginError_title;
    QLabel *m_marginError_min;
    QLabel *m_marginError_max;
    QSlider *m_marginError;

    QCheckBox *m_histoEqulization;
    QCheckBox *m_notes;
    QCheckBox *m_filter;
    QCheckBox *m_drawOnAllLayers;
    QCheckBox *m_shape;

    ScopyBio_Controller *m_scopybioController;
};
