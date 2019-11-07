#include "menu_option.h"
#include <iostream>
#include "scopybio_controller.h"

menu_option::menu_option(QWidget *parent, ScopyBio_Controller *scopybioController): m_scopybioController(scopybioController)
{
    createView();

    connections();

    m_scopybioController = scopybioController;
}

void menu_option::createView()
{

    setCursor(Qt::ArrowCursor);
    setTitle("Options");

    m_gridOptions = new QGridLayout();
    m_gridContrast = new QGridLayout();
    m_gridSlider = new QGridLayout();

    m_marginError_title = new QLabel("Margin of error : ", this);
    m_marginError_min = new QLabel("0", this);
    m_marginError_max = new QLabel("100", this);
    m_marginError = new QSlider(Qt::Horizontal, this);
    m_marginError->setMinimum(0);
    m_marginError->setMaximum(100);
    m_marginError->setValue(50);
    m_gridContrast->addWidget(m_marginError_title, 0, 0);
    m_gridSlider->addWidget(m_marginError, 0, 1, 1, 7);
    m_gridSlider->addWidget(m_marginError_min, 0, 0);
    m_gridSlider->addWidget(m_marginError_max, 0, 8);
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

    m_histoEqulization = new QCheckBox("Histogram equalization", this);
    m_gridOptions->addWidget(m_histoEqulization, 5, 0);

    setLayout(m_gridOptions);
}

void menu_option::connections()
{
    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_filter,&QCheckBox::toggled,this,&menu_option::onFilterToggled);

    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_histoEqulization,&QCheckBox::toggled,this,&menu_option::onHistoToggled);
}

void menu_option::onFilterToggled(bool checked)
{
    if(checked){
        m_scopybioController->applyGreenFilter();
        emit refreshMainDisplay();
    }
    else
    {
        m_scopybioController->removeGreenFilter();
        emit refreshMainDisplay();
    }
}

void menu_option::onHistoToggled(bool checked)
{
    if(checked){
        m_scopybioController->applyHistogramFilter();
        emit refreshMainDisplay();
    }
    else
    {
        m_scopybioController->removeHistogramFilter();
        emit refreshMainDisplay();
    }
}
