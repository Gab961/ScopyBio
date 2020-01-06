#include <QPoint>
#include <algorithm>
#include <iostream>

#include "gestionnaire_calques_model.h"

/**
 * @brief gestionnaire_calque_model::gestionnaire_calque_model construit un modèle et dès le départ crée un calque vert qui pourra être utilisé.
 */
gestionnaire_calque_model::gestionnaire_calque_model(): id(0),isGreen(false),isHistogram(false),idCurrentCalque(-1){
}

void gestionnaire_calque_model::init(int newPileWidth, int newPileHeight){
    pileWidth = newPileWidth;
    pileHeight = newPileHeight;
    listOfCalque.clear();
    dictionnaireImgMap.clear();
    initGlobalCalques(pileWidth,pileHeight);
}

/**
 * @brief gestionnaire_calque_model::initGlobalCalques Initialise les calques histogramme et vert
 * @param _pileWidth
 * @param _pileHeight
 */
void gestionnaire_calque_model::initGlobalCalques(int pileWidth, int pileHeight)
{
    //    std::cout << "cc :" << std::endl;
    //    afficheCalques();
    id = 0;
    calque _calqueHisto(pileWidth, pileHeight, -4,-4,id);
    id++;
    listOfCalque.push_back(_calqueHisto);

    calque _calqueVert(pileWidth, pileHeight, -3,-3,id);
    id++;
    _calqueVert.filtreVert();
    listOfCalque.push_back(_calqueVert);

    calque _calquePertinence(pileWidth, pileHeight, -5,-5,id);
    addInDict(-5,-5,30,id);
    idPertinenceCalque = id;
    listOfCalque.push_back(_calquePertinence);
    id++;

    //Calque de pertinence dans le cas d'une analyse utilisateur
    calque _calquePertinenceUser(pileWidth, pileHeight, -99,-99,id);
    idUserPertinenceCalque = id;
    listOfCalque.push_back(_calquePertinenceUser);
    id++;
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

bool gestionnaire_calque_model::existeCalque(int id){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&id](calque &a)->bool { return a.getId() == id; } );
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
    return -1;
}

int gestionnaire_calque_model::getCalqueIndex(int id){
    int index(0);

    for(calque i : listOfCalque){
        if(i.getId() == id){
            return index;
        }
        else{
            index++;
        }
    }
    return -1;
}



void gestionnaire_calque_model::addCalques(std::vector<calque> calques, int taille){
    if(!calques.empty()){
        for(calque tmp : calques){
            listOfCalque.push_back(tmp);
            addInDict(tmp.getIntervalMin(),tmp.getIntervalMax(),taille,tmp.getId());
        }

        id = calques.back().getId()+1;
    }
}

void gestionnaire_calque_model::removeCalques(int min, int max){
    int search = getCalque(min,max);
    if(search != -1){
         listOfCalque.erase(listOfCalque.begin()+search);
    }
}

void gestionnaire_calque_model::calqueShowable(int min, int max, bool show){
    int search = getCalque(min,max);
    if(search != -1){
        listOfCalque[search].setCanShow(show);
    }
}

/**
 * @brief gestionnaire_calque_model::getCalqueForDisplay renvoie la copie du calque pour l'afficher
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @return la copie du calque que l'on cherche
 */
calque gestionnaire_calque_model::getCalqueForDisplay(int min, int max){
    std::cout << "On est ici avec min = " << min << " et max = " << max << std::endl;
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&min,&max](calque &a)->bool { return a.getIntervalMin() == min && a.getIntervalMax() == max; } );
    return *res;
}

calque gestionnaire_calque_model::getCalqueForDisplay(int id){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&id](calque &a)->bool { return a.getId() == id ; } );
    return *res;
}

calque gestionnaire_calque_model::getPertinenceCalque(){
    int id = -5;
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&id](calque &a)->bool { return a.getId() == id ; } );
    return *res;
}

std::vector<calque> gestionnaire_calque_model::getAllCalques() const
{
    return listOfCalque;
}


/**
 * @brief gestionnaire_calque_model::creerCalque creer un calque et met à jour le dictionnaire puisqu'on sait quelle image va l'utiliser. Si l'image n'existe pas dans le dictionnaire, cette fonction la crée
 * @param min connaitre à partir de quelle image s'applique le calque
 * @param max connaitre jusqu'à quelle image s'appliquer le calque
 * @param taille taille de la pile d'image
 */
