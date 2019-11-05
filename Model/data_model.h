#pragma once
#include <string>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

class data_model
{
public:
    data_model();
    std::string getResultDisplayPath() const;

private:
    std::string pathOfResultsDisplay = "tmp/resultDisplay.bmp";
};

