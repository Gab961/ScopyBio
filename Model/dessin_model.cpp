#include <QPoint>
#include <iostream>
#include "dessin_model.h"
#include "definition.h"

dessin_model::dessin_model() : zoomReady(false), baseColorGiven(false), listenPipetteClick(false), whiteColor(0), penSize(5), shapeSize(10), textSize(10), eraserSize(10), circleIsSelected(true)
{
    pathOfMainDisplay = "tmp";
    pathOfMainDisplay += separator;
    pathOfMainDisplay += "mainDisplay";
    pathOfMainDisplay += separator;
    pathOfMainDisplay += "mainDisplay0.bmp";

    pathOfZoomedDisplay = "tmp";
    pathOfZoomedDisplay += separator;
    pathOfZoomedDisplay += "zoomedDisplay.bmp";
}

void dessin_model::init()
{
    shutdownAllListening();

    zoomReady = false;
    baseColorGiven = false;
    whiteColor = 0;
    penSize = 5;
    shapeSize = 10;
    textSize = 10;
    eraserSize = 10;
    circleIsSelected = true;
}

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

CImg<float> dessin_model::dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> & currentPicture)
{
    const unsigned char colorFaisceau[] = { 255,174,0,255 };
    const unsigned char colorMasque[] = { 200,200,255,150 };

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

    //Masque gris pour la zone non sélectionnée
    cimg_forXY(currentPicture,x,y) {

        if (
                //Si on est à gauche
                ((x1<x2 && x<x1) || (x2<x1 && x<x2)) ||
                //Si on est à droite
                ((x1<x2 && x>x2) || (x2<x1 && x>x1)) ||
                //Si on est en haut
                ((y1<y2 && y<y1) || (y2<y1 && y<y2)) ||
                //Si on est en bas
                ((y1<y2 && y>y2) || (y2<y1 && y>y1))
                )
            currentPicture.draw_point(x,y,colorMasque,1);
    }

    currentPicture.draw_rectangle(x1,y1,x2,y2,colorFaisceau,1,~0U);

    return currentPicture;
}

CImg<float> dessin_model::dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence, CImg<float> & currentPicture)
{
    //Clair
    const unsigned char color1[] = { 136,255,136,50 };
    //Moyen
    const unsigned char color2[] = { 71,255,71,100 };
    //Foncé
    const unsigned char color3[] = { 0,255,0,150 };

    switch (pertinence) {
    case 2:
        currentPicture.draw_rectangle(pos1.x(),pos1.y(),pos2.x(),pos2.y(),color1,~0U);
        break;
    case 3:
        currentPicture.draw_rectangle(pos1.x(),pos1.y(),pos2.x(),pos2.y(),color2,~0U);
        break;
    case 4:
        currentPicture.draw_rectangle(pos1.x(),pos1.y(),pos2.x(),pos2.y(),color3,~0U);
        break;
    default:
        break;
    }

    return currentPicture;
}

