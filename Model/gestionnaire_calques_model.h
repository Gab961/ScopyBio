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

    bool existeCalque(int min, int max);

    void creerCalque(int width, int height, int min, int max, int taille);
    int getCalque(int min, int max);
    void addCalques(std::vector<calque> calques, int taille);
    void removeCalques(int min, int max);
    void calqueShowable(int min, int max, bool show);
    void dessineFaisceau(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void reinitPertinenceCalque();
    void reinitFaisceauCalque();
    void manageNewAnalyse(int pertinence, QPoint pos1, QPoint pos2);
    void dessinLigne(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void updateCalqueVert(int min, int max, int taille);
    void updateHistogram(int min, int max, int taille);
    void updateQuadrillage(QPoint posInitiale, int columns, int lines);
    calque getCalqueForDisplay(int min, int max);
    calque getCalqueForDisplay(int id);
    calque getPertinenceCalque();
    std::vector<calque> getAllCalques() const;
    void setCalque(int min, int max, calque cal);


    void mergeCalques(std::vector<int> ids, CImg<float> currentDisplayedImage, std::string pathOfMainDisplay);
    //    void merge2Images(calque &a, calque b);


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
    std::string pathOfHistogramSave = "tmp/histogram.bmp";
    int idPertinenceCalque;
};
