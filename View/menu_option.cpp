#include "menu_option.h"

menu_option::menu_option(QWidget *parent)
{
    setTitle("Options");

    m_gridOptions = new QGridLayout();
    m_gridContrast = new QGridLayout();
    m_gridSlider = new QGridLayout();

    m_contrast_title = new QLabel("Contrast : ", this);
    m_contrast_min = new QLabel("0", this);
    m_contrast_max = new QLabel("100", this);
    m_contrast = new QSlider(Qt::Horizontal, this);
    m_contrast->setMinimum(0);
    m_contrast->setMaximum(100);
    m_contrast->setValue(50);
    m_gridContrast->addWidget(m_contrast_title, 0, 0);
    m_gridSlider->addWidget(m_contrast, 0, 1, 1, 7);
    m_gridSlider->addWidget(m_contrast_min, 0, 0);
    m_gridSlider->addWidget(m_contrast_max, 0, 8);
    m_gridContrast->addLayout(m_gridSlider, 1, 0);
    m_gridOptions->addLayout(m_gridContrast, 0, 0);

    m_notes = new QCheckBox("Show annotations", this);
    m_gridOptions->addWidget(m_notes, 1, 0);

    m_filter = new QCheckBox("Show filter", this);
    m_gridOptions->addWidget(m_filter, 2, 0);

    m_drawOnAllLayers = new QCheckBox("Draw on all layers", this);
    m_gridOptions->addWidget(m_drawOnAllLayers, 3, 0);

    m_shape = new QCheckBox("Shape", this);
    m_gridOptions->addWidget(m_shape, 4, 0);

    setLayout(m_gridOptions);
}
