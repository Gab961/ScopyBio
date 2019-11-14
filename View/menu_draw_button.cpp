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

    m_selectSquare = new QPushButton("Square", this);
    m_gridTools->addWidget(m_selectSquare, 0, 0);

    m_selectCircle = new QPushButton("Circle", this);
    m_gridTools->addWidget(m_selectCircle, 1, 0);

    m_pen = new QPushButton("Pen", this);
    m_gridTools->addWidget(m_pen, 2, 0);

    m_selectDraw = new QPushButton("Select draw", this);
    m_gridTools->addWidget(m_selectDraw, 0, 1);

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

    //Debut d'un dessin
    QObject::connect(m_pen, &QPushButton::clicked, this, &Menu_Draw_Button::activatePenAnnotation);
}


void Menu_Draw_Button::activatePipetteWaiting()
{
    // Si le bouton est pressé une première fois
    if (!isPipetteButtonActive) {
        setPipetteActive(true);

        emit waitingForZoomClick();
    }
    // Si le bouton a déjà été pressé et on reclic dessus
    else {
        setPipetteActive(false);

        emit pipetteCanceled();
    }
}


void Menu_Draw_Button::activatePenAnnotation()
{
    // Si le bouton est pressé une première fois
    if (!isPenButtonActive) {
        isPenButtonActive = true;
        emit readyToDrawPen();
    }
    // Si le bouton a déjà été pressé et on reclic dessus
    else {
        isPenButtonActive = false;
        emit penCanceled();
    }
}

void Menu_Draw_Button::setPipetteActive(bool state)
{
    isPipetteButtonActive = state;

    if (!isPipetteButtonActive) {
        m_scopybioController->setPipetteClick(false);

        m_selectSquare->setEnabled(true);
        m_selectCircle->setEnabled(true);
        m_selectDraw->setEnabled(true);
        m_pen->setEnabled(true);
        m_eraser->setEnabled(true);
    } else {
        m_selectSquare->setEnabled(false);
        m_selectCircle->setEnabled(false);
        m_selectDraw->setEnabled(false);
        m_pen->setEnabled(false);
        m_eraser->setEnabled(false);
    }
}
