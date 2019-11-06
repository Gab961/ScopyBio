#pragma once

#include <../CImg.h>

using namespace cimg_library;
class annotation_user_memento;

class calque
{
private:
    CImg<float> _calque;
    int intervalMin;
    int intervalMax;
    int name;



public:
    calque(int min, int max, int nom);

    annotation_user_memento *createMemento();
    void reinstateMemento(annotation_user_memento *mem);

    CImg<float> getCalque() const;
    void setCalque(const CImg<float> &calque);

    int getName() const;
    int getIntervalMin() const;
    int getIntervalMax() const;
};

