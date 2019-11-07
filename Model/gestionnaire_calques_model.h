#pragma once

#include <string>
#include <cstdlib>
#include <vector>
#include <map>

#include <iostream>

class QPoint;

#include "calque.h"

using numImg = int;

class calque;
class command_memento;

class gestionnaire_calque_model
{
public:
    gestionnaire_calque_model();

    void saveTmpforDisplay(int min, int max);

    bool existeCalque(int min, int max);

    void creerCalque(int min, int max, int taille);
    int getCalque(int min, int max);
    void dessineFaisceau(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void updateCalqueVert(int min, int max, int taille);
    calque getCalqueForDisplay(int min, int max);


    void afficheDic(){
        for(auto i : dictionnaireImgMap){
            std::cout << i.first << " : ";
            for(auto j : i.second){
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }

protected:

      std::map<numImg,std::vector<int>> dictionnaireImgMap;
      std::vector<calque> listOfCalque;
      int id;
      bool isGreen;
};
