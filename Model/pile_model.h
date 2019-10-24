#ifndef PILE_MODEL_H
#define PILE_MODEL_H

#include <vector>
#include <iostream>
#include <fstream>

//defini dans le cmake
//#define cimg_use_tiff
#include "../CImg.h"


using namespace cimg_library;
using namespace std;

class pile_model
{
private:
    CImgList<float> images;
    CImg<float> currentImages;

public:
    pile_model();
    pile_model(string filename);
    void load(string path);
    void save(string path);
};

#endif // PILE_MODEL_H
