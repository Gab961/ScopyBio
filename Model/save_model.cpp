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


void save_model::saveTiff(){
    std::string name = savePath + separator + filename + ".tiff";
    if(!std::filesystem::exists(name.c_str())){
        std::filesystem::copy(localTiffSave, name.c_str());
    }
}

void save_model::saveCalques(std::vector<calque> calques, bool dataReady, calque res){
    for(auto i : calques){
        if(i.getIntervalMin() >= -1){
            std::string calque_name = saveCalquesPath;
            calque_name += separator;
            calque_name += std::string("calque");
            calque_name += std::string(std::to_string(i.getId()));
            i.saveCalque(calque_name);
        }
    }

    if(dataReady){
        std::string calque_name = saveCalquesPath;
        calque_name += separator;
        calque_name += std::string("result");
        res.saveCalque(calque_name);
    }
}

void save_model::saveJsonFile(std::vector<calque> calques, const std::vector<Resultat> &resultats, int row, int col, int whiteValue){
    std::string _filename = savePath;
    _filename += separator;
    _filename += std::string(filename);
    _filename += std::string(".scb");

    Json::Value value;


    if(calques.size() != 0){
        Json::Value calquesValue;
        for(calque i : calques){
            if(i.getIntervalMin() >= -1){
                Json::Value calqueValue;
                calqueValue["min"] = i.getIntervalMin();
                calqueValue["max"] = i.getIntervalMax();
                calqueValue["id"] = i.getId();
                std::string pathcalque = saveCalquesPath + separator + "calque" + std::to_string(i.getId()) + ".cimg";
                calqueValue["path"] = pathcalque.c_str();

                std::string nom = "calque" + std::to_string(i.getId());
                calquesValue[nom.c_str()] = calqueValue;
            }
        }

        value["calques"] = calquesValue;
    }

    if(resultats.size() != 0 ){
        for(Resultat i : resultats){
            //Pertinence
            Json::Value resultValue;
            resultValue["pertinence"] = i.getPertinence();

            //Top left Point
            Json::Value arrayTopPoint;
            arrayTopPoint.append(i.getTopLeftPoint().x());
            arrayTopPoint.append(i.getTopLeftPoint().y());
            resultValue["topLeftPoint"] = arrayTopPoint;

            //Bottom right Point
            Json::Value arrayBotPoint;
            arrayBotPoint.append(i.getBottomRightPoint().x());
            arrayBotPoint.append(i.getBottomRightPoint().y());
            resultValue["bottomRightPoint"] = arrayBotPoint;

            //Array
            Json::Value arrayV;
            //int index = 0;
            for (auto element: i.getResults()) {
                arrayV.append(element);
            }
            resultValue["resultats"] = arrayV;


            value["results"]["data"].append(resultValue);
        }

        value["results"]["rowAmount"] = row;
        value["results"]["colAmount"] = col;
        std::string calque_name = saveCalquesPath;
        calque_name += separator;
        calque_name += std::string("result.cimg");
        value["results"]["calque"] = calque_name.c_str();
        value["results"]["white"] = whiteValue;
    }

    std::ofstream outfile(_filename);
    //    outfile.open(_filename, std::ofstream::out | std::ofstream::trunc);
    outfile << value;

    outfile.close();
}

void save_model::saveInLocal(std::string sourcePath)
{
    localTiffSave = "tmp";
    localTiffSave += separator;
    localTiffSave += getFileName(sourcePath,true,separator);
    if (!std::filesystem::exists(localTiffSave.c_str()))
        std::filesystem::copy(sourcePath, localTiffSave.c_str());
}

void save_model::saveCurrentDisplay(std::string savePath, std::string currentDisplayPath)
{
    CImg<float> img;
    img.load_bmp(currentDisplayPath.c_str());
    img.save_bmp(savePath.c_str());
}

void save_model::save_as(std::string path, std::string fileName, std::vector<calque> _calques, bool dataReady, std::vector<Resultat> resultats, int row, int col, calque res,int whiteValue){
    auto first = fileName.find(".");
    std::string f = fileName.substr(0, first);
    filename = getFileName(f,true,separator);

    savePath = path;

    saveCalquesPath = savePath;
    saveCalquesPath += separator;
    saveCalquesPath += std::string("Calques");

    if(!std::filesystem::is_empty(std::filesystem::path(savePath))){

        if(std::filesystem::exists(saveCalquesPath.c_str())){
            std::filesystem::remove_all(std::filesystem::path(saveCalquesPath));

            std::filesystem::remove_all(std::filesystem::path(savePath));
        }else{
            savePath = path + separator + filename;

            saveCalquesPath = savePath;
            saveCalquesPath += separator;
            saveCalquesPath += std::string("Calques");
        }
    }



    std::filesystem::create_directories(saveCalquesPath.c_str());

    saveTiff();

    save(_calques,dataReady,resultats,row,col,res,whiteValue);
}


bool save_model::save(std::vector<calque> _calques, bool dataReady, const std::vector<Resultat> &resultats, int row, int col, calque res,int whiteValue){
    if(savePath.empty()){
        return false;
    }else{
        if(!std::filesystem::exists(savePath.c_str())){
            return false;
        }else{
            saveCalques(_calques,dataReady,res);
            saveJsonFile(_calques,resultats,row,col,whiteValue);
            return true;
        }
    }
}
