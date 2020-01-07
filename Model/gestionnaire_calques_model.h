#pragma once

#include <string>
#include <cstdlib>
#include <vector>
#include <map>

#include <iostream>

#include "definition.h"

class QPoint;

#include "calque.h"

using numImg = int;

class command_memento;

class gestionnaire_calque_model
{
public:
    gestionnaire_calque_model();

    void init(int pileWidth, int pileHeight);

    void initGlobalCalques(int _pileWidth, int _pileHeight);

    void saveTmpforDisplay(int min, int max);
    void saveTmpforDisplay(int idCalque);

    bool existeCalque(int min, int max);
    bool existeCalque(int id);

    void creerCalque(int width, int height, int min, int max, int taille);
    int getCalque(int min, int max);
    int getCalqueIndex(int id);
    void addCalques(std::vector<calque> calques, int taille);
    void removeCalques(int min, int max);
    void removeCalques(int idCalque);
    void calqueShowable(int min, int max, bool show);
    void calqueShowable(int idCalque, bool show);
    void dessineFaisceau(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void dessinText(int min, int max, QPoint pos1, std::string text, int fontSize, int labelWidth, int labelHeight);
    void dessinCercle(int min, int max, QPoint origPoint, int diameter, int labelWidth, int labelHeight);
    void dessinCarre(int min, int max, QPoint origPoint, int diameter, int labelWidth, int labelHeight);
    void reinitPertinenceCalque();
    void reinitUserPertinenceCalque(int width, int height);
    void reinitFaisceauCalque();
    void manageNewUserAnalyse(int pertinence, QPoint pos1, QPoint pos2);
    void manageNewAnalyse(int pertinence, QPoint pos1, QPoint pos2);
    void dessinLigne(int idCalque, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void updateCalqueVert();
    void updateHistogram();
    void updateResultat();
    void updateZoomResultat(CImg<float> zoom, std::string zoomPath);
    void dessinLigne(int min, int max, QPoint pos1, QPoint pos2, int brushSize, int labelWidth, int labelHeight, bool isDrawing);
    void updateQuadrillage(int columns, int lines);
    void updateUserQuadrillage(int columns, int lines);
    calque getCalqueForDisplay(int min, int max);
    calque getCalqueForDisplay(int id);
    calque getPertinenceCalque();
    std::vector<calque> getAllCalques() const;
    void setCalque(int min, int max, calque cal);
    int getCurrentCalqueId();
    void setCurrentCalqueId(int newId);

    void mergeUserAnalysis(CImg<float> zoom, std::string zoomPath);
    void mergeCalques(std::vector<int> ids, CImg<float> currentDisplayedImage, std::string pathOfMainDisplay);
    //    void merge2Images(calque &a, calque b);

    //MEMENTO
    void undo();
    void redo();
    void addMemento();


    //          Fonction pour le dictionnaire
    void addInDict(int min, int max, int taille, int id);
    void addInDict(calque cal, int taille);
    void removeFromDict(int min, int max, int id);
    std::vector<int> getListOfCalqueFromImage(int idImage);

    /*
     * Permet d'afficher le dictionnaire
     *
     * */
    void afficheDic();
    void afficheCalques();


protected:
    // Le memento ne fonctionne pas encore. on fait sans.
    int pileWidth;
    int pileHeight;
    std::map<numImg,std::vector<int>> dictionnaireImgMap;// Associe une image à une liste de calque.
    std::vector<calque> listOfCalque;//Sauvegarde tous les calques dont on en a besoin
    int id;//Permet de créer des calques avec un identifiant unique.
    bool isGreen; // Pour savoir s'il faut afficher le calque vert ou non
    bool isHistogram; //Pour savoir s'il faut afficher le calque contraste ou non
    bool isResultat;
    bool isZoomResultat;
    std::string pathOfHistogramSave = "tmp/histogram.bmp";
    int idPertinenceCalque;
    int idUserPertinenceCalque;
    int idCurrentCalque;
};