CImg<float> dessin_model::ecrireText(QPoint pos1, std::string text_a_ecrire, int fontSize, int labelWidth, int labelHeight, CImg<float> & currentPicture){
    const unsigned char color[] = { 255,0,255,255 };
    const unsigned char colorBackground[] = { 0,0,0,0 };

    int x1 = pos1.x() * currentPicture.width() / labelWidth;
    int y1 = pos1.y() * currentPicture.height() / labelHeight;

    currentPicture.draw_text(x1, y1, text_a_ecrire.c_str(), color, colorBackground, 1, fontSize);

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

CImg<float> dessin_model::dessinerCarre(QPoint posOrig, int diameter, int labelWidth, int labelHeight, CImg<float> & currentPicture)
{
    const unsigned char color[] = { 255,174,0,255 };

    int origX = posOrig.x() * currentPicture.width() / labelWidth;
    int origY = posOrig.y() * currentPicture.height() / labelHeight;

    int x1 = origX-diameter/2;
    int y1 = origY-diameter/2;
    int x2 = origX+diameter/2;
    int y2 = origY+diameter/2;

    currentPicture.draw_rectangle(x1,y1,x2,y2,color,1,~0U);

    return currentPicture;
}

CImg<float> dessin_model::dessinerCercle(QPoint posOrig, int diameter, int labelWidth, int labelHeight, CImg<float> & currentPicture)
{
    const unsigned char color[] = { 255,174,0,255 };

    int x1 = posOrig.x() * currentPicture.width() / labelWidth;
    int y1 = posOrig.y() * currentPicture.height() / labelHeight;

    currentPicture.draw_circle(x1,y1,diameter/2,color,1,~0U);

    return currentPicture;
}

CImg<float> dessin_model::dessinerLigne(QPoint pos1, QPoint pos2, bool isDrawing, int brushSize, int labelWidth, int labelHeight, CImg<float> & currentPicture)
{
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

    if (isDrawing)
        drawThickLine(currentPicture,x1,y1,x2,y2,brushSize,true);
    else
        drawThickLine(currentPicture,x1,y1,x2,y2,brushSize,false);

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

CImg<float> dessin_model::saveZoomFromArea(QPoint posTopLeft, QPoint posBottomRight, CImg<float> currentPicture)
{
    //Création de l'image zoomée et demande d'affichage dans la partie zoomée
    CImg<float> zoom = currentPicture.get_crop(posTopLeft.x(),posTopLeft.y(),0,posBottomRight.x(),posBottomRight.y(),0);

    zoomReady = true;

    return zoom;
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

void dessin_model::manageNewWhiteColor(QPoint pos, int labelWidth, int labelHeight, bool zoomView, CImg<float> currentImage)
{
    CImg<float> picture;
    if (zoomView)
        picture.load_bmp(pathOfZoomedDisplay.c_str());
    else
    {
        picture = currentImage;
    }
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
    std::string newPath = "tmp";
    newPath += separator;
    newPath += "mainDisplay";
    newPath += separator;
    newPath += "mainDisplay" + std::to_string(pathOfMainDisplayIndex) + ".bmp";

    pathOfMainDisplayIndex++;

    if (pathOfMainDisplayIndex == 30)
        pathOfMainDisplayIndex = 0;

    pathOfMainDisplay = newPath;
}

void dessin_model::shutdownAllListening()
{
    listenSelectionClick = false;
    listenEraserClick = false;
    listenPenClick = false;
    listenPipetteClick = false;
    listenShapeClick = false;
    listenTextClick = false;
    listenSelectionClick = false;
}

/** Source: https://stackoverflow.com/questions/5673448/can-the-cimg-library-draw-thick-lines **/
void dessin_model::drawThickLine(CImg<float>& image, const int x1, const int y1, const int x2, const int y2, const unsigned int line_width, bool isDrawing)
{

    unsigned char color[] = { 255,0,0,255 };
    unsigned char eraseColor[] = { 0,0,0,0 };

    if (x1 == x2 && y1 == y2) {
        return;
    }
    // Convert line (p1, p2) to polygon (pa, pb, pc, pd)
    const double x_diff = std::abs(x1 - x2);
    const double y_diff = std::abs(y1 - y2);
    const double w_diff = line_width / 2.0;

    const int x_adj = y_diff * w_diff / std::sqrt(std::pow(x_diff, 2) + std::pow(y_diff, 2));
    const int y_adj = x_diff * w_diff / std::sqrt(std::pow(x_diff, 2) + std::pow(y_diff, 2));

    // Points are listed in clockwise order, starting from top-left
    cimg_library::CImg<int> points(4, 2);
    points(0, 0) = x1 - x_adj;
    points(0, 1) = y1 + y_adj;
    points(1, 0) = x1 + x_adj;
    points(1, 1) = y1 - y_adj;
    points(2, 0) = x2 + x_adj;
    points(2, 1) = y2 - y_adj;
    points(3, 0) = x2 - x_adj;
    points(3, 1) = y2 + y_adj;

    if (isDrawing)
        image.draw_polygon(points, color);
    else
        image.draw_polygon(points, eraseColor);
}

void dessin_model::saveImageAsMainDisplay(CImg<float> pictureToShow) { pictureToShow.save_bmp(pathOfMainDisplay.c_str()); }
std::string dessin_model::getMainDisplayPath() const { return pathOfMainDisplay; }
std::string dessin_model::getZoomDisplayPath() const { return pathOfZoomedDisplay; }
int dessin_model::getWhiteValue() const { return whiteColor; }
bool dessin_model::getListenPipetteClick() const { return listenPipetteClick; }
void dessin_model::setListenPipetteClick(bool newValue) { shutdownAllListening(); listenPipetteClick = newValue; }
bool dessin_model::getListenPenClick() const { return listenPenClick; }
void dessin_model::setListenPenClick(bool newValue) { shutdownAllListening(); listenPenClick = newValue; }
bool dessin_model::getListenEraserClick() const { return listenEraserClick; }
void dessin_model::setListenEraserClick(bool newValue) { shutdownAllListening(); listenEraserClick = newValue; }
bool dessin_model::getListenShapeClick() const { return listenShapeClick; }
void dessin_model::setListenShapeClick(bool newValue) { shutdownAllListening(); listenShapeClick = newValue; }
bool dessin_model::getListenTextClick() const { return listenTextClick; }
void dessin_model::setListenTextClick(bool newValue) { shutdownAllListening(); listenTextClick = newValue; }
bool dessin_model::getListenSelectionClick() const { return listenSelectionClick; }
void dessin_model::setListenSelectionClick(bool newValue) { shutdownAllListening(); listenSelectionClick = newValue; }
bool dessin_model::getZoomReady() const { return zoomReady; }
bool dessin_model::getBaseColorGiven() const { return baseColorGiven; }
void dessin_model::setBaseColorGiven() { baseColorGiven = true; }
int dessin_model::getPenSize() { return penSize; }
void dessin_model::setPenSize(int newValue) { this->penSize = newValue; }
int dessin_model::getShapeSize() { return shapeSize; }
void dessin_model::setShapeSize(int newValue) { this->shapeSize = newValue; }
int dessin_model::getTextSize() { return textSize; }
void dessin_model::setTextSize(int newValue) { this->textSize = newValue; }
int dessin_model::getEraserSize() { return eraserSize; }
void dessin_model::setEraserSize(int newValue) { this->eraserSize = newValue; }
bool dessin_model::getCircleIsSelected() { return circleIsSelected; }
void dessin_model::setCircleIsSelected(bool newValue) { circleIsSelected = newValue; }
