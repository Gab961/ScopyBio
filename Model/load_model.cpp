#include <QPoint>
#include "load_model.h"
#include "calque.h"
#include "resultat.h"

#define cimg_use_png
#include "CImg.h"

using namespace cimg_library;

load_model::load_model(){}

void load_model::loadJsonValue(std::string path){
    std::ifstream sauvegarde_file(path, std::ifstream::binary);
    sauvegarde_file >> sauvegarde;
    sauvegarde_file.close();
}

std::vector<calque> load_model::loadCalques(){
    std::vector<calque> vecteur;

    Json::Value calques_json;

    if(sauvegarde["calques"] != Json::Value::null){
        calques_json = sauvegarde["calques"];
    }else{
        return vecteur;
    }

    if(calques_json != Json::Value::null){
        for(Json::Value json : calques_json){
            CImg<float> caltmp;
            std::string nom = json["path"].asCString();
            caltmp.load_cimg(nom.c_str());

            calque tmp(caltmp.width(),caltmp.height(),json["min"].asInt(),json["max"].asInt(),json["id"].asInt());
            tmp.setCalque(caltmp);
            tmp.clearMemento();
            tmp.addMemento();

            vecteur.push_back(tmp);
        }
    }else{
        return vecteur;
    }

    return vecteur;
}


std::vector<Resultat> load_model::loadResults(){
    std::vector<Resultat> vecteur;

    Json::Value result_json;

    if(sauvegarde["results"] != Json::Value::null){
        result_json = sauvegarde["results"]["data"];
    }else{
        return vecteur;
    }

    if(result_json != Json::Value::null){
        for(Json::Value json : result_json){
            Resultat tmp;
            tmp.setPertinence(json["pertinence"].asInt());
            std::vector<float> tmpvec;
            for(auto elt : json["resultats"]){
                tmpvec.push_back(elt.asFloat());
            }
            tmp.setResults(tmpvec);

            int topX = json["topLeftPoint"][0].asInt();
            int topY = json["topLeftPoint"][1].asInt();

            int botX = json["bottomRightPoint"][0].asInt();
            int botY = json["bottomRightPoint"][1].asInt();

            QPoint top(topX,topY);
            QPoint bot(botX,botY);

            tmp.setTopLeftPoint(top);
            tmp.setBottomRightPoint(bot);

            vecteur.push_back(tmp);
        }
    }else{
        return vecteur;
    }

    return vecteur;
}


std::vector<int> load_model::loadColRowAmounts(){
    std::vector<int> vecteur;

    Json::Value result_json;

    if(sauvegarde["results"] != Json::Value::null){
        result_json = sauvegarde["results"];
    }else{
        return vecteur;
    }

    if(result_json != Json::Value::null){
        int row = result_json["rowAmount"].asInt();
        int col = result_json["colAmount"].asInt();

        vecteur.push_back(row);
        vecteur.push_back(col);
    }else{
        return vecteur;
    }

    return vecteur;
}

std::string load_model::loadResultCalque(){
    std::string res = "";

    Json::Value result_json;

    if(sauvegarde["results"] != Json::Value::null){
        result_json = sauvegarde["results"];
    }else{
        return res;
    }

    if(result_json["calque"] != Json::Value::null){
        res = result_json["calque"].asCString();
    }

    return res;
}

int load_model::loadWhiteValue(){
    Json::Value result_json;

    if(sauvegarde["results"] != Json::Value::null){
        result_json = sauvegarde["results"];
    }else{
        return -1;
    }

    if(result_json["white"] != Json::Value::null){
        return result_json["white"].asInt();
    }

    return -1;
}
