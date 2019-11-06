#include <QPoint>
#include <iostream>
#include "dessin_model.h"

dessin_model::dessin_model() : whiteColor(200)
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

void dessin_model::applyGreenFilter(CImg<float> picture)
{
    const unsigned char green[] = { 0,150,0 };
    picture.draw_rectangle(0,0,picture.width(),picture.height(),green,0.5);
    picture.save_bmp(pathOfMainDisplay.c_str());
}

void dessin_model::removeGreenFilter(CImg<float> picture)
{
    //TODO VIRER LE CALQUE
    picture.save_bmp(pathOfMainDisplay.c_str());
}

/**
 * Source du code: https://github.com/HYPJUDY/histogram-equalization-on-grayscale-and-color-image/edit/master/histogram_equalization.cpp
 * @brief dessin_model::applyHistogramFilter
 * @param picture
 */
void dessin_model::applyHistogramFilter(CImg<float> picture)
{
    CImg<unsigned int> input_img;
    input_img = picture;
    int L = 256; // number of grey levels used
    int w = input_img.width();
    int h = input_img.height();
    int number_of_pixels = w * h;

    double cdf[256] = { 0 };
    unsigned int equalized[256] = { 0 };

    CImg<unsigned int> histogram(256, 1, 1, 1, 0);
    cimg_forXY(input_img, x, y)
            ++histogram[input_img(x, y)];

    int count = 0;
    cimg_forX(histogram, pos) { // calculate cdf and equalized transform
        count += histogram[pos];
        cdf[pos] = 1.0 * count / number_of_pixels;
        equalized[pos] = round(cdf[pos] * (L - 1));
    }

    CImg<unsigned int> output_img(w, h, 1, 1, 0);
    cimg_forXY(output_img, x, y) // calculate histogram equalization result
        output_img(x, y, 0) = equalized[input_img(x, y)];

    output_img.save_bmp(pathOfMainDisplay.c_str());
}

void dessin_model::removeHistogramFilter(CImg<float> picture)
{
    //TODO VIRER LE CALQUE
    picture.save_bmp(pathOfMainDisplay.c_str());
}

void dessin_model::manageNewWhiteColor(QPoint pos, int labelWidth, int labelHeight)
{
    std::cout << "Point initial: " << pos.x() << "," << pos.y() << std::endl;
    CImg<float> zoomPicture;
    zoomPicture.load_bmp(pathOfZoomedDisplay.c_str());
    int realX = pos.x() * zoomPicture.width() / labelWidth;
    int realY = pos.y() * zoomPicture.height() / labelHeight;

    std::cout << "Point modifie: " << realX << "," << realY << std::endl;

    int nuance = (int)zoomPicture(realX, realY, 0, 0);
    std::cout << "Nuance = " << nuance << std::endl;
}

void dessin_model::saveImageAsMainDisplay(CImg<float> pictureToShow) { pictureToShow.save_bmp(pathOfMainDisplay.c_str()); }
std::string dessin_model::getMainDisplayPath() const { return pathOfMainDisplay; }
std::string dessin_model::getZoomDisplayPath() const { return pathOfZoomedDisplay; }
int dessin_model::getWhiteValue() const { return whiteColor; }
void dessin_model::setWhiteValue(int color) { whiteColor = color; }
