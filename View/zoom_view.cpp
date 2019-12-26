#include <QMouseEvent>
#include "zoom_view.h"
#include <iostream>
#include "scopybio_controller.h"

Zoom_View::Zoom_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController), readyToShow(false)
{
    createView();
}

void Zoom_View::createView()
{
    setTitle("Zoom view");

    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);
    m_image->setText("No data to show");


    setLayout(m_layout);
}

void Zoom_View::resetZoomView()
{
    m_image->clear();
    m_image->setAlignment(Qt::AlignCenter);
    m_image->setText("No data to show");
}

void Zoom_View::enableDisplay()
{
    readyToShow = true;
}

/**
 * @brief Zoom_View::setNewPicture Affiche l'image située au path dans la fenêtre
 * @param path
 */
void Zoom_View::setNewPicture(int zoneWidth, int zoneHeight)
{
    if (readyToShow)
    {
        float ratio = 0.0;

        m_image->setFixedWidth(zoneWidth);
        m_image->setFixedHeight(zoneHeight);

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
        //m_layout->setMargin(0);
        m_image->setAlignment(Qt::AlignCenter);

        QPixmap pm(m_scopybioController->getZoomDisplayPath().c_str());
        m_image->setPixmap(pm);
        m_image->setScaledContents(true);
        update();

    }
}

void Zoom_View::readyForClick() { m_scopybioController->setPipetteClick(true); }

void Zoom_View::mousePressEvent( QMouseEvent* ev )
{
    if (m_scopybioController->getZoomReady())
    {
        QPoint origPoint = ev->pos();
        if (m_scopybioController->getPipetteClick())
        {
            m_scopybioController->setPipetteClick(false);
            origPoint.setX(origPoint.x() - m_image->x());
            origPoint.setY(origPoint.y() - m_image->y());
            m_scopybioController->manageNewWhite(origPoint, m_image->width(), m_image->height(), true);

            emit pipetteClicked();
        }
        //If une analyse a été effectuée
        else
        {
            origPoint.setX(origPoint.x() - m_image->x());
            origPoint.setY(origPoint.y() - m_image->y());
            getData(origPoint,m_image->width(),m_image->height());
        }

    }
}

void Zoom_View::setPictureFromFile()
{
    float ratio = 0.0;

    QPixmap pm(m_scopybioController->getZoomDisplayPath().c_str());
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

void Zoom_View::getData(QPoint area, int labelWidth, int labelHeight) {
    if (m_scopybioController->dataReady())
    {
        m_scopybioController->getDataFromZoomArea(area, labelWidth, labelHeight);

        emit changeGraphPicture();

        update();
    }
}
