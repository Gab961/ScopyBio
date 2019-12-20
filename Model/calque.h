#pragma once

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



public:
    calque(int width, int height, int min, int max, int _id);

    annotation_user_memento *createMemento();
    void reinstateMemento(annotation_user_memento *mem);

    CImg<float> getCalque() const;
    void saveCalque(std::string path);
    void setCalque(const CImg<float> &calque);

    int getId() const;
    int getIntervalMin() const;
    int getIntervalMax() const;
    bool getCanShow() const;
    void setCanShow(bool value);

    //          ACTIONS !
    void dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence);
    void dessinerLigne(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void dessinerRond(QPoint pos, int pertinence);
    void filtreVert();
    void filtreHistogram();
    void filtreQuadrillage(QPoint posInit, int columns, int lines);
    void ecrireText(QPoint pos1, int labelWidth, int labelHeight,std::string text_a_ecrire, CImg<float> & currentPicture);

};

