#include "menu_draw_button.h"
#include "scopybio_controller.h"

Menu_Draw_Button::Menu_Draw_Button(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{
    createView();

    connections();
}

void Menu_Draw_Button::createView()
{
    setTitle("Tools");

    m_gridTools = new QGridLayout();

    m_selectSquare = new QPushButton("Select square", this);
    m_gridTools->addWidget(m_selectSquare, 0, 0);

    m_selectCircle = new QPushButton("Select circle", this);
    m_gridTools->addWidget(m_selectCircle, 1, 0);

    m_selectDraw = new QPushButton("Select draw", this);
    m_gridTools->addWidget(m_selectDraw, 2, 0);

    m_pen = new QPushButton("Pen", this);
    m_gridTools->addWidget(m_pen, 0, 1);

    m_eraser = new QPushButton("Eraser", this);
    m_gridTools->addWidget(m_eraser, 1, 1);

    m_pipette = new QPushButton("Pipette", this);
    m_gridTools->addWidget(m_pipette, 2, 1);

    setLayout(m_gridTools);
}

void Menu_Draw_Button::connections()
{
    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_pipette, &QPushButton::clicked, this, &Menu_Draw_Button::activatePipetteWaiting);
}


void Menu_Draw_Button::activatePipetteWaiting()
{
    emit waitingForZoomClick();
}
