#include <QPoint>
#include <iostream>

#include "calque.h"
#include "annotation_user_memento.h"

calque::calque(int width, int height, int min, int max, int _id): _calque(width,height,1,4,0), intervalMin(min), intervalMax(max), id(_id)
{}

int calque::getId() const
{
    return id;
}

int calque::getIntervalMin() const
{
    return intervalMin;
}

int calque::getIntervalMax() const
{
    return intervalMax;
}

void calque::setCalque(const CImg<float> &calque)
{
    _calque = calque;
}

CImg<float> calque::getCalque() const
{
    return _calque;
}

annotation_user_memento *calque::createMemento(){
    return new annotation_user_memento(_calque);
}

void calque::reinstateMemento(annotation_user_memento *mem){
    _calque = mem->_calque;
}

//                               ACTION !

void calque::dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    _calque = dessine.dessinerRectangle(pos1,pos2,labelWidth,labelHeight,_calque);
}

/**
 * Plus utilisé, remplacé par dessinerRectangle
 */
void calque::dessinerRond(QPoint pos, int pertinence){
    _calque = dessine.dessinerRond(pos, pertinence, _calque);
}

void calque::dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence){
    _calque = dessine.dessinerRectanglePertinence(pos1,pos2,pertinence,_calque);
}


/**
 * @brief calque::dessinerFaisceau supprimer le calque actuel et redessine le rectangle.
 * @param pos1
 * @param pos2
 * @param labelWidth
 * @param labelHeight
 */
void calque::dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    CImg<float> tmp(_calque.width(),_calque.height(),1,4,0);
    _calque = dessine.dessinerRectangle(pos1,pos2,labelWidth,labelHeight,tmp);
}

/**
 * @brief calque::dessinerLigne
 * @param pos1
 * @param pos2
 * @param labelWidth
 * @param labelHeight
 */
void calque::dessinerLigne(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    _calque = dessine.dessinerLigne(pos1,pos2,labelWidth,labelHeight,_calque);
}

/**
 * @brief calque::filtreVert pour créer le calque vert, sert juste au début du programme.
 */
void calque::filtreVert(){
    _calque = dessine.applyGreenFilter(_calque);
}

void calque::filtreQuadrillage(int columns, int lines){
    _calque = dessine.applyQuadrillageFilter(columns, lines, _calque);
}

/**
 * @brief calque::filtreVert pour créer le calque vert, sert juste au début du programme.
 */
void calque::filtreHistogram(){
    _calque = dessine.applyHistogramFilter(_calque);
}
