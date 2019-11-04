#include "zoom_view.h"

Zoom_View::Zoom_View( QWidget * parent) : QLabel( parent )
{

}

/**
 * @brief Zoom_View::setNewPicture Affiche l'image située au path dans la fenêtre
 * @param path
 */
void Zoom_View::setNewPicture(std::string path)
{
    QPixmap pm(path.c_str());
    this->setPixmap(pm);
    this->setScaledContents(true);
    update();
}

