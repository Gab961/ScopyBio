#include <QPoint>
#include <algorithm>
#include <iostream>

#include "gestionnaire_calques_model.h"

gestionnaire_calque_model::gestionnaire_calque_model():id(0),isGreen(false){
    calque _calque(-3,-3,id);
    id++;
    _calque.filtreVert();

    listOfCalque.push_back(_calque);

}

void gestionnaire_calque_model::saveTmpforDisplay(int min, int max){
    int search = getCalque(min,max);

    CImg<float> calquetmp = listOfCalque[search].getCalque();

    std::string path = "./tmp/calque" + std::to_string(listOfCalque[search].getId()) + ".png";

    calquetmp.save_png(path.c_str(),0);
}

bool gestionnaire_calque_model::existeCalque(int min, int max){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    if(res != listOfCalque.end()){
        return true;
    }else{
        return false;
    }
}

int gestionnaire_calque_model::getCalque(int min, int max){
    int index(0);

    for(auto i : listOfCalque){
        if(i.getIntervalMin() == min && i.getIntervalMax()==max){
            return index;
        }
        else{
            index++;
        }
    }

    std::cout << "Calque not Found" << std::endl;
    return -1;
}

calque gestionnaire_calque_model::getCalqueForDisplay(int min, int max){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    return *res;
}

void gestionnaire_calque_model::creerCalque(int min, int max, int taille){
    calque _calque(min,max,id);

    listOfCalque.push_back(_calque);

    int minimum = min, maximum = max;
    if(min < 0){
        minimum = 0;
    }

    if(max < 0){
        maximum = taille;
    }else{
        maximum = max+1;
    }

    for(int i = minimum; i < maximum; i++){

        //Recherche dans le dictionnaire
        auto search = dictionnaireImgMap.find(i);
        //Si il trouve il ajoute le calque
        if (search != dictionnaireImgMap.end()) {
            search->second.push_back(id);

        }else{//Sinon on crée
            std::map<int,std::vector<int>>::iterator it = dictionnaireImgMap.begin();
            std::vector<int> vec;
            vec.push_back(id);
            dictionnaireImgMap.insert (it, std::pair<int,std::vector<int>>(i,vec));
        }

    }

    id++;
}

void gestionnaire_calque_model::dessineFaisceau(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){

    int search = getCalque(min,max);
    if(search != -1){
        listOfCalque[search].dessinerFaisceau(pos1,pos2,labelWidth,labelHeight);
    }
}

void gestionnaire_calque_model::updateCalqueVert(int min, int max, int taille){
    isGreen = !isGreen;

    int minimum = min, maximum = max;
    if(min < 0){
        minimum = 0;
    }

    if(max < 0){
        maximum = taille;
    }else{
        maximum = max+1;
    }

    if(isGreen){// Afficher le filtre
        for(int i = minimum; i < maximum; i++){

            //Recherche dans le dictionnaire
            auto search = dictionnaireImgMap.find(i);
            //Si il trouve il ajoute le calque
            if (search != dictionnaireImgMap.end()) {
                search->second.push_back(id);

            }else{//Sinon on crée
                std::map<int,std::vector<int>>::iterator it = dictionnaireImgMap.begin();
                std::vector<int> vec;
                vec.push_back(id);
                dictionnaireImgMap.insert (it, std::pair<int,std::vector<int>>(i,vec));
            }

        }


    }else{// Ne pas afficher le filtre

        int searchGreen = getCalque(min,max);
        int id = listOfCalque[searchGreen].getId();

        for(int i = minimum; i < maximum; i++){

            //Recherche dans le dictionnaire
            auto search = dictionnaireImgMap.find(i);
            //Si il trouve il ajoute le calque
            if (search != dictionnaireImgMap.end()) {
                search->second.erase(std::remove(search->second.begin(), search->second.end(), id), search->second.end());
            }

        }
    }
}
