#include <QPoint>
#include <iostream>

#include "calque.h"


calque::calque(int width, int height, int min, int max, int _id): _calque(width,height,1,4,0), intervalMin(min), intervalMax(max), id(_id),canShow(true), numList(0), highWater(0)
{}

int calque::getId() const
{
    return id;
}

bool calque::getCanShow() const
{
    return canShow;
}

void calque::setCanShow(bool value)
{
    canShow = value;
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

void calque::saveCalque(std::string path)
{
    _calque.save_cimg(path.c_str());
}

//MEMENTO

void calque::reinstateMemento(int mem){
    _calque = mementoList[mem];
}

void calque::undo()
{
    if (numList == 0)
    {
        return ;
    }
    numList--;
    reinstateMemento(numList);
}

void calque::redo()
{
    if (numList >= highWater-1)
    {
        return ;
    }
    numList++;
    reinstateMemento(numList);
    std::cout << "numList = " << numList << " Highwater = " << highWater << std::endl;
}

void calque::addMemento(){
    if(numList < highWater){
        mementoList.erase(mementoList.begin()+numList,mementoList.end());
    }

    mementoList.push_back(_calque);
    numList++;
    highWater++;
}

//                               ACTION !

void calque::dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    _calque = dessine.dessinerRectangle(pos1,pos2,labelWidth,labelHeight,_calque);
    addMemento();
}

/**
 * Plus utilisé, remplacé par dessinerRectangle
 */
void calque::dessinerRond(QPoint pos, int pertinence){
    _calque = dessine.dessinerRond(pos, pertinence, _calque);
    addMemento();
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
    _calque = dessine.dessinerFaisceau(pos1,pos2,labelWidth,labelHeight,tmp);
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
    addMemento();
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

void calque::ecrireText(QPoint pos1, int labelWidth, int labelHeight,std::string text_a_ecrire, CImg<float> & currentPicture){
    _calque = dessine.ecrireText(pos1,labelWidth,labelHeight,text_a_ecrire,currentPicture);
}