void gestionnaire_calque_model::creerCalque(int width, int height, int min, int max, int taille){
    calque _calque(width, height, min,max,id);


    listOfCalque.push_back(_calque);

    if(min != -2){
        addInDict(min,max,taille,id);
    }

    id++;
}

/**
 * @brief gestionnaire_calque_model::reinitUserPertinenceCalque
 * @param width
 * @param height
 */
void gestionnaire_calque_model::reinitUserPertinenceCalque(int width, int height)
{
    calque newCalque = getCalqueForDisplay(-99,-99);

    CImg<float> newImage(width,height,1,4,0);
    newCalque.setCalque(newImage);

    newCalque.getCalque().save_bmp("/home/etudiant/reinit.bmp");

    listOfCalque[idUserPertinenceCalque] = newCalque;
}

/**
 * @brief gestionnaire_calque_model::reinitPertinenceCalque
 */
void gestionnaire_calque_model::reinitPertinenceCalque()
{
    calque newCalque = getCalqueForDisplay(-5,-5);

    CImg<float> newImage(pileWidth,pileHeight,1,4,0);
    newCalque.setCalque(newImage);

    listOfCalque[idPertinenceCalque] = newCalque;
}

/**
 * @brief gestionnaire_calque_model::reinitFaisceauCalque
 */
void gestionnaire_calque_model::reinitFaisceauCalque()
{
    calque newCalque = getCalqueForDisplay(-2,-2);

    CImg<float> newImage(pileWidth,pileHeight,1,4,0);
    newCalque.setCalque(newImage);

    int indexFaisceau = getCalque(-2,-2);

    listOfCalque[indexFaisceau] = newCalque;
}

/**
 * @brief gestionnaire_calque_model::manageNewAnalyse
 * @param results
 */
void gestionnaire_calque_model::manageNewAnalyse(int pertinence, QPoint pos1, QPoint pos2){
    calque newCalque = getCalqueForDisplay(-5, -5);

    newCalque.dessinerRectanglePertinence(pos1,pos2,pertinence);

    listOfCalque[idPertinenceCalque] = newCalque;
}

/**
 * @brief gestionnaire_calque_model::manageNewUserAnalyse
 * @param pertinence
 * @param pos1
 * @param pos2
 */
