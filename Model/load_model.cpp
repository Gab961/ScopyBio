#include <QPoint>
#include "load_model.h"
#include "calque.h"
#include "resultat.h"

#define cimg_use_png
#include "CImg.h"

using namespace cimg_library;

load_model::load_model(){}

std::vector<calque> load_model::loadCalques(std::string path){
    std::vector<calque> vecteur;

    Json::Value sauvegarde;

    std::ifstream sauvegarde_file(path, std::ifstream::binary);
    sauvegarde_file >> sauvegarde;


    Json::Value calques_json;

    if(sauvegarde["calques"] != Json::Value::null){
        calques_json = sauvegarde["calques"];
    }

    if(calques_json != Json::Value::null){
        for(Json::Value json : calques_json){
            CImg<float> caltmp;
            std::string nom = json["path"].asCString();
            caltmp.load_cimg(nom.c_str());

            calque tmp(caltmp.width(),caltmp.height(),json["min"].asInt(),json["max"].asInt(),json["id"].asInt());
            tmp.setCalque(caltmp);

            vecteur.push_back(tmp);
        }
    }

    return vecteur;
}

//TODO Finir le vecteur et Qpoint
std::vector<Resultat> load_model::loadResults(std::string path){
    std::vector<Resultat> vecteur;

    Json::Value sauvegarde;

    std::ifstream sauvegarde_file(path, std::ifstream::binary);
    sauvegarde_file >> sauvegarde;


    Json::Value result_json;

    if(sauvegarde["results"] != Json::Value::null){
        result_json = sauvegarde["results"];
    }
/*
    if(calques_json != Json::Value::null){
        for(Json::Value json : calques_json){
            Resultat tmp;
            tmp.setPertinence(json["pertinence"].asInt());
        }
    }
*/
    return vecteur;
}
