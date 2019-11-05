#include "image_view.h"
#include <iostream>
#include <QMouseEvent>
#include <QDateTime>
#include "scopybio_controller.h"

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Image_View::Image_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController)
{
    setTitle("Main view");

    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    TEMPS_CLIC_LONG=100;

    //Affichage du rectangle
    QObject::connect(this, &Image_View::drawRectOnMouse, this, &Image_View::nouveauClicCreerRectangle);

    setLayout(m_layout);
}


void Image_View::mousePressEvent( QMouseEvent* ev )
{
    QSize tailleEntier = this->size();
    int tailleEntierLargeur = tailleEntier.width();
    int tailleEntierHauteur = tailleEntier.height();

    std::cout << "Taille entière = " << tailleEntierLargeur << "x" << tailleEntierHauteur << std::endl;

    QSize tailleLabel = m_image->size();
    int tailleLabelLargeur = tailleLabel.width();
    int tailleLabelHauteur = tailleLabel.height();

    std::cout << "Taille label = " << tailleLabelLargeur << "x" << tailleLabelHauteur << std::endl;

    temps_pression_orig = QDateTime::currentMSecsSinceEpoch();
    origPoint = ev->pos();

    std::cout << "Position cliquée = " << origPoint.x() << "x" << origPoint.y() << std::endl;

    origPoint.setX(origPoint.x()+m_image->x());
    origPoint.setY(origPoint.y()+m_image->y());


    std::cout << "Position du label = " << m_image->x() << "x" << m_image->y() << std::endl;


    std::cout << "Position MODIFIEE = " << origPoint.x() << "x" << origPoint.y() << std::endl;
}

/**
 * @brief Image_View::mouseReleaseEvent
 * Dans le cas d'un clic court, on demande l'affichage d'un point
 * Dans le cas d'un clic long, on demande l'affichage d'un rectangle entre le point de début et le point de fin
 * @param ev
 */
void Image_View::mouseReleaseEvent( QMouseEvent* ev )
{
    QSize tailleEntier = this->size();
    int tailleEntierLargeur = tailleEntier.width();
    int tailleEntierHauteur = tailleEntier.height();


    QSize tailleLabel = m_image->size();
    int tailleLabelLargeur = tailleLabel.width();
    int tailleLabelHauteur = tailleLabel.height();

    if (m_scopybioController->fileReady())
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

            secondPoint.setX(secondPoint.x()+m_image->x());
            secondPoint.setY(secondPoint.y()+m_image->y());
            emit drawRectOnMouse(origPoint,secondPoint);
        }
    }
}

/**
 * @brief Image_View::setNewPicture Modifie l'image affichée dans le label par l'image située au chemin donné
 * @param path
 */
void Image_View::setNewPicture()
{
    // Largeur du widget <= hauteur
    // Sert à créer une image qui va prendre un maximum de place possible
    // sans empiéter sur les autres widgets
    if (size().width() <= size().height()) {
        float ratio = size().width() / 514.0;
        m_image->setFixedWidth(size().width());
        m_image->setFixedHeight(static_cast<int>(476*ratio));
    } else {
        float ratio = size().height() / 476.0;
        m_image->setFixedHeight(size().height());
        m_image->setFixedWidth(static_cast<int>(514*ratio));
    }

    QPixmap pm(m_scopybioController->getMainDisplayPath().c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);

    update();
}

void Image_View::nouveauClicCreerRectangle(QPoint pos1, QPoint pos2)
{
    //Dessine le rectangle sur l'image et créer l'image zoomée
    m_scopybioController->dessinerRectangle(pos1, pos2);
    setNewPicture();

    //Demande de rafraichir le zoom
    int largeurZone = pos1.x() - pos2.x();
    if (largeurZone < 0) largeurZone = largeurZone * -1;
    int hauteurZone = pos1.y() - pos2.y();
    if (hauteurZone < 0) hauteurZone = hauteurZone * -1;
    emit changeZoomedPicture(largeurZone, hauteurZone);

    //Demande de calculer les résultats pour la zone
    emit processResults(pos1,pos2);

    update();
}
