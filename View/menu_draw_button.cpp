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

    m_select = new QPushButton(QIcon("../../Resources/Icons/selection.svg"), "", this);
    m_select->setStyleSheet(buttonStyle);
    m_select->setIconSize(QSize(20,20));
    m_select->setMinimumSize(25,25);
    m_select->setMaximumSize(25,25);
    m_gridTools->addWidget(m_select, 0, 4);

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

    m_newLayer = new QPushButton(QIcon("../../Resources/Icons/new-file.svg"), "", this);
    m_newLayer->setStyleSheet(buttonStyle);
    m_newLayer->setIconSize(QSize(20,20));
    m_newLayer->setMinimumSize(25,25);
    m_newLayer->setMaximumSize(25,25);
    m_gridTools->addWidget(m_newLayer, 1, 3);

    m_hide = new QPushButton(QIcon("../../Resources/Icons/visibility.svg"), "", this);
    m_hide->setIconSize(QSize(20,20));
    m_hide->setMinimumSize(25,25);
    m_hide->setMaximumSize(25,25);
    m_hide->setStyleSheet(buttonStyle);
    //m_hide->setEnabled(false);
    m_gridTools->addWidget(m_hide, 1, 4);

    setLayout(m_gridTools);
}

void Menu_Draw_Button::connections()
{
    //Gestion des icones
    QObject::connect(m_pen, &QPushButton::clicked, this, &Menu_Draw_Button::activatePenAnnotation);
    QObject::connect(m_eraser, &QPushButton::clicked, this, &Menu_Draw_Button::activateEraserAnnotation);
    QObject::connect(m_shapes, &QPushButton::clicked, this, &Menu_Draw_Button::activateShapesAnnotation);
    QObject::connect(m_text, &QPushButton::clicked, this, &Menu_Draw_Button::activateTextAnnotation);
    QObject::connect(m_select, &QPushButton::clicked, this, &Menu_Draw_Button::activateSelectionAnnotation);
    QObject::connect(m_analysis, &QPushButton::clicked, this, &Menu_Draw_Button::activateAnalysisTool);
    QObject::connect(m_filters, &QPushButton::clicked, this, &Menu_Draw_Button::activateFiltersTool);
    QObject::connect(m_newLayer, &QPushButton::clicked, this, &Menu_Draw_Button::activateNewLayerTool);
    QObject::connect(m_pipette, &QPushButton::clicked, this, &Menu_Draw_Button::activatePipetteWaiting);


    // Met à jour la vue des options en fonction de l'outil sélectionné
    QObject::connect(m_pen, &QPushButton::clicked, this, &Menu_Draw_Button::pen);
    QObject::connect(m_shapes, &QPushButton::clicked, this, &Menu_Draw_Button::shapes);
    QObject::connect(m_text, &QPushButton::clicked, this, &Menu_Draw_Button::text);
    QObject::connect(m_eraser, &QPushButton::clicked, this, &Menu_Draw_Button::eraser);
    QObject::connect(m_pipette, &QPushButton::clicked, this, &Menu_Draw_Button::pipette);
    QObject::connect(m_filters, &QPushButton::clicked, this, &Menu_Draw_Button::filters);
    QObject::connect(m_analysis, &QPushButton::clicked, this, &Menu_Draw_Button::analysis);
    QObject::connect(m_newLayer, &QPushButton::clicked, this, &Menu_Draw_Button::newLayer);
    QObject::connect(m_select, &QPushButton::clicked, this, &Menu_Draw_Button::selectButton);
    QObject::connect(m_hide, &QPushButton::clicked, this, &Menu_Draw_Button::hideButton);
}


void Menu_Draw_Button::askForAnalysis()
{
    emit startFullAnalysis();
}

void Menu_Draw_Button::activatePipetteWaiting()
{
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isPipetteButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStylePressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        setPipetteActive(true);
        isPenButtonActive = false;
        isEraserButtonActive = false;
        isShapesButtonActive = false;
        isTextButtonActive = false;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = false;
        isLayerButtonActive = false;

        emit waitingForZoomClick();
    }
    // Si le bouton a déjà été pressé et on reclic dessus
    else {
        m_pipette->setStyleSheet(buttonStyleUnpressed);

        setPipetteActive(false);
        emit pipetteCanceled();
    }
}

void Menu_Draw_Button::activatePenAnnotation()
{
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isPenButtonActive) {
        m_pen->setStyleSheet(buttonStylePressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        setPipetteActive(false);
        isPenButtonActive = true;
        isEraserButtonActive = false;
        isShapesButtonActive = false;
        isTextButtonActive = false;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = false;
        isLayerButtonActive = false;

        emit readyToDrawPen();
    }
    // Si le bouton a déjà été pressé et on reclic dessus
    else {
        m_pen->setStyleSheet(buttonStyleUnpressed);

        isPenButtonActive = false;
        emit penCanceled();
    }
}

