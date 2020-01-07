#include <QMessageBox>
#include "menu_option.h"
#include <iostream>
#include "scopybio_controller.h"

menu_option::menu_option(QWidget *parent, ScopyBio_Controller *scopybioController): m_scopybioController(scopybioController), analysisPanelActive(false), activateUserAnalyse(false)
{
    createView();

    m_scopybioController = scopybioController;
    m_greenChecked = false;
    m_histoChecked = false;
    m_isCircle = m_scopybioController->getCircleIsSelected();
    m_eraserSizeValue = m_scopybioController->getEraserSize();
    m_shapeSizeValue = m_scopybioController->getShapeSize();
    m_penSizeValue = m_scopybioController->getPenSize();
    m_textSizeValue = m_scopybioController->getTextSize();
    m_accuracyValue = m_scopybioController->getAnalysisErrorMargin();
}

void menu_option::createView()
{
    setCursor(Qt::ArrowCursor);
    setTitle("Options");

    m_gridOptions = new QGridLayout();
    m_message = new QLabel("No tool selected.");

    m_gridOptions->addWidget(m_message, 0, 0);

    setLayout(m_gridOptions);
}

void menu_option::pen() {
    m_scopybioController->setListenPenClick(true);
    clearLayout(m_gridOptions);

    // Pen view
    m_gridPenSize = new QGridLayout();
    m_penSize = new QLabel("Pen size : ", this);
    m_penSizeMin = new QLabel("1", this);
    m_penSizeMax = new QLabel("50", this);
    m_penSizeSlider = new QSlider(Qt::Horizontal, this);
    m_penSizeSlider->setMinimum(1);
    m_penSizeSlider->setMaximum(50);
    m_penSizeSlider->setValue(m_penSizeValue);

    m_gridOptions->addWidget(m_penSize, 0, 0);
    m_gridPenSize->addWidget(m_penSizeSlider, 0, 1, 1, 7);
    m_gridPenSize->addWidget(m_penSizeMin, 0, 0);
    m_gridPenSize->addWidget(m_penSizeMax, 0, 8);
    m_gridOptions->addLayout(m_gridPenSize, 1, 0);

    QObject::connect(m_penSizeSlider, &QSlider::valueChanged, this, &menu_option::onPenSizeValueChanged);
}

void menu_option::shapes() {
    m_scopybioController->setListenShapeClick(true);
    clearLayout(m_gridOptions);

    // Shape view
    m_gridShapeSize = new QGridLayout();
    m_shapeSize = new QLabel("Shapes size : ", this);
    m_shapeSizeMin = new QLabel("1", this);
    m_shapeSizeMax = new QLabel("50", this);
    m_shapeSizeSlider = new QSlider(Qt::Horizontal, this);
    m_shapeSizeSlider->setMinimum(1);
    m_shapeSizeSlider->setMaximum(50);
    m_shapeSizeSlider->setValue(m_shapeSizeValue);

    m_circle = new QCheckBox("Circle shape", this);
    m_square = new QCheckBox("Square shape", this);

    if(m_isCircle) {
        m_circle->setChecked(true);
        m_square->setChecked(false);
    } else {
        m_circle->setChecked(false);
        m_square->setChecked(true);
    }

    m_gridOptions->addWidget(m_circle, 0, 0);
    m_gridOptions->addWidget(m_square, 1, 0);

    m_gridOptions->addWidget(m_shapeSize, 2, 0);
    m_gridShapeSize->addWidget(m_shapeSizeSlider, 0, 1, 1, 7);
    m_gridShapeSize->addWidget(m_shapeSizeMin, 0, 0);
    m_gridShapeSize->addWidget(m_shapeSizeMax, 0, 8);
    m_gridOptions->addLayout(m_gridShapeSize, 3, 0);

    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_circle, &QCheckBox::toggled, this, &menu_option::onCircleToggled);

    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_square, &QCheckBox::toggled, this, &menu_option::onSquareToggled);

    QObject::connect(m_shapeSizeSlider, &QSlider::valueChanged, this, &menu_option::onShapeSizeValueChanged);
}

void menu_option::text() {
    m_scopybioController->setListenTextClick(true);
    clearLayout(m_gridOptions);

    //Text
    m_textTitle = new QLabel("Text content : ", this);
    m_textContent = new QLineEdit(this);

    // Text view
    m_gridTextSize = new QGridLayout();
    m_textSize = new QLabel("Text size : ", this);
    m_textSizeMin = new QLabel("1", this);
    m_textSizeMax = new QLabel("50", this);
    m_textSizeSlider = new QSlider(Qt::Horizontal, this);
    m_textSizeSlider->setMinimum(1);
    m_textSizeSlider->setMaximum(50);
    m_textSizeSlider->setValue(m_textSizeValue);

    m_gridOptions->addWidget(m_textTitle, 0, 0);
    m_gridOptions->addWidget(m_textContent, 1, 0);
    m_gridOptions->addWidget(m_textSize, 2, 0);
    m_gridTextSize->addWidget(m_textSizeSlider, 0, 1, 1, 7);
    m_gridTextSize->addWidget(m_textSizeMin, 0, 0);
    m_gridTextSize->addWidget(m_textSizeMax, 0, 8);
    m_gridOptions->addLayout(m_gridTextSize, 3, 0);

    QObject::connect(m_textSizeSlider, &QSlider::valueChanged, this, &menu_option::onTextSizeValueChanged);
}

