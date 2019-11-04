#include "image_view.h"
#include <iostream>
#include <QMouseEvent>
#include <QDateTime>

Image_View::Image_View( QWidget * parent) : QLabel( parent )
{
    TEMPS_CLIC_LONG=100;
}


void Image_View::mousePressEvent( QMouseEvent* ev )
{
    temps_pression_orig = QDateTime::currentMSecsSinceEpoch();
    origPoint = ev->pos();
}

/**
 * @brief Image_View::mouseReleaseEvent
 * Dans le cas d'un clic court, on demande l'affichage d'un point
 * Dans le cas d'un clic long, on demande l'affichage d'un rectangle entre le point de début et le point de fin
 * @param ev
 */
void Image_View::mouseReleaseEvent( QMouseEvent* ev )
{
    quint64 temps = QDateTime::currentMSecsSinceEpoch() - temps_pression_orig;

    //Si c'est un clic court
    if (temps < TEMPS_CLIC_LONG)
    {
        emit drawCircleOnMouse(origPoint);
    }
    else
    {
        QPoint secondPoint = ev->pos();
        emit drawRectOnMouse(origPoint,secondPoint);
    }
}

/**
 * @brief Image_View::setNewPicture Modifie l'image affichée dans le label par l'image située au chemin donné
 * @param path
 */
void Image_View::setNewPicture(std::string path)
{
    QPixmap pm(path.c_str());
    this->setPixmap(pm);
    this->setScaledContents(true);
    update();
}
