#include "zoom_view.h"
#include <iostream>
#include "scopybio_controller.h"

Zoom_View::Zoom_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QLabel( parent ), m_scopybioController(scopybioController)
{
    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);
}

/**
 * @brief Zoom_View::setNewPicture Affiche l'image située au path dans la fenêtre
 * @param path
 */
void Zoom_View::setNewPicture(int zoneWidth, int zoneHeight)
{
    float ratio = 0.0;

    m_image->setFixedWidth(zoneWidth);
    m_image->setFixedHeight(zoneHeight);

//     Largeur du widget <= hauteur
//     Sert à créer une image qui va prendre un maximum de place possible
//     sans empiéter sur les autres widgets
    if (m_image->size().width() >= m_image->size().height()) {
        if (m_image->size().width() >= size().width()) {
            ratio = (float)m_image->size().width() / (float)size().width();
        }
        else {
            ratio = (float)size().width() / (float)m_image->size().width();
        }

        m_image->setFixedWidth(size().width());
        m_image->setFixedHeight(static_cast<int>(m_image->size().height()*ratio));
    }
    else
    {
        if (m_image->size().height() >= size().height()) {
            ratio = (float)m_image->size().height() / (float)size().height();
        }
        else {
            ratio = (float)size().height() / (float)m_image->size().height();
        }

        m_image->setFixedWidth(static_cast<int>(m_image->size().width()*ratio));
        m_image->setFixedHeight(size().height());
    }

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    QPixmap pm(m_scopybioController->getZoomDisplayPath().c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);
    update();
}

