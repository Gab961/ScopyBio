#pragma once
#include <string>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;
class QPoint;

class dessin_model
{
public:
    dessin_model();
    std::string getMainDisplayPath() const;
    std::string getZoomDisplayPath() const;
    CImg<float> dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> &currentPicture);
    void savePics(int x1, int y1, int x2, int y2, unsigned char color, CImg<float> currentPicture);
    void saveImageAsMainDisplay(CImg<float> pictureToShow);

    //Filtres
    CImg<float> applyGreenFilter(CImg<float> picture);
    void removeGreenFilter(CImg<float> picture);    
    void applyHistogramFilter(CImg<float> picture);
    void removeHistogramFilter(CImg<float> picture);

    void manageNewWhiteColor(QPoint pos, int labelWidth, int labelHeight, bool zoomView);
    int getWhiteValue() const;
    void setWhiteValue(int color);
    bool getListenPipetteClick() const;
    void setListenPipetteClick(bool pipetteClick);
    void saveZoomFromPicture(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> currentPicture);
    bool getZoomReady() const;

private:
    std::string pathOfMainDisplay = "tmp/mainDisplay.bmp";
    std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";
    bool zoomReady;

    int whiteColor;
    bool listenPipetteClick;
};
