#pragma once

#include <string>
#include <cstdlib>
#include <vector>
#include <map>

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
    calque &getCalque(int min, int max);
    void dessineFaisceau(int min, int max, QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

protected:

      std::map<numImg,std::vector<int>> dictionnaireImgMap;
      std::vector<calque> listOfCalque;
      int id;
};
