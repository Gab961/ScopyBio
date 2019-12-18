#include <QPoint>
#include <iostream>
#include "dessin_model.h"

dessin_model::dessin_model() : zoomReady(false), baseColorGiven(false), listenPipetteClick(false), whiteColor(0)
{}

CImg<float> dessin_model::dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> & currentPicture)
{
    const unsigned char color[] = { 255,174,0,255 };

    int x1 = pos1.x() * currentPicture.width() / labelWidth;
    int y1 = pos1.y() * currentPicture.height() / labelHeight;
    int x2 = pos2.x() * currentPicture.width() / labelWidth;
    int y2 = pos2.y() * currentPicture.height() / labelHeight;

    if (x1<0)
        x1 = -1;
    if (y1 < 0)
        y1 = -1;
    if (x2 > currentPicture.width())
        x2 = currentPicture.width();
    if (y2 > currentPicture.height())
        y2 = currentPicture.height();

    currentPicture.draw_rectangle(x1,y1,x2,y2,color,1,~0U);

    return currentPicture;
}

CImg<float> dessin_model::dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence, CImg<float> & currentPicture)
{
    //Clair
    const unsigned char color1[] = { 136,255,136,50 };
    //Moyen
    const unsigned char color2[] = { 71,255,71,75 };
    //Foncé
    const unsigned char color3[] = { 0,255,0,100 };

    switch (pertinence) {
    case 1:
        currentPicture.draw_rectangle(pos1.x(),pos1.y(),pos2.x(),pos2.y(),color1,~0U);
        break;
    case 2:
        currentPicture.draw_rectangle(pos1.x(),pos1.y(),pos2.x(),pos2.y(),color2,~0U);
        break;
    case 3:
        currentPicture.draw_rectangle(pos1.x(),pos1.y(),pos2.x(),pos2.y(),color3,~0U);
        break;
    default:
        break;
    }

    return currentPicture;
}

CImg<float> dessin_model::dessinerRond(QPoint pos1, int labelWidth, int labelHeight, CImg<float> & currentPicture)
{
    const unsigned char color[] = { 255,174,0,255 };

    int x1 = pos1.x() * currentPicture.width() / labelWidth;
    int y1 = pos1.y() * currentPicture.height() / labelHeight;

    currentPicture.draw_circle(x1,y1,3,color,1);

    return currentPicture;
}

CImg<float> dessin_model::dessinerRond(QPoint pos, int pertinence, CImg<float> & currentPicture)
{
    const unsigned char color1[] = { 255,0,0,255 };
    const unsigned char color2[] = { 255,39,39,255 };
    const unsigned char color3[] = { 255,71,71,255 };
    const unsigned char color4[] = { 255,102,102,255 };
    const unsigned char color5[] = { 255,136,136,255 };


    switch (pertinence) {
    case 1:
        currentPicture.draw_circle(pos.x(),pos.y(),10,color5,1);
        break;
    case 2:
        currentPicture.draw_circle(pos.x(),pos.y(),10,color4,1);
        break;
    case 3:
        currentPicture.draw_circle(pos.x(),pos.y(),10,color3,1);
        break;
    case 4:
        currentPicture.draw_circle(pos.x(),pos.y(),10,color2,1);
        break;
    case 5:
        currentPicture.draw_circle(pos.x(),pos.y(),10,color1,1);
        break;
    default:
        break;
    }

    return currentPicture;
}


CImg<float> dessin_model::dessinerLigne(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> & currentPicture)
{
    const unsigned char color[] = { 255,0,0,255 };

    int x1 = pos1.x() * currentPicture.width() / labelWidth;
    int y1 = pos1.y() * currentPicture.height() / labelHeight;
    int x2 = pos2.x() * currentPicture.width() / labelWidth;
    int y2 = pos2.y() * currentPicture.height() / labelHeight;

    if (x1<0)
        x1 = -1;
    if (y1 < 0)
        y1 = -1;
    if (x2 > currentPicture.width())
        x2 = currentPicture.width();
    if (y2 > currentPicture.height())
        y2 = currentPicture.height();

    currentPicture.draw_line(x1,y1,x2,y2,color,1,~0U);

    return currentPicture;
}

void dessin_model::saveZoomFromPicture(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> currentPicture)
{
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

    //Création de l'image zoomée et demande d'affichage dans la partie zoomée
    CImg<float> zoom = currentPicture.get_crop(x1+1,y1+1,0,x2-1,y2-1,0);

    zoom.save_bmp(pathOfZoomedDisplay.c_str());

    zoomReady = true;
}

void dessin_model::saveZoomFromArea(QPoint posTopLeft, QPoint posBottomRight, CImg<float> currentPicture)
{
    //Création de l'image zoomée et demande d'affichage dans la partie zoomée
    CImg<float> zoom = currentPicture.get_crop(posTopLeft.x(),posTopLeft.y(),0,posBottomRight.x(),posBottomRight.y(),0);

    zoom.save_bmp(pathOfZoomedDisplay.c_str());

    zoomReady = true;
}

