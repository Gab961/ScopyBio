#include <QPoint>
#include <iostream>

#include "calque.h"
#include "annotation_user_memento.h"

calque::calque(int min, int max, int _id):intervalMin(min), intervalMax(max), id(_id)
{
//    int yellow[] = {255,255,0};
    _calque.assign(514,476,1,3,255);
    //cimg_forXY(_calque, x, y) { _calque(x,y,0) = 255;_calque(x,y,1) = 255;_calque(x,y,2) = 255;}
//    _calque.draw_circle(30,30,20,yellow,1);
    _calque.draw_image(0,0,0,0,_calque,_calque.get_channel(3),1,255);
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

void calque::dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){
    _calque.assign(514,476,1,3,255);
    _calque.draw_image(0,0,0,0,_calque,_calque.get_channel(3),1,255);
    _calque = dessine.dessinerRectangle(pos1,pos2,labelWidth,labelHeight,_calque);
}
