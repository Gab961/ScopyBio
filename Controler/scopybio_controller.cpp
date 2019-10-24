#include "scopybio_controller.h"

#define PATH "../../Config/config.json"

ScopyBio_Controller::ScopyBio_Controller()
{
    Json::Value config;

    std::ifstream config_file(PATH, std::ifstream::binary);
    config_file >> config;

    std::cout<<config; //This will print the entire json object.

    //The following lines will let you access the indexed objects.
//    cout<<people["Anna"]; //Prints the value for "Anna"
//    cout<<people["ben"]; //Prints the value for "Ben"
//    cout<<people["Anna"]["profession"]; //Prints the value corresponding to "profession" in the json for "Anna"

//    cout<<people["profession"];
}



//=====================

//       SETTERS

//=====================

void ScopyBio_Controller::setPercentOfBlack(float black){
    percentageOfBlack = black;
}
