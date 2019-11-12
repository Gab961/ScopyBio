#include <QPoint>
#include <algorithm>
#include <iostream>

#include "gestionnaire_calques_model.h"

/**
 * @brief gestionnaire_calque_model::gestionnaire_calque_model construit un modèle et dès le départ crée un calque vert qui pourra être utilisé.
 */
gestionnaire_calque_model::gestionnaire_calque_model():id(0),isGreen(false){
    calque _calque(-3,-3,id);
    id++;
    _calque.filtreVert();

    listOfCalque.push_back(_calque);

}

/**
 * @brief gestionnaire_calque_model::saveTmpforDisplay Sauvegarde
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 */
void gestionnaire_calque_model::saveTmpforDisplay(int min, int max){
    int search = getCalque(min,max);

    CImg<float> calquetmp = listOfCalque[search].getCalque();

    std::string path = "./tmp/calque" + std::to_string(listOfCalque[search].getId()) + ".png";

    calquetmp.save_png(path.c_str(),0);
}

/**
 * @brief gestionnaire_calque_model::existeCalque renvoie si le calque existe.
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @return true s'il existe, false sinon
 */
bool gestionnaire_calque_model::existeCalque(int min, int max){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    if(res != listOfCalque.end()){
        return true;
    }else{
        return false;
    }
}

/**
 * @brief gestionnaire_calque_model::getCalque renvoie l'id du calque qu'on souhaite modifier
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @return l'id du calque que l'on cherche, -1 si non trouvé
 */
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

/**
 * @brief gestionnaire_calque_model::getCalqueForDisplay renvoie la copie du calque pour l'afficher
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @return la copie du calque que l'on cherche
 */
calque gestionnaire_calque_model::getCalqueForDisplay(int min, int max){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    return *res;
}

calque gestionnaire_calque_model::getCalqueForDisplay(int id){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&id](calque &a)->bool { return a.getId() == id ; } );
    return *res;
}

/**
 * @brief gestionnaire_calque_model::creerCalque creer un calque et met à jour le dictionnaire puisqu'on sait quelle image va l'utiliser. Si l'image n'existe pas dans le dictionnaire, cette fonction la crée
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @param taille taille de la pile d'image
 */
void gestionnaire_calque_model::creerCalque(int min, int max, int taille){
    calque _calque(min,max,id);

    listOfCalque.push_back(_calque);

    addInDict(min,max,taille,id);

    id++;
}

/**
 * @brief gestionnaire_calque_model::dessineFaisceau dessine un faisceau. Cette fonction est spéciale puisqu'il doit tout effacer à chaque fois qu'un nouveau faisceau est créé
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @param pos1
 * @param pos2
 * @param labelWidth
 * @param labelHeight
 */
void gestionnaire_calque_model::dessineFaisceau(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){

    int search = getCalque(min,max);
    if(search != -1){
        listOfCalque[search].dessinerFaisceau(pos1,pos2,labelWidth,labelHeight);
    }
}

/**
 * @brief gestionnaire_calque_model::updateCalqueVert met juste à jour le dictionnaire, l'ajoute dans le dico s'il est actif, le supprime sinon.
 * @param min
 * @param max
 * @param taille
 */
void gestionnaire_calque_model::updateCalqueVert(int min, int max, int taille){
    isGreen = !isGreen;

    int search = getCalque(min,max);

    int id = listOfCalque[search].getId();

    if(isGreen){// Afficher le filtre
        addInDict(min,max,taille,id);


    }else{// Ne pas afficher le filtre

        removeFromDict(min,max,id);
    }
}

void gestionnaire_calque_model::mergeCalques(std::vector<int> ids, CImg<float> currentDisplayedImage, std::string pathOfMainDisplay){
    std::cout << "fonction mergeCalques" << std::endl;
    if(ids.size() == 0){
        std::cout << "0 image à merge" << std::endl;
        calque _calqueResultat(-4,-4,-1);// pour afficher le résultat on crée un calque vide transparent
        currentDisplayedImage.draw_image(0,0,0,0,_calqueResultat.getCalque(),_calqueResultat.getCalque().get_channel(3),1,255);
        currentDisplayedImage.save_png(pathOfMainDisplay.c_str());
    }
    //S'il il y a qu'un seul calque à afficher, on affiche que lui
    if(ids.size() == 1){
        std::cout << "1 image à merge" << std::endl;
        calque tmp = getCalqueForDisplay(ids[0]);

        currentDisplayedImage.draw_image(0,0,0,0,tmp.getCalque(),tmp.getCalque().get_channel(3),1,255);
        currentDisplayedImage.save_png(pathOfMainDisplay.c_str());
    }else{//Sinon on merge et on affiche


        for(auto i : ids){
            std::cout << i << " | ";
        }
        calque _calqueResultat(-4,-4,-1);// pour afficher le résultat on crée un calque vide transparent
        for(auto i : ids){

            std::cout << "plusieurs images à merge" << std::endl;
            calque overlay = getCalqueForDisplay(i);
            merge2Images(_calqueResultat,overlay);
        }

        currentDisplayedImage.draw_image(0,0,0,0,_calqueResultat.getCalque(),_calqueResultat.getCalque().get_channel(3),1,255);
        currentDisplayedImage.save_png(pathOfMainDisplay.c_str());
    }
}

calque gestionnaire_calque_model::merge2Images(calque a, calque b){
    calque tmp = getCalqueForDisplay(a.getId());
    tmp.getCalque().draw_image(0,0,b.getCalque());
    return tmp;
}


//              Fonction pour le dictionnaire.

void gestionnaire_calque_model::addInDict(int min, int max, int taille, int id){
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
}


void gestionnaire_calque_model::removeFromDict(int min, int max, int id){

    int minimum = min, maximum = max;
    if(min < 0){
        minimum = 0;
    }

    if(max < 0){
        maximum = dictionnaireImgMap.size();
    }else{
        maximum = max+1;
    }

    for(int i = minimum; i < maximum; i++){

        //Recherche dans le dictionnaire
        auto search = dictionnaireImgMap.find(i);
        //Si il trouve il ajoute le calque
        if (search != dictionnaireImgMap.end()) {
            search->second.erase(std::remove(search->second.begin(), search->second.end(), id), search->second.end());
        }

    }
}

std::vector<int> gestionnaire_calque_model::getListOfCalqueFromImage(int idImage){
    if(dictionnaireImgMap.empty()){
        std::vector<int> tmp;
        return tmp;
    }

    auto res = dictionnaireImgMap.find(idImage);
    return res->second;

}
