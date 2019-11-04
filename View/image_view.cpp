#include "image_view.h"
#include <iostream>
#include <QMouseEvent>
#include <QDateTime>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Image_View::Image_View( QWidget * parent) : QLabel( parent )
{
    // TODO ALIGNEMENT CNTRE VERTICAL
    m_image = new QLabel(this);
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
void Image_View::setNewPicture(std::string path)
{
    // Largeur du widget <= hauteur
    // Sert à créer une image qui va prendre un maximum de place possible
    // sans empiéter sur les autres widgets
    if (size().width() <= size().height()) {
        std::cout << "IF WIDTH <= HEIGHT" << std::endl;
        std::cout << "width widget : " << size().width() << std::endl;
        float ratio = size().width() / 514.0;
        std::cout << "ratio : " << ratio << std::endl;
        m_image->setFixedWidth(size().width());
        std::cout << "image width : " << m_image->size().width() <<std::endl;
        m_image->setFixedHeight(static_cast<int>(476*ratio));
        std::cout << "height widget : " << size().height() << std::endl;
        std::cout << "image height : " << static_cast<int>(476*ratio)<< std::endl;
    } else {
        std::cout << "IF HEIGHT < WIDTH" << std::endl;
        std::cout << "height widget : " << size().height() << std::endl;
        float ratio = size().height() / 476.0;
        std::cout << "ratio : " << ratio << std::endl;
        m_image->setFixedHeight(size().height());
        std::cout << "image height : " << m_image->size().height() <<std::endl;
        m_image->setFixedWidth(514*ratio);
        std::cout << size().width() << std::endl;
        std::cout << 514*ratio << std::endl;
        std::cout << "width widget : " << size().width() << std::endl;
        std::cout << "image width : " << 514*ratio << std::endl;
    }

    this->path = path;
    QPixmap pm(path.c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);
    update();
}

void Image_View::nouveauClicCreerRectangle(QPoint pos1, QPoint pos2)
{
    CImg<float> img;
    img.load_bmp(path.c_str());

    const unsigned char color[] = { 255,174,0 };

    int x1 = pos1.x();
    int y1 = pos1.y();
    int x2 = pos2.x();
    int y2 = pos2.y();

    //Gestion des positions
    if (x1 > x2)
    {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y1 > y2)
    {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
    }

    if (x1<0)
        x1 = -1;
    if (y1 < 0)
        y1 = -1;
    if (x2 > img.width())
        x2 = img.width();
    if (y2 > img.height())
        y2 = img.height();

    //Dessin du rectangle et affichage sur l'image principale
    img.draw_rectangle(x1,y1,x2,y2,color,1,~0U);
    img.save_bmp(pathOfMainDisplay.c_str());
    setNewPicture(pathOfMainDisplay);

    //Création de l'image zoomée et demande d'affichage dans la partie zoomée
    CImg<float> zoom = img.get_crop(x1+1,y1+1,0,x2-1,y2-1,0);
    zoom.resize(476,514);
    zoom.save_bmp(pathOfZoomedDisplay.c_str());
    emit changeZoomedPicture(pathOfZoomedDisplay);

    //    testDataOnZoom(x1,x2,y1,y2);

    update();
}
