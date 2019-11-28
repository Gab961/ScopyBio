#include <json/json.h>

#include "save_model.h"

#include "calque.h"


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
save_model::save_model():canSave(false){}



void save_model::saveCalques(){
    for(auto i : calques){
        if(i.getIntervalMin() >= -1){
            std::string calque_name = saveCalquesPath + separator + "calques" + std::to_string(i.getId());
            i.getCalque().save_png(calque_name.c_str());
        }
    }
}

void save_model::saveJsonFile(){
    std::string _filename= savePath + separator + filename+".scb";
    Json::Value value;

    for(auto i : calques){
        if(i.getIntervalMin() >= -1){
            Json::Value calqueValue;
            calqueValue["min"] = i.getIntervalMin();
            calqueValue["max"] = i.getIntervalMax();
            calqueValue["id"] = i.getId();
            std::string pathcalque = saveCalquesPath + separator + "calque" + std::to_string(i.getId());
            calqueValue["path"] = pathcalque.c_str();

            std::string nom = "calque" + std::to_string(i.getId());
            value[nom.c_str()] = calqueValue;
        }
    }


    std::ofstream outfile(_filename);
//    outfile.open(_filename, std::ofstream::out | std::ofstream::trunc);
    outfile << value;

    outfile.close();
}

void save_model::save_as(std::string path, std::string fileName, std::vector<calque> _calques){

    canSave = true;


    auto first = fileName.find(".");
    std::string f = fileName.substr(0, first);
    filename = getFileName(f,true,separator);


    std::string pathCalque = path +separator+"Calques";
    savePath = path;


    saveCalquesPath = savePath + separator + "Calques";
    if(boost::filesystem::exists(saveCalquesPath.c_str())){
        boost::filesystem::remove_all(saveCalquesPath.c_str());
    }

    boost::filesystem::create_directories(saveCalquesPath.c_str());

    save(_calques);
}

void saveTiff(){

}

bool save_model::getCanSave() const
{
    return canSave;
}

void save_model::save(std::vector<calque> _calques){
    std::cout << "save" << std::endl;
    calques.clear();
    for(auto i : _calques){
        calques.push_back(i);
    }
    saveCalques();
    saveJsonFile();
}
