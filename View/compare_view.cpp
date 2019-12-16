#include <QDesktopWidget>
#include <QPushButton>
#include <QLineEdit>
#include "Controler/scopybio_controller.h"
#include "compare_view.h"

CompareView::CompareView(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{
    createView();

    connections();
}

void CompareView::createView()
{
    std::cout << "HERE" << std::endl;
    QDesktopWidget dw;
    int screenHeight = dw.height()*0.7;
    setFixedSize(screenHeight, screenHeight);

    //Images
    m_firstImageFull = new QPixmap();
    m_secondImageFull = new QPixmap();

    m_resultImage = new QPixmap();

    //Display
    m_display = new QLabel(this);

    //Reste
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setMinimum(0);
    m_slider->setMaximum(100);
    m_slider->setValue(50);

    //Layout
    m_mainLayout = new QGridLayout();
    m_mainLayout->addWidget(m_display, 0, 0);
    m_mainLayout->addWidget(m_slider, 1, 0);

    setLayout(m_mainLayout);
}

void CompareView::connections()
{
    QObject::connect(m_slider, &QSlider::valueChanged, this, &CompareView::compare);
}

void CompareView::drawSlider()
{
    float divisionValue = this->valeurSlide / 100;
    float xCut = (float)m_firstImageFull->width()*divisionValue;

    QPixmap firstBroke = m_firstImageFull->copy(0,0,(int)xCut,m_firstImageFull->height());

    QPainter *painter = new QPainter(m_resultImage);
    painter->drawPixmap(0, 0, m_secondImageFull->width(), m_secondImageFull->height(), *m_secondImageFull);
    painter->drawPixmap(0, 0, (int)xCut, m_firstImageFull->height(), firstBroke);
    painter->end();

    m_display->setPixmap(*m_resultImage);

    update();
}

void CompareView::compare()
{
    int value = m_slider->value();
    valeurSlide = (float)value;
    drawSlider();
}

void CompareView::setImages(QString image1, QString image2) {
    m_firstImageFull = new QPixmap(image1);
    m_secondImageFull = new QPixmap(image2);

    m_resultImage = new QPixmap(m_secondImageFull->width(), m_secondImageFull->height());
    m_resultImage->fill(Qt::transparent);

    drawSlider();

    update();
}