void Menu_Draw_Button::activateEraserAnnotation()
{
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isEraserButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStylePressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        emit penCanceled();

        setPipetteActive(false);
        isPenButtonActive = false;
        isEraserButtonActive = true;
        isShapesButtonActive = false;
        isTextButtonActive = false;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = false;
        isLayerButtonActive = false;
        isSelectionButtonActive = false;
    }
}

void Menu_Draw_Button::activateShapesAnnotation()
{
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isShapesButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStylePressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        emit penCanceled();

        setPipetteActive(false);
        isPenButtonActive = false;
        isEraserButtonActive = false;
        isShapesButtonActive = true;
        isTextButtonActive = false;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = false;
        isLayerButtonActive = false;
        isSelectionButtonActive = false;
    }
}


void Menu_Draw_Button::activateSelectionAnnotation()
{
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isShapesButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStylePressed);

        setPipetteActive(false);
        emit penCanceled();

        isPenButtonActive = false;
        isEraserButtonActive = false;
        isShapesButtonActive = true;
        isTextButtonActive = false;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = false;
        isLayerButtonActive = false;
        isSelectionButtonActive = true;
    }
}

void Menu_Draw_Button::activateTextAnnotation()
{
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isTextButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStylePressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        setPipetteActive(false);
        isPenButtonActive = false;
        isEraserButtonActive = false;
        isShapesButtonActive = false;
        isTextButtonActive = true;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = false;
        isLayerButtonActive = false;
        isSelectionButtonActive = false;
    }
}

void Menu_Draw_Button::activateAnalysisTool() {
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isAnalysisButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStylePressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        setPipetteActive(false);
        isPenButtonActive = false;
        isEraserButtonActive = false;
        isShapesButtonActive = false;
        isTextButtonActive = false;
        isAnalysisButtonActive = true;
        isFiltersButtonActive = false;
        isLayerButtonActive = false;
        isSelectionButtonActive = false;
    }
}

void Menu_Draw_Button::activateFiltersTool() {
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isFiltersButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStylePressed);
        m_newLayer->setStyleSheet(buttonStyleUnpressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        setPipetteActive(false);
        isPenButtonActive = false;
        isEraserButtonActive = false;
        isShapesButtonActive = false;
        isTextButtonActive = false;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = true;
        isLayerButtonActive = false;
        isSelectionButtonActive = false;
    }
}

void Menu_Draw_Button::activateNewLayerTool() {
    QString buttonStylePressed = "QPushButton{border:none;background-color:rgba(0, 255, 0,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    QString buttonStyleUnpressed = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";

    // Si le bouton est pressé une première fois
    if (!isLayerButtonActive) {
        m_pen->setStyleSheet(buttonStyleUnpressed);
        m_shapes->setStyleSheet(buttonStyleUnpressed);
        m_eraser->setStyleSheet(buttonStyleUnpressed);
        m_text->setStyleSheet(buttonStyleUnpressed);
        m_analysis->setStyleSheet(buttonStyleUnpressed);
        m_pipette->setStyleSheet(buttonStyleUnpressed);
        m_filters->setStyleSheet(buttonStyleUnpressed);
        m_newLayer->setStyleSheet(buttonStylePressed);
        m_select->setStyleSheet(buttonStyleUnpressed);

        setPipetteActive(false);
        isPenButtonActive = false;
        isEraserButtonActive = false;
        isShapesButtonActive = false;
        isTextButtonActive = false;
        isAnalysisButtonActive = false;
        isFiltersButtonActive = false;
        isLayerButtonActive = true;
        isSelectionButtonActive = false;
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
        m_newLayer->setEnabled(true);
        m_hide->setEnabled(true);
        m_select->setEnabled(true);
    } else {
        m_pen->setEnabled(false);
        m_shapes->setEnabled(false);
        m_text->setEnabled(false);
        m_eraser->setEnabled(false);
        m_filters->setEnabled(false);
        m_analysis->setEnabled(false);
        m_newLayer->setEnabled(false);
        m_hide->setEnabled(false);
        m_select->setEnabled(false);
    }
}

void Menu_Draw_Button::pen() {emit penClicked();}

void Menu_Draw_Button::shapes() {emit shapesClicked();}

void Menu_Draw_Button::text() {emit textClicked();}

void Menu_Draw_Button::eraser() {emit eraserClicked();}

void Menu_Draw_Button::pipette() {emit pipetteClicked();}

void Menu_Draw_Button::filters() {emit filtersClicked();}

void Menu_Draw_Button::analysis() {emit analysisClicked();}

void Menu_Draw_Button::newLayer() {emit newLayerClicked();}

void Menu_Draw_Button::selectButton() {emit selectClicked();}

void Menu_Draw_Button::hideButton() {emit hideClicked();}

void Menu_Draw_Button::changePipetteStyleWhenUsed() {
    QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
    m_pipette->setStyleSheet(buttonStyle);
}
