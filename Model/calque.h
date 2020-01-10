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
    bool canShow;         //Permet d'afficher ou masquer le calque.
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
    /**
     * @brief dessinerFaisceau draw on the layer a beam
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

    /**
     * @brief dessinerRectangle draw on the layer a rectangle
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

    /**
     * @brief dessinerRectanglePertinence draw on the layer a rectangle for displaying user results
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param pertinence Level of pertinence
     */
    void dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence);

    /**
     * @brief dessinerLigne draw a line on the layer between 2 positions of the mouse
     * @param pos1 begin of the line
     * @param pos2 end of the line
     * @param brushSize width of the line
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param isDrawing To know if we draw (true) or erase (false)
     */
    void dessinerLigne(QPoint pos1, QPoint pos2, int brushSize, int labelWidth, int labelHeight, bool isDrawing);

    /**
     * @brief dessinerRond draw a circle at the position of the mouse
     * @param pos position of the mouse
     * @param pertinence level of pertinence
     */
    void dessinerRond(QPoint pos, int pertinence);

    /**
     * @brief dessinerCarre draw a square in the layer at the position of the mouse
     * @param posOrig position of the mouse
     * @param diameter size of the square
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessinerCarre(QPoint posOrig, int diameter, int labelWidth, int labelHeight);

    /**
     * @brief dessinerCercle draw circle on the layer at the position of the mouse
     * @param posOrig position of the mouse
     * @param diameter diameter of the circle
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessinerCercle(QPoint posOrig, int diameter, int labelWidth, int labelHeight);

    /**
     * @brief filtreVert apply the green filter on layer
     */
    void filtreVert();

    //TODO
    /**
     * @brief filtreHistogram TODO
     */
    void filtreHistogram();

    /**
     * @brief filtreQuadrillage
     * @param columns
     * @param lines
     */
    void filtreQuadrillage(int columns, int lines);

    /**
     * @brief ecrireText draw a text message on the layer at the position of the mouse
     * @param pos1 position of the mouse
     * @param text_a_ecrire text that should be displayed
     * @param fontSize size of the text
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void ecrireText(QPoint pos1, std::string text_a_ecrire, int fontSize, int labelWidth, int labelHeight);

};

