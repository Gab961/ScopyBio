#include <QPoint>
#include "gestionnaire_calques_model.h"
#include <algorithm>
#include <iostream>

gestionnaire_calque_model::gestionnaire_calque_model():id(0){}

void gestionnaire_calque_model::saveTmpforDisplay(int min, int max){
    calque search = getCalque(min,max);

    CImg<float> calquetmp = search.getCalque();

    std::string path = "./tmp/calque" + std::to_string(search.getName()) + ".png";

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

calque &gestionnaire_calque_model::getCalque(int min, int max){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    return *(res);
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

    calque search = getCalque(min,max);

    cimg_forXY(search.getCalque(), x, y) { search.getCalque()(x,y,0)=255;  search.getCalque()(x,y,1)=255;  search.getCalque()(x,y,2)=255; }
    search.getCalque().save_png("./tmp/coucou.png",0);
    //search.dessinerRectangle(pos1,pos2,labelWidth,labelHeight);
}
