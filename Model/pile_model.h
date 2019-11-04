#pragma once

#include <vector>
#include <iostream>
#include <json/json.h>
#include <fstream>

//defini dans le cmake
//#define cimg_use_tiff
#include "image_model.h"


using namespace cimg_library;
using namespace std;


class pile_model
{
private:
    CImgList<float> images;
    CImg<float> currentImage;
    std::vector<image_model> images_modified;

    std::string fileName;
    float percentageOfBlack;        //Put the limit of percentage of black for treatment.
    bool isGreen;                   //To display the image with white or green
    bool isDisplayingAnnotation;    //To display or hide annotation on the image
    bool isDisplayingContour;       //To display or hide Contour on the image


public:
    pile_model(string filename);

    void setCurrentImage(int position);
    void load(string path);
    void save(string path);
    void read_json_config();

//===================
//      Getter
//===================

    CImgList<float> getImages() const;
    CImg<float> getCurrentImage() const;

//===================
//      Setter
//===================

    void setPercentageOfBlack(float value);

//===================
//      Methods
//===================



};
