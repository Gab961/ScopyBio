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
    void dessinerRectangle(QPoint pos1, QPoint pos2, CImg<float> currentPicture);


private:
    std::string pathOfMainDisplay = "tmp/mainDisplay.bmp";
    std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";
};
