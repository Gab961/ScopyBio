#include <QPoint>
#include <iostream>
#include "dessin_model.h"

dessin_model::dessin_model()
{}

void dessin_model::dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> currentPicture)
{
    const unsigned char color[] = { 255,174,0 };

    int x1 = pos1.x() * currentPicture.width() / labelWidth;
    int y1 = pos1.y() * currentPicture.height() / labelHeight;
    int x2 = pos2.x() * currentPicture.width() / labelWidth;
    int y2 = pos2.y() * currentPicture.height() / labelHeight;

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
    if (x2 > currentPicture.width())
        x2 = currentPicture.width();
    if (y2 > currentPicture.height())
        y2 = currentPicture.height();

    //Dessin du rectangle et affichage sur l'image principale
    currentPicture.draw_rectangle(x1,y1,x2,y2,color,1,~0U);
    currentPicture.save_bmp(pathOfMainDisplay.c_str());

    //Création de l'image zoomée et demande d'affichage dans la partie zoomée
    CImg<float> zoom = currentPicture.get_crop(x1+1,y1+1,0,x2-1,y2-1,0);
    zoom.resize(476,514);
    zoom.save_bmp(pathOfZoomedDisplay.c_str());
}

void dessin_model::saveImageAsMainDisplay(CImg<float> pictureToShow) { pictureToShow.save_bmp(pathOfMainDisplay.c_str()); }
std::string dessin_model::getMainDisplayPath() const { return pathOfMainDisplay; }
std::string dessin_model::getZoomDisplayPath() const { return pathOfZoomedDisplay; }
