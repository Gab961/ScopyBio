#include <QPoint>
#include "gestionnaire_calques_model.h"
#include <algorithm>

gestionnaire_calque_model::gestionnaire_calque_model():id(0){}

void gestionnaire_calque_model::save(std::string pathToSave){

}

bool gestionnaire_calque_model::existeCalque(int min, int max){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    if(res != listOfCalque.end()){
        return true;
    }else{
        return false;
    }
}

calque &gestionnaire_calque_model::getCalque(int min, int max){
    auto res = std::find(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    return listOfCalque.at(res);
}


void gestionnaire_calque_model::creerCalque(int min, int max, int taille){
    calque _calque(min,max,id);
    id++;

    listOfCalque.push_back(_calque);

    int minimum = min, maximum = max;
    if(min < 0){
        minimum = 0;
    }

    if(max < 0){
        maximum = taille;
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
}

void gestionnaire_calque_model::dessineFaisceau(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){

    auto search = existeCalque();

    if (search != dictionnaireImgMap.end()) {
        CImg<float> tmp(labelWidth,labelWidth);

    }
}
