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
    m_firstImageFull = new QPixmap("tmp/2.bpm");
    m_secondImageFull = new QPixmap("tmp/15.bpm");

    m_resultImage = new QPixmap(m_secondImageFull->width(),m_secondImageFull->height());
    m_resultImage->fill(Qt::transparent);

    //Display
    m_display = new QLabel(this);

    drawSlider();

    //Reste
    m_tempTextEdit = new QLineEdit();
    m_boutonTest = new QPushButton();
    m_boutonTest->setText("Go");

    //Layout
    m_mainLayout = new QGridLayout();
    m_mainLayout->addWidget(m_display, 0, 0);
    m_mainLayout->addWidget(m_tempTextEdit, 1, 0);
    m_mainLayout->addWidget(m_boutonTest, 1, 1);

    setLayout(m_mainLayout);
}

void CompareView::connections()
{
    QObject::connect(m_boutonTest, &QPushButton::clicked, this, &CompareView::blabla);
}

void CompareView::drawSlider()
{
    float divisionValue = this->valeurSlide / 100;
    float xCut = (float)m_firstImageFull->width()*divisionValue;


    QPixmap firstBroke = m_firstImageFull->copy(0,0,(int)xCut,m_firstImageFull->height());

    QPainter *painter=new QPainter(m_resultImage);
    painter->drawPixmap(0, 0, m_secondImageFull->width(), m_secondImageFull->height(), *m_secondImageFull);
    painter->drawPixmap(0, 0, (int)xCut, m_firstImageFull->height(), firstBroke);
    painter->end();

    m_display->setPixmap(*m_resultImage);

    update();
}

void CompareView::blabla()
{
    QString text = m_tempTextEdit->text();
    bool ok;
    int value = text.toInt(&ok,10);
    valeurSlide = (float)value;
    drawSlider();
}
