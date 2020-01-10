#include <QPoint>
#include <algorithm>
#include <iostream>
#include "definition.h"

#include "gestionnaire_calques_model.h"

gestionnaire_calque_model::gestionnaire_calque_model(): id(0),isGreen(false),isHistogram(false),isResultat(false),isZoomResultat(true)
{
    pathOfHistogramSave = "tmp";
    pathOfHistogramSave = separator;
    pathOfHistogramSave += "histogram.bmp";
}

void gestionnaire_calque_model::init(int newPileWidth, int newPileHeight){
    pileWidth = newPileWidth;
    pileHeight = newPileHeight;
    isGreen = false;
    isHistogram = false;
    isResultat = false;
    isZoomResultat = true;
    listOfCalque.clear();
    dictionnaireImgMap.clear();
    initGlobalCalques(pileWidth,pileHeight);
    id = 0;
}

void gestionnaire_calque_model::initGlobalCalques(int pileWidth, int pileHeight)
{

    creerCalqueSpecial(pileWidth, pileHeight, HISTOGRAM,HISTOGRAM,HISTOGRAM);

    calque _calqueVert(pileWidth, pileHeight, CALQUEVERT,CALQUEVERT,CALQUEVERT);
    _calqueVert.filtreVert();
    listOfCalque.push_back(_calqueVert);

    creerCalqueSpecial(pileWidth, pileHeight, RESULTAT_VIEW,RESULTAT_VIEW,RESULTAT_VIEW);
    idPertinenceCalque = 2;

    //Calque de pertinence dans le cas d'une analyse utilisateur
    creerCalqueSpecial(pileWidth, pileHeight, CALQUEPERTINENCE,CALQUEPERTINENCE,CALQUEPERTINENCE);
    idUserPertinenceCalque = 3;
}


void gestionnaire_calque_model::saveTmpforDisplay(int idCalque){
    int search = getCalqueIndex(idCalque);

    CImg<float> calquetmp = listOfCalque[search].getCalque();

    std::string path = ".";
    path += separator;
    path += "tmp";
    path += separator;
    path += "calque" + std::to_string(listOfCalque[search].getId()) + ".png";

    calquetmp.save_png(path.c_str(),0);
}


bool gestionnaire_calque_model::existeCalque(int id){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&id](calque &a)->bool { return a.getId() == id; } );
    if(res != listOfCalque.end()){
        return true;
    }else{
        return false;
    }
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

void gestionnaire_calque_model::addCalqueSpecial(CImg<float> cal, int id){
    int search = getCalqueIndex(id);
    listOfCalque[search].setCalque(cal);
}


void gestionnaire_calque_model::removeCalques(int idCalque){
    int search = getCalqueIndex(idCalque);
    if(search != -1){
        listOfCalque.erase(listOfCalque.begin()+search);
    }
}



void gestionnaire_calque_model::calqueShowable(int idCalque, bool show){
    int search = getCalqueIndex(idCalque);
    if(search != -1){
        listOfCalque[search].setCanShow(show);
    }
}


calque gestionnaire_calque_model::getCalqueForDisplay(int id){
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&id](calque &a)->bool { return a.getId() == id ; } );
    return *res;
}

calque gestionnaire_calque_model::getPertinenceCalque(){
    int id = RESULTAT_VIEW;
    auto res = std::find_if(listOfCalque.begin(), listOfCalque.end(), [&id](calque &a)->bool { return a.getId() == id ; } );
    return *res;
}

std::vector<calque> gestionnaire_calque_model::getAllCalques() const
{
    return listOfCalque;
}


void gestionnaire_calque_model::creerCalque(int width, int height, int min, int max, int taille){
    calque _calque(width, height, min,max,id);


    listOfCalque.push_back(_calque);

    addInDict(min,max,taille,id);

    setCurrentCalqueId(id);

    id++;
}

void gestionnaire_calque_model::creerCalqueSpecial(int width, int height, int min, int max,int idCalque){
    calque _calque(width, height, min,max,idCalque);

    listOfCalque.push_back(_calque);
}


void gestionnaire_calque_model::reinitUserPertinenceCalque(int width, int height)
{
    calque newCalque = getCalqueForDisplay(CALQUEPERTINENCE);

    CImg<float> newImage(width,height,1,4,0);
    newCalque.setCalque(newImage);

    listOfCalque[idUserPertinenceCalque] = newCalque;
}


void gestionnaire_calque_model::reinitPertinenceCalque()
{
    calque newCalque = getCalqueForDisplay(RESULTAT_VIEW);

    CImg<float> newImage(pileWidth,pileHeight,1,4,0);
    newCalque.setCalque(newImage);

    listOfCalque[idPertinenceCalque] = newCalque;
}


void gestionnaire_calque_model::reinitFaisceauCalque()
{
    calque newCalque = getCalqueForDisplay(FAISCEAU);

    CImg<float> newImage(pileWidth,pileHeight,1,4,0);
    newCalque.setCalque(newImage);

    int indexFaisceau = getCalqueIndex(FAISCEAU);

    listOfCalque[indexFaisceau] = newCalque;
}


