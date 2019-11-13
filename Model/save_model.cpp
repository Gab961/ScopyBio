#include <experimental/filesystem>
#include <iostream>
#include <regex>
#include <json/json.h>

#include "save_model.h"

#include "calque.h"

inline char save_model::separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

save_model::save_model(std::string path, std::__cxx11::string filename, std::vector<calque> _calques)
{
    for(auto i : _calques){
        calques.push_back(i);
    }

    if(!std::experimental::filesystem::is_empty(path)){
        int i = 0;
        for (const auto & entry : std::experimental::filesystem::directory_iterator(path)){
            std::cout << entry.path() << std::endl;
            std::string tmp = entry.path();
            if (tmp.find(filename) != std::string::npos) {
                i++;
            }
        }

        if(i == 0){
            savePath = path + separator() + filename;
            std::experimental::filesystem::create_directories(savePath);
        }else{
            savePath = path + separator() + filename + std::to_string(i);
            std::experimental::filesystem::create_directories(savePath);
        }
    }else{
        savePath = path;
    }


    saveCalquesPath = savePath + separator() + "Calques";
    std::experimental::filesystem::create_directories(saveCalquesPath);

    save();
}

void save_model::saveCalques(){
    for(auto i : calques){
        if(i.getIntervalMin() >= -1){
            std::string calque_name = saveCalquesPath + separator() + "calques" + std::to_string(i.getId());
            i.getCalque().save_png(calque_name.c_str());
        }
    }
}

void save_model::saveJsonFile(){
    std::string filename= filename+".scb";
    Json::Value value;

    for(auto i : calques){
        if(i.getIntervalMin() >= -1){
            Json::Value calqueValue;
            calqueValue["min"] = i.getIntervalMin();
            calqueValue["max"] = i.getIntervalMax();
            calqueValue["id"] = i.getId();
            std::string pathcalque = saveCalquesPath + separator() + "calque" + std::to_string(i.getId());
            calqueValue["path"] = pathcalque;
        }
    }

}


void save_model::save(){
    saveCalques();
    saveJsonFile();
}
