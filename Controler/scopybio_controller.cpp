#include "scopybio_controller.h"
#include <fstream>
#include <json/json.h>

using namespace std;

ScopyBio_Controller::ScopyBio_Controller()
{
    std:: cout << "gab il a une maitr yi op" << std::endl;

    Json::Value Config;

    ifstream gloubiboulqua("../test.json", ifstream::binary);

    if (gloubiboulqua.is_open()){
        cout << "gloubiboulqua est bien ouvert" << endl;
    }

    gloubiboulqua >> Config;

    cout << Config ;
}

