#include <json/json.h>

#include "save_model.h"

#include "calque.h"

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


void save_model::changeSavePath(std::string newSavePath)
{
    savePath = newSavePath;
}


void save_model::saveTiff(std::string pathSource){
    std::string name = savePath + separator + filename + ".tiff";
    std::filesystem::copy(pathSource, name.c_str());
}

void save_model::saveCalques(){
    for(auto i : calques){
        if(i.getIntervalMin() >= -1){
            std::string calque_name = saveCalquesPath;
            calque_name += separator;
            calque_name += std::string("calque");
            calque_name += std::string(std::to_string(i.getId()));
            i.getCalque().save_png(calque_name.c_str());
        }
    }
}

void save_model::saveJsonFile(){
    std::string _filename = savePath;
    _filename += separator;
    _filename += std::string(filename);
    _filename += std::string(".scb");

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

    save(_calques);
}


bool save_model::save(std::vector<calque> _calques){
    if(savePath.empty()){
        return false;
    }else{
        if(!std::filesystem::exists(savePath.c_str())){
            return false;
        }else{
            calques.clear();
            for(auto i : _calques){
                calques.push_back(i);
            }
            saveCalques();
            saveJsonFile();
            return true;
        }
    }
}
