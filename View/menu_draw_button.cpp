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

    QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    m_pen = new QPushButton(QIcon("../../Resources/Icons/pen.svg"), "", this);
    m_pen->setStyleSheet(buttonStyle);
    m_pen->setIconSize(QSize(20,20));
    m_pen->setMinimumSize(25,25);
    m_pen->setMaximumSize(25,25);
    m_gridTools->addWidget(m_pen, 0, 0);

    m_shapes = new QPushButton(QIcon("../../Resources/Icons/circle-outline.svg"), "", this);
    m_shapes->setStyleSheet(buttonStyle);
    m_shapes->setIconSize(QSize(20,20));
    m_shapes->setMinimumSize(25,25);
    m_shapes->setMaximumSize(25,25);
    m_gridTools->addWidget(m_shapes, 0, 1);

    m_text = new QPushButton(QIcon("../../Resources/Icons/font.svg"), "", this);
    m_text->setStyleSheet(buttonStyle);
    m_text->setIconSize(QSize(20,20));
    m_text->setMinimumSize(25,25);
    m_text->setMaximumSize(25,25);
    m_gridTools->addWidget(m_text, 0, 2);

    m_eraser = new QPushButton(QIcon("../../Resources/Icons/eraser.svg"), "", this);
    m_eraser->setStyleSheet(buttonStyle);
    m_eraser->setIconSize(QSize(20,20));
    m_eraser->setMinimumSize(25,25);
    m_eraser->setMaximumSize(25,25);
    m_gridTools->addWidget(m_eraser, 0, 3);

    m_pipette = new QPushButton(QIcon("../../Resources/Icons/pipette.svg"), "", this);
    m_pipette->setStyleSheet(buttonStyle);
    m_pipette->setIconSize(QSize(20,20));
    m_pipette->setMinimumSize(25,25);
    m_pipette->setMaximumSize(25,25);
    m_gridTools->addWidget(m_pipette, 1, 0);

    m_filters = new QPushButton(QIcon("../../Resources/Icons/filter.svg"), "", this);
    m_filters->setStyleSheet(buttonStyle);
    m_filters->setIconSize(QSize(20,20));
    m_filters->setMinimumSize(25,25);
    m_filters->setMaximumSize(25,25);
    m_gridTools->addWidget(m_filters, 1, 1);

    m_analysis = new QPushButton(QIcon("../../Resources/Icons/analysis.svg"), "", this);
    m_analysis->setStyleSheet(buttonStyle);
    m_analysis->setIconSize(QSize(20,20));
    m_analysis->setMinimumSize(25,25);
    m_analysis->setMaximumSize(25,25);
    m_gridTools->addWidget(m_analysis, 1, 2);

    setLayout(m_gridTools);
}

void Menu_Draw_Button::connections()
{
    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_pipette, &QPushButton::clicked, this, &Menu_Draw_Button::activatePipetteWaiting);

    //Debut d'un dessin
    QObject::connect(m_pen, &QPushButton::clicked, this, &Menu_Draw_Button::activatePenAnnotation);

    // Met à jour la vue des options en fonction de l'outil sélectionné
    QObject::connect(m_pen, &QPushButton::clicked, this, &Menu_Draw_Button::pen);
    QObject::connect(m_shapes, &QPushButton::clicked, this, &Menu_Draw_Button::shapes);
    QObject::connect(m_text, &QPushButton::clicked, this, &Menu_Draw_Button::text);
    QObject::connect(m_eraser, &QPushButton::clicked, this, &Menu_Draw_Button::eraser);
    QObject::connect(m_pipette, &QPushButton::clicked, this, &Menu_Draw_Button::pipette);
    QObject::connect(m_filters, &QPushButton::clicked, this, &Menu_Draw_Button::filters);
    QObject::connect(m_analysis, &QPushButton::clicked, this, &Menu_Draw_Button::analysis);
}


void Menu_Draw_Button::askForAnalysis()
{
    emit startFullAnalysis();
}

void Menu_Draw_Button::activatePipetteWaiting()
{
    // Si le bouton est pressé une première fois
    if (!isPipetteButtonActive) {
        QString buttonStyle = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
        m_pipette->setStyleSheet(buttonStyle);

        setPipetteActive(true);
        emit waitingForZoomClick();
    }
    // Si le bouton a déjà été pressé et on reclic dessus
    else {
        QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
        m_pipette->setStyleSheet(buttonStyle);

        setPipetteActive(false);
        emit pipetteCanceled();
    }
}

void Menu_Draw_Button::activatePenAnnotation()
{
    // Si le bouton est pressé une première fois
    if (!isPenButtonActive) {
        QString buttonStyle = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
        m_pen->setStyleSheet(buttonStyle);

        isPenButtonActive = true;
        emit readyToDrawPen();
    }
    // Si le bouton a déjà été pressé et on reclic dessus
    else {
        QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
        m_pen->setStyleSheet(buttonStyle);

        isPenButtonActive = false;
        emit penCanceled();
    }
}

void Menu_Draw_Button::setPipetteActive(bool state)
{
    isPipetteButtonActive = state;

    if (!isPipetteButtonActive) {
        m_scopybioController->setPipetteClick(false);

        m_pen->setEnabled(true);
        m_shapes->setEnabled(true);
        m_text->setEnabled(true);
        m_eraser->setEnabled(true);
        m_pipette->setEnabled(true);
        m_filters->setEnabled(true);
        m_analysis->setEnabled(true);
    } else {
        m_pen->setEnabled(false);
        m_shapes->setEnabled(false);
        m_text->setEnabled(false);
        m_eraser->setEnabled(false);
        m_filters->setEnabled(false);
        m_analysis->setEnabled(false);
    }
}

void Menu_Draw_Button::pen() {emit penClicked();}

void Menu_Draw_Button::shapes() {emit shapesClicked();}

void Menu_Draw_Button::text() {emit textClicked();}

void Menu_Draw_Button::eraser() {emit eraserClicked();}

void Menu_Draw_Button::pipette() {emit pipetteClicked();}

void Menu_Draw_Button::filters() {emit filtersClicked();}

void Menu_Draw_Button::analysis() {emit analysisClicked();}

void Menu_Draw_Button::changePipetteStyleWhenUsed() {
    std::cout << "coucou" << std::endl;
    QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    m_pipette->setStyleSheet(buttonStyle);
}
