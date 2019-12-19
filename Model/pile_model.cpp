#include "pile_model.h"
#include <json/json.h>
#include "gestionnaire_calques_model.h"
#include <iostream>

#define PATH "../../Resources/Config/config.json"

//=======================================================

//                  CONSTRUCTOR

//=======================================================

std::string pile_model::getFileName() const
{
    return fileName;
}

pile_model::pile_model()
{
    currentImageIndex = 0;
    fileIsLoaded = false;
}

//=======================================================

//                  GETTERS AND SETTERS

//=======================================================

void pile_model::loadNewFilename(std::string filename)
{
    fileName = filename;
    load(filename);
    fileIsLoaded = true;
    //=======================
    // Configure the project
    //=======================

    //TODO
    //    read_json_config();
}

CImg<float> pile_model::getImageAtIndex(int i) { return images[i]; }
int pile_model::getCurrentImageIndex() { return currentImageIndex; }
void pile_model::setCurrentImageIndex(int index) { currentImageIndex  = index; }
void pile_model::setPercentageOfBlack(float value) { percentageOfBlack = value; }
CImgList<float> pile_model::getImages() const { return images; }
CImg<float> pile_model::getCurrentImage() const { return currentImage; }
void pile_model::setCurrentImage(int position){ currentImage = images[position]; }
std::vector<string> pile_model::getIconFilenames() { return images_icons_filename; }
bool pile_model::fileReady() { return fileIsLoaded; }

//=======================================================

//                  METHODS

//=======================================================

void pile_model::read_json_config(){
    Json::Value config;

    std::ifstream config_file(PATH, std::ifstream::binary);
    config_file >> config;

    if(config["black"] != Json::Value::null){
        percentageOfBlack = config["black"].asFloat();
    }else{
        percentageOfBlack = 100.0;
    }

    if(config["green"] != Json::Value::null){
        isGreen = config["green"].asBool();
    }else{
        isGreen = false;
    }

    if(config["annotation"] != Json::Value::null){
        isDisplayingAnnotation = config["annotation"].asBool();
    }else{
        isDisplayingAnnotation = true;
    }

    if(config["contour"] != Json::Value::null){
        isDisplayingContour = config["contour"].asBool();
    }else{
        isDisplayingContour = false;
    }
}

void pile_model::load(string path)
{
    images.clear();
    images_icons_filename.clear();
    images.load_tiff(path.c_str());

    //Enregistrement dans un fichier temporaire
    for (unsigned int i=0; i<images.size(); i++)
    {
        CImg<float> img = images[i];

        std::string chemin = "tmp/" + std::to_string(i) + ".bpm";
        img.save_bmp(chemin.c_str());         // problem here
        images_icons_filename.push_back(chemin);
    }

    currentImage = images[0];

    //Obtention de l'image aplatie
    //TODO LE MULTIPLATFORME
    std::string command = "convert " + path + " -flatten tmp/flatten.bmp";
    system(command.c_str());

    return;

}

void pile_model::save(string path)
{

}