void menu_option::eraser() {
    m_scopybioController->setListenEraserClick(true);
    clearLayout(m_gridOptions);

    // Eraser view
    m_gridEraserSize = new QGridLayout();
    m_eraserSize = new QLabel("Eraser size : ", this);
    m_eraserSizeMin = new QLabel("1", this);
    m_eraserSizeMax = new QLabel("50", this);
    m_eraserSizeSlider = new QSlider(Qt::Horizontal, this);
    m_eraserSizeSlider->setMinimum(1);
    m_eraserSizeSlider->setMaximum(50);
    m_eraserSizeSlider->setValue(m_eraserSizeValue);

    m_gridOptions->addWidget(m_eraserSize, 0, 0);
    m_gridEraserSize->addWidget(m_eraserSizeSlider, 0, 1, 1, 7);
    m_gridEraserSize->addWidget(m_eraserSizeMin, 0, 0);
    m_gridEraserSize->addWidget(m_eraserSizeMax, 0, 8);
    m_gridOptions->addLayout(m_gridEraserSize, 1, 0);

    QObject::connect(m_eraserSizeSlider, &QSlider::valueChanged, this, &menu_option::onEraserSizeValueChanged);
}

void menu_option::pipette() {
    clearLayout(m_gridOptions);

    m_pipette = new QLabel("There are no options for this tool.", this);

    m_gridOptions->addWidget(m_pipette, 0, 0);
}

void menu_option::filters() {
    clearLayout(m_gridOptions);

    // Filters view
    m_gridFilter = new QGridLayout();
    m_histogramEqualization = new QCheckBox("Histogram equalization", this);
    m_greenFilter = new QCheckBox("Green filter", this);

    m_greenFilter->setChecked(m_greenChecked);
    m_histogramEqualization->setChecked(m_histoChecked);

    m_gridFilter->addWidget(m_histogramEqualization, 0, 0);
    m_gridFilter->addWidget(m_greenFilter, 1, 0);
    m_gridOptions->addLayout(m_gridFilter, 0, 0);


    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_greenFilter, &QCheckBox::toggled, this, &menu_option::onFilterToggled);

    //Demande d'affichage dans la fenêtre de data
    QObject::connect(m_histogramEqualization, &QCheckBox::toggled, this, &menu_option::onHistoToggled);
}

void menu_option::analysis() {
    analysisPanelActive = true;
    clearLayout(m_gridOptions);

    // Analysis view
    m_gridAnalysis = new QGridLayout();
    m_lineLabel = new QLabel("Number of lines : ", this);
    m_lines = new QLineEdit();
    m_lines->setText(QVariant(m_scopybioController->getLineAmount()).toString());

    m_columnLabel = new QLabel("Number of columns : ", this);
    m_columns = new QLineEdit();
    m_columns->setText(QVariant(m_scopybioController->getColumnAmount()).toString());

    m_whiteLevelLabel = new QLabel("White level : ", this);
    m_whiteLevel = new QLineEdit();
    m_whiteLevel->setReadOnly(true);
    m_whiteLevel->setText(QVariant(m_scopybioController->getWhiteColor()).toString());
    m_whiteLevel->setEnabled(false);

    m_gridAccuracy = new QGridLayout();
    m_accuracy = new QLabel("Accuracy : ", this);
    m_accuracyMin = new QLabel("1", this);
    m_accuracyMax = new QLabel("10", this);
    m_accuracySlider = new QSlider(Qt::Horizontal, this);
    m_accuracySlider->setMinimum(1);
    m_accuracySlider->setMaximum(10);
    m_accuracySlider->setValue(m_accuracyValue);

    m_gridAnalysis->addWidget(m_accuracy, 3, 0);
    m_gridAccuracy->addWidget(m_accuracySlider, 0, 1, 1, 7);
    m_gridAccuracy->addWidget(m_accuracyMin, 0, 0);
    m_gridAccuracy->addWidget(m_accuracyMax, 0, 8);
    m_gridAnalysis->addLayout(m_gridAccuracy, 4, 0, 2, 0);

    m_launchSelect = new QPushButton("Analyse selection", this);
    m_launchSelect->setEnabled(activateUserAnalyse);
    m_launch = new QPushButton("Full analyse", this);

    m_gridAnalysis->addWidget(m_lineLabel, 0, 0);
    m_gridAnalysis->addWidget(m_lines, 0, 1);
    m_gridAnalysis->addWidget(m_columnLabel, 1, 0);
    m_gridAnalysis->addWidget(m_columns, 1, 1);
    m_gridAnalysis->addWidget(m_whiteLevelLabel, 2, 0);
    m_gridAnalysis->addWidget(m_whiteLevel, 2, 1);
    m_gridAnalysis->addWidget(m_launchSelect, 5, 0);
    m_gridAnalysis->addWidget(m_launch, 5, 1);
    m_gridOptions->addLayout(m_gridAnalysis, 0, 0);

    //Lance l'analyse de l'image complète
    QObject::connect(m_launch, &QPushButton::clicked, this, &menu_option::launchAnalysis);

    //Lance l'analyse localement
    QObject::connect(m_launchSelect, &QPushButton::clicked, this, &menu_option::launchAnalysisFromSelection);

    QObject::connect(m_accuracySlider, &QSlider::valueChanged, this, &menu_option::onAccuracyValueChanged);
}

