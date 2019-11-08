#include "data_view.h"
#include "scopybio_controller.h"
#include <iostream>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Data_View::Data_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController)
{    
    this->setAttribute(Qt::WA_Hover, true);
    createView();
}

void Data_View::createView()
{
    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    setLayout(m_layout);
}

void Data_View::drawResults()
{
    setCursor(Qt::PointingHandCursor);
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

void Data_View::hoverEnter(QHoverEvent * event) { }
void Data_View::hoverLeave(QHoverEvent * event) { }
void Data_View::hoverMove(QHoverEvent * event) {
    if (m_scopybioController->dataReady())
    {
        QPoint origPoint = event->pos();

        if (mouseInLabel(origPoint))
        {
            int item = m_scopybioController->getItemAtPoint(origPoint.x()-m_image->x(), m_image->width());
            QString str = "Image : " + QString::number(item);

            QPoint realPosition = QCursor::pos();
            QToolTip::showText(realPosition,str, nullptr, QRect());
        }
    }
}

bool Data_View::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

bool Data_View::mouseInLabel(QPoint pos)
{
    if (pos.x() >= m_image->x() && pos.x() <= m_image->x()+m_image->width())
    {
        if (pos.y() >= m_image->y() && pos.y() <= m_image->y()+m_image->height())
        {
            return true;
        }
    }
    return false;
}
