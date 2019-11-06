#pragma once
#include <string>
#include <vector>

#define cimg_use_tiff
#include "CImg.h"

class QPoint;
using namespace cimg_library;

class data_model
{
public:
    data_model();
    std::string getResultDisplayPath() const;
    std::vector<int> getResults() const;
    void processResultsWithCrops(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void processResults(CImgList<float> allPictures);
    void createResultsDisplay();
    int calculPlacementY(int imageHeight, int y);
    int getItemAtPoint(int posX, int labelWidth);
    bool dataReady();

private:
    bool isDataReady;

    std::string pathOfResultsDisplay = "tmp/resultDisplay.bmp";
    std::vector<int> results;
};

