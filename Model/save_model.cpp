#include <QPoint>
#include <json/json.h>

#include "save_model.h"

#include "calque.h"
#include "resultat.h"

#include <filesystem>


std::string save_model::getFileName(std::string filePath, bool withExtension, char seperator){
    // Get last dot position
    std::size_t dotPos = filePath.rfind('.');
    std::size_t sepPos = filePath.rfind(seperator);

    if(sepPos != std::string::npos)
    {
        return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos) );
    }
    return "";
}

//Constructor
save_model::save_model()
{}


void save_model::changeSavePaths(std::string newSavePath)
{
    savePath = newSavePath;
    saveCalquesPath = newSavePath + separator + "Calques";
}


void save_model::saveTiff(std::string pathSource){
    std::string name = savePath + separator + filename + ".tiff";
    if(!std::filesystem::exists(name.c_str())){
        std::filesystem::copy(pathSource, name.c_str());
    }
}

void save_model::saveCalques(std::vector<calque> calques){
    for(auto i : calques){
        if(i.getIntervalMin() >= -1){
            std::string calque_name = saveCalquesPath;
            calque_name += separator;
            calque_name += std::string("calque");
            calque_name += std::string(std::to_string(i.getId()));
            i.saveCalque(calque_name);
        }
    }
}

void save_model::saveJsonFile(std::vector<calque> calques, const std::vector<Resultat> &resultats){
    std::string _filename = savePath;
    _filename += separator;
    _filename += std::string(filename);
    _filename += std::string(".scb");

    Json::Value value;

    Json::Value calquesValue;

    for(calque i : calques){
        if(i.getIntervalMin() >= -1){
            Json::Value calqueValue;
            calqueValue["min"] = i.getIntervalMin();
            calqueValue["max"] = i.getIntervalMax();
            calqueValue["id"] = i.getId();
            std::string pathcalque = saveCalquesPath + separator + "calque" + std::to_string(i.getId());
            calqueValue["path"] = pathcalque.c_str();

            std::string nom = "calque" + std::to_string(i.getId());
            calquesValue[nom.c_str()] = calqueValue;
        }
    }

    value["calques"] = calquesValue;


    for(Resultat i : resultats){
        Json::Value resultValue;
        resultValue["pertinence"] = i.getPertinence();

        //Array
        Json::Value arrayV;
        for (int element: i.getResults()) {
            arrayV.append(element);
        }
        resultValue["resultats"] = arrayV;


        value["results"].append(resultValue);
    }



    std::ofstream outfile(_filename);
    //    outfile.open(_filename, std::ofstream::out | std::ofstream::trunc);
    outfile << value;

    outfile.close();
}

void save_model::save_as(std::string path, std::string fileName, std::vector<calque> _calques,std::vector<Resultat> resultats){
    std::cout << "function save_as " << std::endl;

    auto first = fileName.find(".");
    std::string f = fileName.substr(0, first);
    filename = getFileName(f,true,separator);


    savePath = path;

    saveCalquesPath = savePath;
    saveCalquesPath += separator;
    saveCalquesPath += std::string("Calques");

    if(std::filesystem::exists(saveCalquesPath.c_str())){
        std::cout << saveCalquesPath << " Found" << std::endl;

        std::filesystem::remove_all(std::filesystem::path(saveCalquesPath));


        std::cout << saveCalquesPath << " Removed" << std::endl;
    }


    std::filesystem::create_directory(saveCalquesPath.c_str());
//    fs::remove_all(fs::path(saveCalquesPath));

    saveTiff(fileName);

    save(_calques,resultats);
}


bool save_model::save(std::vector<calque> _calques, const std::vector<Resultat> &resultats){
    if(savePath.empty()){
        return false;
    }else{
        if(!std::filesystem::exists(savePath.c_str())){
            return false;
        }else{
            saveCalques(_calques);
            saveJsonFile(_calques,resultats);
            return true;
        }
    }
}