void menu_option::newLayer() {
    clearLayout(m_gridOptions);
    // New layer view
    m_gridNewLayer = new QGridLayout();
    m_firstLayerLabel = new QLabel("First image : ");
    m_firstLayer = new QLineEdit();
    m_firstLayer->setText("0");

    m_lastLayerLabel = new QLabel("Last image : ");
    m_lastLayer = new QLineEdit();
    m_lastLayer->setText("0");

    m_createLayer = new QPushButton("Create layer");

    m_gridNewLayer->addWidget(m_firstLayerLabel, 0, 0);
    m_gridNewLayer->addWidget(m_firstLayer, 0, 1);
    m_gridNewLayer->addWidget(m_lastLayerLabel, 1, 0);
    m_gridNewLayer->addWidget(m_lastLayer, 1, 1);
    m_gridNewLayer->addWidget(m_createLayer, 2, 0);
    m_gridOptions->addLayout(m_gridNewLayer, 0, 0);

    //Créer le nouveau calque sur les images renseignées
    QObject::connect(m_createLayer, &QPushButton::clicked, this, &menu_option::onCreateLayer);
}

//TODO METTRE A JOUR LE BOUTON
void menu_option::activateLocalAnalyse()
{
    activateUserAnalyse = true;
    m_scopybioController->setAnalysisTypeIsUser(true);
    analysis();
}

void menu_option::desactivateLocalAnalyse()
{
    activateUserAnalyse = false;
    m_scopybioController->setAnalysisTypeIsUser(false);
    analysis();
}

void menu_option::launchAnalysisFromSelection()
{
    m_scopybioController->setLineAmount(m_lines->text().toInt());
    m_scopybioController->setColumnAmount(m_columns->text().toInt());
    m_scopybioController->setAnalysisTypeIsUser(true);
    emit askForUserAnalyse();

    QMessageBox::information(this, "", "Local analysis processing");
}

void menu_option::launchAnalysis()
{
    m_launchSelect->setEnabled(false);

    m_scopybioController->setLineAmount(m_lines->text().toInt());
    m_scopybioController->setColumnAmount(m_columns->text().toInt());
    m_scopybioController->setWhiteColor(m_whiteLevel->text().toInt());
    m_scopybioController->setAnalysisTypeIsUser(false);

    emit askFullAnalysis();

    QMessageBox::information(this, "", "Full analysis processing");
}

void menu_option::onPenSizeValueChanged(int value) {
    m_penSizeValue = value;
    m_penSizeSlider->setValue(value);

    m_scopybioController->setPenSize(m_penSizeValue);
}

void menu_option::onShapeSizeValueChanged(int value) {
    m_shapeSizeValue = value;
    m_shapeSizeSlider->setValue(value);

    m_scopybioController->setShapeSize(m_shapeSizeValue);
}

void menu_option::onTextSizeValueChanged(int value) {
    m_textSizeValue = value;
    m_textSizeSlider->setValue(value);

    m_scopybioController->setTextSize(m_textSizeValue);
}

void menu_option::onEraserSizeValueChanged(int value) {
    m_eraserSizeValue = value;
    m_eraserSizeSlider->setValue(value);

    m_scopybioController->setEraserSize(m_eraserSizeValue);
}

void menu_option::onAccuracyValueChanged(int value) {
    m_accuracyValue = value;
    m_accuracySlider->setValue(value);

    m_scopybioController->setAnalysisErrorMargin(m_accuracyValue);
}

void menu_option::onFilterToggled(bool checked)
{
    m_greenChecked = checked;
    m_scopybioController->applyGreenFilter();
    emit refreshMainDisplay();
}

void menu_option::onHistoToggled(bool checked)
{
    m_histoChecked = checked;
    m_scopybioController->applyHistogramFilter();
    emit refreshMainDisplay();
}

void menu_option::onCircleToggled(bool checked)
{
    m_isCircle = checked;
    m_square->setChecked(!checked);

    m_scopybioController->setCircleIsSelected(true);
}

void menu_option::onSquareToggled(bool checked)
{
    m_isCircle = !checked;
    m_circle->setChecked(!checked);

    m_scopybioController->setCircleIsSelected(false);
}

void menu_option::clearLayout(QLayout* layout, bool deleteWidgets)
{
    analysisPanelActive = false;
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

void menu_option::onCreateLayer() {
    // TODO Creer calque backend (m_firstLayer = min, m_lastLayer = max)
}

void menu_option::askForTextContent()
{
    emit sendTextBack(m_textContent->text());
}
