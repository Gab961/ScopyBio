#include <QPoint>
#include "calque.h"
#include "annotation_user_memento.h"

calque::calque(int min, int max, int nom) :intervalMin(min), intervalMax(max), name(nom)
{
    _calque(514,476,1,3);
    //_calque.assign(514,476);

}

int calque::getName() const
{
    return name;
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
