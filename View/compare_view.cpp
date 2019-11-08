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

    setLayout(m_mainLayout);
}

void CompareView::connections()
{

}
