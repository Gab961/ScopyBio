#include "pile_model.h"
#include <json/json.h>
#include "image_model.h"
#include <iostream>

#define PATH "../../Config/config.json"

//=======================================================

//                  CONSTRUCTOR

//=======================================================

pile_model::pile_model()
{}

//=======================================================

//                  GETTERS AND SETTERS

//=======================================================

void pile_model::loadNewFilename(std::string filename)
{
    std::cout << "Test modèle: " << filename << std::endl;
    fileName = filename;
    load(filename);

    //=======================
    // Configure the project
    //=======================

    //    read_json_config();
}

void pile_model::setPercentageOfBlack(float value) { percentageOfBlack = value; }

CImgList<float> pile_model::getImages() const { return images; }
CImg<float> pile_model::getCurrentImage() const { return currentImage; }
CImg<float> pile_model::getImageAtIndex(int i) const { return images[i]; }
void pile_model::setCurrentImage(int position){ currentImage = images[position]; }
std::vector<string> pile_model::getIconFilenames() { return images_icons_filename; }
std::string pile_model::getResultDisplayPath() const { return pathOfResultsDisplay; }

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
    images.load_tiff(path.c_str());

    //Enregistrement dans un fichier temporaire
    for (unsigned int i=0; i<images.size(); i++)
    {
        CImg<float> img = images[i];

        //TODO TBD où on l'enregistre
        std::string chemin = "tmp/" + std::to_string(i) + ".bpm";
        img.save_bmp(chemin.c_str());
        images_icons_filename.push_back(chemin);
    }

    currentImage = images[0];

    return;

}

void pile_model::save(string path)
{
    for(auto img : images_modified){
        img.save(path);
    }
}

