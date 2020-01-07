#pragma once

#include<vector>

#include "CImg.h"
#include "dessin_model.h"

#define cimg_use_png

using namespace cimg_library;
class annotation_user_memento;
class dessin_model;

class QPoint;

class calque
{
private:
    CImg<float> _calque;
    dessin_model dessine; //Pour dessiner sur les calques. Pourquoi s'embeter à écrire les fonctions de dessin si Bastien l'a déjà fait ¯\_(ツ)_/¯
    int intervalMin;
    int intervalMax;
    int id;
    bool canShow;
    //MEMENTO
    int numList;
    int highWater;
    std::vector<CImg<float>> mementoList;



public:
    calque(int width, int height, int min, int max, int _id);
    ~calque(){mementoList.clear();}

    CImg<float> getCalque() const;
    void saveCalque(std::string path);
    void setCalque(const CImg<float> &calque);

    int getId() const;
    int getIntervalMin() const;
    int getIntervalMax() const;
    bool getCanShow() const;
    void setCanShow(bool value);

    //MEMENTO
    void undo();
    void redo();
    void addMemento();
    void reinstateMemento(int mem);
    void clearMemento();


    //          ACTIONS !
    void dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence);
    void dessinerLigne(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void dessinerRond(QPoint pos, int pertinence);
    void dessinerCarre(QPoint posOrig, int diameter, int labelWidth, int labelHeight);
    void dessinerCercle(QPoint posOrig, int diameter, int labelWidth, int labelHeight);
    void filtreVert();
    void filtreHistogram();
    void filtreQuadrillage(int columns, int lines);
    void ecrireText(QPoint pos1, std::string text_a_ecrire, int fontSize, int labelWidth, int labelHeight);

};

