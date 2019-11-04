#include "zoom_view.h"
#include <iostream>

Zoom_View::Zoom_View( QWidget * parent) : QLabel( parent )
{

}

/**
 * @brief Zoom_View::setNewPicture Affiche l'image située au path dans la fenêtre
 * @param path
 */
void Zoom_View::setNewPicture(std::string path)
{
    std::cout << "Coucou ici" << std::endl;

    QPixmap pm(path.c_str());
    this->setPixmap(pm);
    this->setScaledContents(true);
    update();
}

