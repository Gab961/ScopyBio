#include "data_view.h"
#include "scopybio_controller.h"
#include <iostream>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Data_View::Data_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController)
{
    createView();
}

void Data_View::createView()
{
    setTitle("Datas view");

    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    setLayout(m_layout);
}

void Data_View::drawResults()
{
    QPixmap pm(m_scopybioController->getResultDisplayPath().c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);
    update();
}

void Data_View::processingResults(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight)
{
    m_scopybioController->processResultsWithCrop(pos1, pos2, labelWidth, labelHeight);
    drawResults();
}

void Data_View::mousePressEvent( QMouseEvent* ev )
{
    QPoint origPoint = ev->pos();
    if (m_scopybioController->dataReady())
    {
        int item = m_scopybioController->getItemAtPoint(origPoint.x(),m_image->width());
        emit graphClic(item);
    }
}
