#include "image_view.h"
#include <iostream>
#include <QMouseEvent>
#include <QDateTime>
#include "scopybio_controller.h"

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Image_View::Image_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QLabel( parent ), m_scopybioController(scopybioController)
{
    TEMPS_CLIC_LONG=100;

    //Affichage du rectangle
    QObject::connect(this, &Image_View::drawRectOnMouse, this, &Image_View::nouveauClicCreerRectangle);
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
void Image_View::setNewPicture()
{
    QPixmap pm(m_scopybioController->getMainDisplayPath().c_str());
    this->setPixmap(pm);
    this->setScaledContents(true);
    update();
}

void Image_View::nouveauClicCreerRectangle(QPoint pos1, QPoint pos2)
{
    //Dessine le rectangle sur l'image et créer l'image zoomée
    m_scopybioController->dessinerRectangle(pos1, pos2);
    setNewPicture();

    //Demande de rafraichir le zoom
    emit changeZoomedPicture();

    update();
}
