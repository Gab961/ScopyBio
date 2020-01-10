#include <QPoint>
#include <iostream>

#include "calque.h"


calque::calque(int width, int height, int min, int max, int _id): _calque(width,height,1,4,0), intervalMin(min), intervalMax(max), id(_id),canShow(true), numList(-1), highWater(0)
{
    addMemento();
}

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
    path += ".cimg";
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
}

void calque::addMemento(){
    if(numList < highWater-1){
        mementoList.erase(mementoList.begin()+numList+1,mementoList.end());
        highWater = numList+1;
    }
    std::cout << "numList = " << numList << " Highwater = " << highWater << std::endl;

    mementoList.push_back(_calque);
    numList++;
    highWater++;
    std::cout << "numList = " << numList << " Highwater = " << highWater << std::endl;
    std::cout << "memento.size = " << mementoList.size() << std::endl;
}

void calque::clearMemento(){
    mementoList.clear();
}

//                               ACTION !

void calque::dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    _calque = dessine.dessinerRectangle(pos1,pos2,labelWidth,labelHeight,_calque);
}

void calque::dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence){
    _calque = dessine.dessinerRectanglePertinence(pos1,pos2,pertinence,_calque);
}



void calque::dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    CImg<float> tmp(_calque.width(),_calque.height(),1,4,0);
    _calque = dessine.dessinerFaisceau(pos1,pos2,labelWidth,labelHeight,tmp);
}

void calque::dessinerLigne(QPoint pos1, QPoint pos2, int brushSize, int labelWidth, int labelHeight, bool isDrawing){
    _calque = dessine.dessinerLigne(pos1,pos2,isDrawing, brushSize, labelWidth,labelHeight,_calque);
}


void calque::dessinerCarre(QPoint posOrig, int diameter, int labelWidth, int labelHeight){
    _calque = dessine.dessinerCarre(posOrig,diameter,labelWidth,labelHeight,_calque);
}


void calque::dessinerCercle(QPoint posOrig, int diameter, int labelWidth, int labelHeight){
    _calque = dessine.dessinerCercle(posOrig,diameter,labelWidth,labelHeight,_calque);
}


void calque::filtreVert(){
    _calque = dessine.applyGreenFilter(_calque);
}

void calque::filtreQuadrillage(int columns, int lines){
    _calque = dessine.applyQuadrillageFilter(columns, lines, _calque);
}

void calque::filtreHistogram(){
    _calque = dessine.applyHistogramFilter(_calque);
}

void calque::ecrireText(QPoint pos1, std::string text_a_ecrire, int fontSize, int labelWidth, int labelHeight){
    _calque = dessine.ecrireText(pos1,text_a_ecrire,fontSize,labelWidth,labelHeight, _calque);
}
