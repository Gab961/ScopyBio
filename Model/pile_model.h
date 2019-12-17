#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#define cimg_use_tiff
#include "CImg.h"

#include "../definition.h"

#include "gestionnaire_calques_model.h"

class gestionnaire_calque_model;
using namespace cimg_library;
using namespace std;

#include <string>


class pile_model
{
private:
    CImgList<float> images;
    CImg<float> currentImage;
    int currentImageIndex;
    gestionnaire_calque_model gestionnaire_calque;
    std::vector<std::string> images_icons_filename; //Le nom des fichiers utilisés pour affichage dans la pile

    std::string fileName;
    float percentageOfBlack;        //Put the limit of percentage of black for treatment.
    bool isGreen;                   //To display the image with white or green
    bool isDisplayingAnnotation;    //To display or hide annotation on the image
    bool isDisplayingContour;       //To display or hide Contour on the image
    bool fileIsLoaded;


public:
    pile_model();

    void loadNewFilename(std::string filename);
    void load(string path);
    void loadProject(std::string path);
    void save(string path);
    void read_json_config();

    //===================
    //      Getter
    //===================

    CImgList<float> getImages() const;
    CImg<float> getCurrentImage() const;
    int getCurrentImageIndex();
    std::vector<string> getIconFilenames();
    CImg<float> getImageAtIndex(int i);
    std::string getMainDisplayPath() const;
    std::string getZoomDisplayPath() const;
    std::string getResultDisplayPath() const;
    bool fileReady();
    std::string getFileName() const;


    //===================
    //      Setter
    //===================

    void setPercentageOfBlack(float value);
    void setCurrentImage(int position);
    void setCurrentImageIndex(int index);

    //===================
    //      Methods
    //===================



};