void dessin_model::savePics(int x1, int y1, int x2, int y2, unsigned char color, CImg<float> currentPicture){

    //Dessin du rectangle et affichage sur l'image principale
    //currentPicture.draw_rectangle(x1,y1,x2,y2,color,1,~0U);
    currentPicture.save_bmp(pathOfMainDisplay.c_str());
}

CImg<float> dessin_model::applyGreenFilter(CImg<float> picture)
{
    const unsigned char green[] = { 0,150,0,150 };
    picture.draw_rectangle(0,0,picture.width(),picture.height(),green);

    return picture;
}

CImg<float> dessin_model::applyQuadrillageFilter(int columns, int lines, CImg<float> picture)
{
    const unsigned char color[] = { 255,0,0,255 };

    int hauteur = picture.height();
    int largeur = picture.width();

    float xSeparateurFloat = (float)largeur / (float)columns;
    float ySeparateurFloat = (float)hauteur / (float)lines;

    float xSeparateur = (int)xSeparateurFloat;
    float ySeparateur = (int)ySeparateurFloat;

    int oldX = 0;

    for (int i=0; i<columns; i++)
    {
        if (i == columns)
            oldX = largeur;
        picture.draw_line(oldX,0,oldX,hauteur,color,1,~0U);
        oldX = oldX + xSeparateur;
    }

    int oldY = 0;
    for (int j=0; j<lines; j++)
    {
        if (j == lines)
            oldY = hauteur;
        picture.draw_line(0,oldY,largeur, oldY, color,1,~0U);
        oldY = oldY + ySeparateur;
    }

    return picture;
}

/**
 * Source du code: https://github.com/HYPJUDY/histogram-equalization-on-grayscale-and-color-image/edit/master/histogram_equalization.cpp
 * @brief dessin_model::applyHistogramFilter
 * @param picture
 */
CImg<float> dessin_model::applyHistogramFilter(CImg<float> picture)
{
    CImg<unsigned int> input_img;
    input_img = picture;
    int L = 256; // number of grey levels used
    int w = input_img.width();
    int h = input_img.height();
    int number_of_pixels = w * h;

    double cdf[256] = { 0 };
    unsigned int equalized[256] = { 0 };

    CImg<unsigned int> histogram(256, 1, 1, 1, 1);
    cimg_forXY(input_img, x, y)
            ++histogram[input_img(x, y)];

    int count = 0;
    cimg_forX(histogram, pos) { // calculate cdf and equalized transform
        count += histogram[pos];
        cdf[pos] = 1.0 * count / number_of_pixels;
        equalized[pos] = round(cdf[pos] * (L - 1));
    }

    CImg<unsigned int> output_img(w, h, 1, 1, 0);
    cimg_forXY(output_img, x, y)
            output_img(x, y, 0) = equalized[input_img(x, y)];

    return output_img;
}

void dessin_model::manageNewWhiteColor(QPoint pos, int labelWidth, int labelHeight, bool zoomView)
{
    CImg<float> picture;
    if (zoomView)
        picture.load_bmp(pathOfZoomedDisplay.c_str());
    else
        picture.load_bmp(pathOfMainDisplay.c_str());
    int realX = pos.x() * picture.width() / labelWidth;
    int realY = pos.y() * picture.height() / labelHeight;


    whiteColor = (int)picture(realX, realY, 0, 0);
    baseColorGiven = true;
}


void dessin_model::manageNewWhiteColor(int newWhite)
{
    whiteColor = newWhite;
    baseColorGiven = true;
}

void dessin_model::switchSaveLocation()
{
    std::string newPath = "tmp/mainDisplay/mainDisplay" + std::to_string(pathOfMainDisplayIndex) + ".bmp";
    pathOfMainDisplayIndex++;

    if (pathOfMainDisplayIndex == 30)
        pathOfMainDisplayIndex = 0;

    pathOfMainDisplay = newPath;
}

void dessin_model::saveImageAsMainDisplay(CImg<float> pictureToShow) { pictureToShow.save_bmp(pathOfMainDisplay.c_str()); }
std::string dessin_model::getMainDisplayPath() const { return pathOfMainDisplay; }
std::string dessin_model::getZoomDisplayPath() const { return pathOfZoomedDisplay; }
int dessin_model::getWhiteValue() const { return whiteColor; }
void dessin_model::setWhiteValue(int color) { whiteColor = color; }
bool dessin_model::getListenPipetteClick() const { return listenPipetteClick; }
void dessin_model::setListenPipetteClick(bool pipetteClick) { listenPipetteClick = pipetteClick; }
bool dessin_model::getZoomReady() const { return zoomReady; }
bool dessin_model::getBaseColorGiven() const { return baseColorGiven; }
void dessin_model::setBaseColorGiven() { baseColorGiven = true; }
