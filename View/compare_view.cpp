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
    m_sliderLayout = new QGridLayout();
    m_sliderLayout->addWidget(m_slider);
    m_displayLayout = new QGridLayout();
    m_mainLayout = new QGridLayout();
    m_mainLayout->addLayout(m_displayLayout, 0, 0);
    m_mainLayout->addLayout(m_sliderLayout, 1, 0);

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

    QPixmap firstBroke = m_firstImageFull->copy(0,0, (int)xCut, m_firstImageFull->height());

    QPainter *painter = new QPainter(m_resultImage);
    painter->drawPixmap(0, 0, m_secondImageFull->width(), m_secondImageFull->height(), *m_secondImageFull);
    painter->drawPixmap(0, 0, (int)xCut, m_firstImageFull->height(), firstBroke);
    painter->end();

    m_display->setPixmap(*m_resultImage);
    m_display->setFixedHeight(m_resultImage->height());
    m_display->setFixedWidth(m_resultImage->width());

    float ratio = 0.0;

    //     Sert à créer une image qui va prendre un maximum de place possible
    //     sans empiéter sur les autres widgets
    if (m_display->size().width() >= m_display->size().height()) {
        if (m_display->size().width() >= size().width()) {
            ratio = (float)m_display->size().width() / (float)size().width();
            m_display->setFixedWidth(size().width()*0.9);
            m_display->setFixedHeight(static_cast<int>(m_display->size().height()/ratio));
        }
        else {
            ratio = (float)size().width() / (float)m_display->size().width();
            m_display->setFixedWidth(size().width()*0.9);
            m_display->setFixedHeight(static_cast<int>(m_display->size().height()*ratio));
        }
    }
    else {
        if (m_display->size().height() >= size().height()) {
            ratio = (float)m_display->size().height() / (float)size().height();
            m_display->setFixedWidth(static_cast<int>(m_display->size().width()/ratio));
            m_display->setFixedHeight(size().height()*0.9);
        }
        else {
            ratio = (float)size().height() / (float)m_display->size().height();
            m_display->setFixedWidth(static_cast<int>(m_display->size().width()*ratio));
            m_display->setFixedHeight(size().height()*0.9);
        }
    }

    m_displayLayout->addWidget(m_display);
    //m_mainLayout->setMargin(0);
    m_display->setAlignment(Qt::AlignCenter);

    m_display->setScaledContents(true);

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
