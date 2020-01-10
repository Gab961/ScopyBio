#include "pile_model.h"
#include <json/json.h>
#include <iostream>
#include <filesystem>
#include "definition.h"

//=======================================================

//                  CONSTRUCTOR

//=======================================================

pile_model::pile_model()
{
    currentImageIndex = 0;
    fileIsLoaded = false;
}

//=======================================================

//                  GETTERS AND SETTERS

//=======================================================

std::string pile_model::getFileName() const{return fileName;}
CImg<float> pile_model::getImageAtIndex(int i) { return images[i]; }
int pile_model::getCurrentImageIndex() { return currentImageIndex; }
void pile_model::setCurrentImageIndex(int index) { currentImageIndex  = index; }
CImgList<float> pile_model::getImages() const { return images; }
CImg<float> pile_model::getCurrentImage() const { return currentImage; }
void pile_model::setCurrentImage(int position){ currentImage = images[position]; }
std::vector<string> pile_model::getIconFilenames() { return images_icons_filename; }
bool pile_model::fileReady() { return fileIsLoaded; }

//=======================================================

//                  METHODS

//=======================================================

void pile_model::loadNewFilename(std::string filename)
{
    fileName = filename;
    load(filename);
    fileIsLoaded = true;
}

void pile_model::load(string path)
{

    images.clear();
    images_icons_filename.clear();
    if(!std::filesystem::exists(std::filesystem::path(path))){
        path += "f";
    }
    images.load_tiff(path.c_str());

    //Enregistrement dans un fichier temporaire
    for (unsigned int i=0; i<images.size(); i++)
    {
        CImg<float> img = images[i];

        std::string chemin = "tmp";
        chemin += separator;
        chemin += "pileDisplay";
        chemin += separator;
        chemin += std::to_string(i) + ".bpm";

        img.save_bmp(chemin.c_str());         // problem here
        images_icons_filename.push_back(chemin);
    }

    currentImage = images[0];
}

bool pile_model::is24Bits()
{
    if (currentImage.spectrum() == 3)
        return true;
    else
        return false;
}
