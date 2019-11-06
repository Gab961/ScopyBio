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
    void applyGreenFilter(CImg<float> picture);
    void removeGreenFilter(CImg<float> picture);

private:
    std::string pathOfMainDisplay = "tmp/mainDisplay.bmp";
    std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";
};
