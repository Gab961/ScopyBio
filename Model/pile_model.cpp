#include "pile_model.h"

#define PATH "../../Config/config.json"


//=======================================================

//                  CONSTRUCTOR

//=======================================================

pile_model::pile_model(string filename)
{
    fileName = filename;
    load(filename);

    //=======================
    // Configure the project
    //=======================

    read_json_config();

}

//=======================================================

//                  GETTERS AND SETTERS

//=======================================================

void pile_model::setPercentageOfBlack(float value)
{
    percentageOfBlack = value;
}

CImgList<float> pile_model::getImages() const
{
    return images;
}


CImg<float> pile_model::getCurrentImage() const
{
    return currentImage;
}

void pile_model::setCurrentImage(int position){
    currentImage = images[position];
}

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
    ifstream file (path, std::ifstream::in | std::ifstream::binary);;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

      images.clear();

      images.load_tiff(path.c_str());

      currentImage = images[0];

      file.close();

    return;

}

void pile_model::save(string path)
{
    for(auto img : images_modified){
        img.save(path);
    }
}

