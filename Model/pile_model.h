#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#define cimg_use_tiff
#include "CImg.h"

class image_model;
using namespace cimg_library;
using namespace std;


class pile_model
{
private:
    CImgList<float> images;
    CImg<float> currentImage;
    std::vector<image_model> images_modified;
    std::vector<std::string> images_icons_filename; //Le nom des fichiers utilisés pour affichage dans la pile

    std::string fileName;
    std::string pathOfResultsDisplay = "tmp/resultDisplay.bmp";
    float percentageOfBlack;        //Put the limit of percentage of black for treatment.
    bool isGreen;                   //To display the image with white or green
    bool isDisplayingAnnotation;    //To display or hide annotation on the image
    bool isDisplayingContour;       //To display or hide Contour on the image


public:
    pile_model();

    void loadNewFilename(std::string filename);
    void setCurrentImage(int position);
    void load(string path);
    void save(string path);
    void read_json_config();

//===================
//      Getter
//===================

    CImgList<float> getImages() const;
    CImg<float> getCurrentImage() const;
    std::vector<string> getIconFilenames();
    CImg<float> getImageAtIndex(int i) const;
    std::string getMainDisplayPath() const;
    std::string getZoomDisplayPath() const;
    std::string getResultDisplayPath() const;


//===================
//      Setter
//===================

    void setPercentageOfBlack(float value);

//===================
//      Methods
//===================



};
