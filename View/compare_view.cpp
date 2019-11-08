#include "compare_view.h"
#include "Controler/scopybio_controller.h"

#include <QDesktopWidget>

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

    m_mainLayout = new QGridLayout();

    m_firstImage = new QLabel();
    m_mainLayout->addWidget(m_firstImage, 0, 0);

    m_secondImage = new QLabel();
    m_mainLayout->addWidget(m_secondImage, 0, 0);

    setLayout(m_mainLayout);
}

void CompareView::connections()
{

}
