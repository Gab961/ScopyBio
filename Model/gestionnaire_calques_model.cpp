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

/**
 * @brief gestionnaire_calque_model::creerCalque creer un calque et met à jour le dictionnaire puisqu'on sait quelle image va l'utiliser. Si l'image n'existe pas dans le dictionnaire, cette fonction la crée
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @param taille taille de la pile d'image
 */
void gestionnaire_calque_model::creerCalque(int min, int max, int taille){
    calque _calque(min,max,id);

    listOfCalque.push_back(_calque);

    //On pourra appeler plus tard une fonction qui ajoute dans le dictionnaire

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
    //On pourra appeler plus tard une fonction qui ajoute dans le dictionnaire
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
        //On pourra plus tard appeler une fonction qui fait la suppression.
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

/*
 * Fonction pour supprimer un calque d'un dico l'idée serait :
 * supprimerCalque(int min, int max){
 *
 * rechercher le calque correspondant
 *
 * récupérer son id
 *
 * int searchId = getCalque(min,max);
        int id = listOfCalque[searchGreen].getId();

        for(int i = minimum; i < maximum; i++){

            //Recherche dans le dictionnaire
            auto search = dictionnaireImgMap.find(i);
            //Si il trouve il ajoute le calque
            if (search != dictionnaireImgMap.end()) {
                search->second.erase(std::remove(search->second.begin(), search->second.end(), id), search->second.end());
            }

        }
 *
 * }
 * */

/* Fonction pour ajouter dans le dictionnaire.
 *
 * int minimum = min, maximum = max;
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
 *
 *
 * /