void gestionnaire_calque_model::manageNewAnalyse(int pertinence, QPoint pos1, QPoint pos2){
    calque newCalque = getCalqueForDisplay(RESULTAT_VIEW);

    newCalque.dessinerRectanglePertinence(pos1,pos2,pertinence);

    listOfCalque[idPertinenceCalque] = newCalque;
}



void gestionnaire_calque_model::manageNewUserAnalyse(int pertinence, QPoint pos1, QPoint pos2){
    calque newCalque = getCalqueForDisplay(CALQUEPERTINENCE);

    newCalque.dessinerRectanglePertinence(pos1,pos2,pertinence);

    listOfCalque[idUserPertinenceCalque] = newCalque;
}


void gestionnaire_calque_model::dessineFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){

    int search = getCalqueIndex(FAISCEAU);
    if(search != -1){
        listOfCalque[search].dessinerFaisceau(pos1,pos2,labelWidth,labelHeight);
    }
}


void gestionnaire_calque_model::dessinLigne(QPoint pos1, QPoint pos2, int brushSize, int labelWidth, int labelHeight, bool isDrawing){

    int search = getCalqueIndex(idCurrentCalque);
    if(search != -1){
        listOfCalque[search].dessinerLigne(pos1, pos2, brushSize, labelWidth,labelHeight, isDrawing);
    }
}


void gestionnaire_calque_model::dessinText(QPoint pos1, std::string text, int fontSize, int labelWidth, int labelHeight){
    int search = getCalqueIndex(idCurrentCalque);
    if(search != -1){
        listOfCalque[search].ecrireText(pos1,text,fontSize,labelWidth,labelHeight);
    }
}


void gestionnaire_calque_model::dessinCercle(QPoint origPoint, int diameter, int labelWidth, int labelHeight)
{
    int search = getCalqueIndex(idCurrentCalque);
    if(search != -1){
        listOfCalque[search].dessinerCercle(origPoint,diameter,labelWidth,labelHeight);
    }
}


void gestionnaire_calque_model::dessinCarre(QPoint origPoint, int diameter, int labelWidth, int labelHeight)
{
    int search = getCalqueIndex(idCurrentCalque);
    if(search != -1){
        listOfCalque[search].dessinerCarre(origPoint,diameter,labelWidth,labelHeight);
    }
}


void gestionnaire_calque_model::updateCalqueVert(){
    isGreen = !isGreen;
}

void gestionnaire_calque_model::updateResultat(){
    isResultat = !isResultat;
}

void gestionnaire_calque_model::updateZoomResultat(){
    isZoomResultat = !isZoomResultat;
}


void gestionnaire_calque_model::updateHistogram(){
    isHistogram = !isHistogram;
}


void gestionnaire_calque_model::updateQuadrillage(int columns, int lines){
    calque newCalque = getCalqueForDisplay(RESULTAT_VIEW);

    newCalque.filtreQuadrillage(columns, lines);

    listOfCalque[idPertinenceCalque] = newCalque;
}

void gestionnaire_calque_model::updateUserQuadrillage(int columns, int lines){
    calque newCalque = getCalqueForDisplay(CALQUEPERTINENCE);

    newCalque.filtreQuadrillage(columns, lines);

    listOfCalque[idUserPertinenceCalque] = newCalque;
}

void gestionnaire_calque_model::mergeUserAnalysis(CImg<float> zoom, std::string zoomPath)
{
    if(isZoomResultat){
        calque overlay = getCalqueForDisplay(CALQUEPERTINENCE);
        zoom.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);
        zoom.save_bmp(zoomPath.c_str());
    }
    else
        zoom.save_bmp(zoomPath.c_str());
}

void gestionnaire_calque_model::mergeCalques(std::vector<int> ids, CImg<float> currentDisplayedImage, std::string pathOfMainDisplay){
    //Contraste en premier
    if (isHistogram)
    {
        calque overlay = getCalqueForDisplay(HISTOGRAM);
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
        calque overlay = getCalqueForDisplay(CALQUEVERT);
        currentDisplayedImage.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);
    }

    if(isResultat){
        calque overlay = getCalqueForDisplay(RESULTAT_VIEW);
        currentDisplayedImage.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);
    }

    if(ids.size() != 0)
    {
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

    auto search = getCalqueIndex(FAISCEAU);
    if(search != -1){
        calque overlay = listOfCalque[search];
        currentDisplayedImage.draw_image(0,0,0,0,overlay.getCalque(),overlay.getCalque().get_channel(3),1,255);

    }

    //On sauvegarde l'ensemble
    currentDisplayedImage.save_bmp(pathOfMainDisplay.c_str());
}

//MEMENTO
void gestionnaire_calque_model::undo(){
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
void gestionnaire_calque_model::setCurrentCalqueId(int newId) { idCurrentCalque = newId; }
void gestionnaire_calque_model::setShowResultat(bool newValue) { isResultat = newValue; }
