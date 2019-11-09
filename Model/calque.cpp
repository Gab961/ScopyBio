#include <QPoint>
#include <iostream>

#include "calque.h"
#include "annotation_user_memento.h"

calque::calque(int min, int max, int _id): _calque(514,476,1,4,0), intervalMin(min), intervalMax(max), id(_id)
{
}

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
 * @brief calque::dessinerFaisceau supprimer le calque actuel et redessine le rectangle.
 * @param pos1
 * @param pos2
 * @param labelWidth
 * @param labelHeight
 */
void calque::dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    CImg<float> tmp(514,476,1,4,0);
    _calque = dessine.dessinerRectangle(pos1,pos2,labelWidth,labelHeight,tmp);
}

/**
 * @brief calque::filtreVert pour créer le calque vert, sert juste au début du programme.
 */
void calque::filtreVert(){
    _calque = dessine.applyGreenFilter(_calque);
}
