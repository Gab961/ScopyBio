#include "zoom_view.h"
#include <iostream>

Zoom_View::Zoom_View( QWidget * parent) : QLabel( parent )
{
    m_layout = new QGridLayout(this);
}

/**
 * @brief Zoom_View::setNewPicture Affiche l'image située au path dans la fenêtre
 * @param path
 */
void Zoom_View::setNewPicture(std::string path)
{
    float ratio = 0.0;

    m_layout->removeWidget(m_image);
    m_image = new QLabel(this);

    // Largeur du widget <= hauteur
    // Sert à créer une image qui va prendre un maximum de place possible
    // sans empiéter sur les autres widgets
    if (m_image->size().width() >= m_image->size().height()) {
        std::cout << "IF WIDTH >= HEIGHT" << std::endl;
        std::cout << "width widget : " << size().width() << std::endl;
        std::cout << "height widget : " << size().height() << std::endl;
        std::cout << "image width : " << m_image->size().width() << std::endl;
        std::cout << "image height : " << m_image->size().height() << std::endl;

        if (m_image->size().width() >= size().width()) {
            std::cout << "JE SUIS LA" << std::endl;
            ratio = (float)m_image->size().width() / (float)size().width();
        }
        else {
            std::cout << "JE SUIS ICI" << std::endl;
            ratio = (float)size().width() / (float)m_image->size().width();
        }

        m_image->setFixedWidth(size().width());
        m_image->setFixedHeight(static_cast<int>(m_image->size().height()*ratio));

        std::cout << "ratio : " << ratio << std::endl;
        std::cout << "image width after : " << m_image->size().width() << std::endl;
        std::cout << "image height after : " << static_cast<int>(m_image->size().height()*ratio)<< std::endl;
    } else {
        std::cout << "IF WIDTH < HEIGHT" << std::endl;
        std::cout << "width widget : " << size().width() << std::endl;
        std::cout << "height widget : " << size().height() << std::endl;
        std::cout << "image width : " << m_image->size().width() << std::endl;
        std::cout << "image height : " << m_image->size().height() << std::endl;

        if (m_image->size().height() >= size().height()) {
            std::cout << "JE SUIS LA-BAS" << std::endl;
            ratio = (float)m_image->size().height() / (float)size().height();
        }
        else {
            std::cout << "JE SUIS ICI-BAS" << std::endl;
            ratio = (float)size().height() / (float)m_image->size().height();
        }

        m_image->setFixedWidth(static_cast<int>(m_image->size().width()*ratio));
        m_image->setFixedHeight(size().height());

        std::cout << "ratio : " << ratio << std::endl;
        std::cout << "image width after : " << static_cast<int>(m_image->size().width()*ratio) << std::endl;
        std::cout << "image height after : " << m_image->size().height() << std::endl;
    }

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    QPixmap pm(path.c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);
    update();
}