//TODO ICI
void gestionnaire_calque_model::manageNewUserAnalyse(int pertinence, QPoint pos1, QPoint pos2){
    calque newCalque = getCalqueForDisplay(-99, -99);

    newCalque.dessinerRectanglePertinence(pos1,pos2,pertinence);

    listOfCalque[idUserPertinenceCalque] = newCalque;
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
 * @brief gestionnaire_calque_model::dessinPoint
 * @param min
 * @param max
 * @param pos1
 * @param labelWidth
 * @param labelHeight
 */
void gestionnaire_calque_model::dessinLigne(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){

    int search = getCalque(min,max);
    if(search != -1){
        listOfCalque[search].dessinerLigne(pos1, pos2, labelWidth,labelHeight);
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
}

/**
 * @brief gestionnaire_calque_model::updateHistogram
 * @param min
 * @param max
 * @param taille
 */
void gestionnaire_calque_model::updateHistogram(int min, int max, int taille){
    isHistogram = !isHistogram;
}

/**
 * @brief gestionnaire_calque_model::updateQuadrillage
 * @param posInitiale
 * @param columns
 * @param lines
 */
void gestionnaire_calque_model::updateQuadrillage(int columns, int lines){
    calque newCalque = getCalqueForDisplay(-5, -5);

    newCalque.filtreQuadrillage(columns, lines);

    listOfCalque[idPertinenceCalque] = newCalque;
}

void gestionnaire_calque_model::updateUserQuadrillage(int columns, int lines){
    calque newCalque = getCalqueForDisplay(-99, -99);

    newCalque.filtreQuadrillage(columns, lines);

    listOfCalque[idUserPertinenceCalque] = newCalque;
}

void gestionnaire_calque_model::mergeUserAnalysis(CImg<float> zoom, std::string zoomPath)
{
    int idCalque = getCalque(-99,-99);
    calque overlay = getCalqueForDisplay(idCalque);
    zoom.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);
    zoom.save_bmp(zoomPath.c_str());
}

void gestionnaire_calque_model::mergeCalques(std::vector<int> ids, CImg<float> currentDisplayedImage, std::string pathOfMainDisplay){
    //Contraste en premier
    if (isHistogram)
    {
        calque overlay = getCalqueForDisplay(0);
        overlay.setCalque(currentDisplayedImage);
        overlay.filtreHistogram();
        //On enregistre au format bmp le calque qui a perdu ses
        //parties vert et bleu (le bmp implique obligatoirement RVB
        overlay.getCalque().save_bmp(pathOfHistogramSave.c_str());
        //Et on le récupère en tant qu'image courante sur laquelle on va
        //appliquer nos calques
        currentDisplayedImage.load_bmp(pathOfHistogramSave.c_str());
    }

    //Filtre vert en deuxieme
    if (isGreen)
    {
        calque overlay = getCalqueForDisplay(1);
        //std::cout << overlay.getId() << std::endl;
        currentDisplayedImage.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);
    }

    //    afficheCalques();
    //    std::cout << "*********************************************" << std::endl;

    if(ids.size() == 0){
        //std::cout << "0 image à merge" << std::endl;
        currentDisplayedImage.save_bmp(pathOfMainDisplay.c_str());
    }
    else
    {//Sinon on merge et on affiche

        //        std::cout << "plusieurs images à merge" << std::endl;

        //        for(auto i : ids){
        //            std::cout << i << " | ";
        //        }

        //        std::cout << "cc" << std::endl;

        //Et tous les autres ensuite
        for(auto i : ids){
            //std::cout << "I = " << i << std::endl;
            calque overlay = getCalqueForDisplay(i);
            if(overlay.getCanShow()){
                currentDisplayedImage.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);
            }
        }
    }

    //Selection en dernier

    auto search = getCalque(-2,-2);
    if(search != -1){
        calque overlay = listOfCalque[search];
        currentDisplayedImage.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);

    }


    //On sauvegarde l'ensemble
    currentDisplayedImage.save_bmp(pathOfMainDisplay.c_str());
}

//void gestionnaire_calque_model::merge2Images(calque &a, calque b){
//    a.getCalque().draw_image(0,0,0,0,b.getCalque(),b.getCalque().get_channel(3),1,255);
//}

//MEMENTO
void gestionnaire_calque_model::undo(){
    std::cout << "Undo sur le calque d'ID " << idCurrentCalque << std::endl;
    auto search = getCalqueIndex(idCurrentCalque);
    if(search != -1){
        listOfCalque[search].undo();
    }
}

void gestionnaire_calque_model::redo(){
    auto search = getCalqueIndex(idCurrentCalque);
    if(search != -1){
        listOfCalque[search].redo();
    }
}

void gestionnaire_calque_model::addMemento(){
    auto search = getCalqueIndex(idCurrentCalque);
    if(search != -1){
        listOfCalque[search].addMemento();
    }
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

void gestionnaire_calque_model::addInDict(calque cal,int taille){
    addInDict(cal.getIntervalMin(),cal.getIntervalMax(),taille,cal.getId());
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
    auto res = dictionnaireImgMap.find(idImage);
    if(res == dictionnaireImgMap.end()){
        std::vector<int> tmp;
        return tmp;
    }else if(res->second.empty()){
        std::vector<int> tmp;
        return tmp;
    }

    return res->second;

}

void gestionnaire_calque_model::afficheDic(){
    for(auto i : dictionnaireImgMap){
        std::cout << i.first << " : ";
        for(auto j : i.second){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void gestionnaire_calque_model::afficheCalques(){
    for(calque i : listOfCalque){
        std::cout << "id : " << i.getId() << ", min : " << i.getIntervalMin() << ", max : " << i.getIntervalMax() << std::endl;
    }
}

int gestionnaire_calque_model::getCurrentCalqueId() { return idCurrentCalque; }
void gestionnaire_calque_model::setCurrentCalqueId(int newId) { idCurrentCalque = newId;
                                                              std::cout << "Nouveau calque courant = " << idCurrentCalque << std::endl;}
