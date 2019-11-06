#include "calque.h"
#include "annotation_user_memento.h"

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

calque::calque(int min, int max, int nom) : intervalMin(min), intervalMax(max), name(nom)
{

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
