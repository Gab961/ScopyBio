#include "zoom_view.h"
#include <iostream>
#include "scopybio_controller.h"

Zoom_View::Zoom_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController)
{
    setTitle("Zoom view");

    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);

    setLayout(m_layout);
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
        std::cout << "LARGE" << std::endl;
        std::cout << "Largeur widget : " << size().width()
                  << " - Hauteur widget : " << size().height() << std::endl;
        if (m_image->size().width() >= size().width()) {
            std::cout << "--- Image plus large ---" << std::endl;
            ratio = (float)m_image->size().width() / (float)size().width();
        }
        else {
            std::cout << "--- Widget plus large ---" << std::endl;
            ratio = (float)size().width() / (float)m_image->size().width();
        }

        std::cout << "Ratio : " << ratio << std::endl;
        std::cout << "Largeur image avant modification : " << m_image->size().width()
                  << " - Hauteur image avant modification : " << m_image->size().height() << std::endl;

        m_image->setFixedWidth(size().width());
        m_image->setFixedHeight(static_cast<int>(m_image->size().height()*ratio));

        std::cout << "Largeur image après modification : " << m_image->size().width()
                  << " - Hauteur image après modification : " << m_image->size().height() << std::endl;
    }
    else
    {
        std::cout << "LONG" << std::endl;
        std::cout << "Largeur widget : " << size().width()
                  << " - Hauteur widget : " << size().height() << std::endl;
        if (m_image->size().height() >= size().height()) {
            std::cout << "--- Image plus longue ---" << std::endl;
            ratio = (float)m_image->size().height() / (float)size().height();
        }
        else {
            std::cout << "--- Widget plus long ---" << std::endl;
            ratio = (float)size().height() / (float)m_image->size().height();
        }

        std::cout << "Ratio : " << ratio << std::endl;
        std::cout << "Largeur image avant modification : " << m_image->size().width()
                  << " - Hauteur image avant modification : " << m_image->size().height() << std::endl;

        m_image->setFixedWidth(static_cast<int>(m_image->size().width()*ratio));
        m_image->setFixedHeight(size().height());

        std::cout << "Largeur image après modification : " << m_image->size().width()
                  << " - Hauteur image après modification : " << m_image->size().height() << std::endl;
    }

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    QPixmap pm(m_scopybioController->getZoomDisplayPath().c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);
    update();
}

