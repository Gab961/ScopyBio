#include "data_view.h"
#include "scopybio_controller.h"
#include <iostream>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Data_View::Data_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController), readyToShow(false)
{    
    setTitle("Data view");
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
    m_image->setText("No data to show");

    setLayout(m_layout);
}

void Data_View::resetDataView()
{
    m_image->clear();
    m_image->setAlignment(Qt::AlignCenter);
    m_image->setText("No data to show");
}

void Data_View::drawResults()
{
    if (readyToShow)
    {
        setCursor(Qt::PointingHandCursor);
        QPixmap pm(m_scopybioController->getResultDisplayPath().c_str());
        m_image->setPixmap(pm);
        m_image->setScaledContents(true);
        update();
    }
}

void Data_View::processingResults(int labelWidth, int labelHeight)
{
    m_scopybioController->processResultsWithCrop( labelWidth, labelHeight);
    drawResults();
}


void Data_View::enableDisplay()
{
    readyToShow = true;
}

void Data_View::mousePressEvent( QMouseEvent* ev )
{
    QPoint origPoint = ev->pos();
    if (m_scopybioController->dataReady())
    {
        int item = m_scopybioController->getItemAtPoint(origPoint.x()-m_image->x(),m_image->width());
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

void Data_View::setGraphFromFile()
{
    float ratio = 0.0;

    QPixmap pm(m_scopybioController->getResultDisplayPath().c_str());
    m_image->setFixedWidth(pm.width());
    m_image->setFixedHeight(pm.height());

    //     Largeur du widget <= hauteur
    //     Sert à créer une image qui va prendre un maximum de place possible
    //     sans empiéter sur les autres widgets
    if (m_image->size().width() >= m_image->size().height()) {
        if (m_image->size().width() >= size().width()) {
            ratio = (float)m_image->size().width() / (float)size().width();
            m_image->setFixedWidth(size().width());
            m_image->setFixedHeight(static_cast<int>(m_image->size().height()/ratio));
        }
        else {
            ratio = (float)size().width() / (float)m_image->size().width();
            m_image->setFixedWidth(size().width());
            m_image->setFixedHeight(static_cast<int>(m_image->size().height()*ratio));
        }
    }
    else {
        if (m_image->size().height() >= size().height()) {
            ratio = (float)m_image->size().height() / (float)size().height();
            m_image->setFixedWidth(static_cast<int>(m_image->size().width()/ratio));
            m_image->setFixedHeight(size().height());
        }
        else {
            ratio = (float)size().height() / (float)m_image->size().height();
            m_image->setFixedWidth(static_cast<int>(m_image->size().width()*ratio));
            m_image->setFixedHeight(size().height());
        }
    }

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    m_image->setPixmap(pm);
    m_image->setScaledContents(true);

    update();
}
