#ifndef PILE_MODEL_H
#define PILE_MODEL_H

#include <vector>
#include <iostream>
#include <json/json.h>
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

    float percentageOfBlack;        //Put the limit of percentage of black for treatment.
    bool isGreen;                   //To display the image with white or green
    bool isDisplayingAnnotation;    //To display or hide annotation on the image
    bool isDisplayingContour;       //To display or hide Contour on the image


public:
    pile_model();
    pile_model(string filename);
    void load(string path);
    void save(string path);


    void setPercentOfBlack(float black); //TODO

    void putColorGreen();//TODO
    void putColorWhite();//TODO

    void displayAnnotation();//TODO
    void hideAnnotation();//TODO

    void displayContour();//TODO
    void hideContour();//TODO
};

#endif // PILE_MODEL_H
