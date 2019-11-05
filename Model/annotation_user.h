#pragma once

#include <../CImg.h>

using namespace cimg_library;
class annotation_user_memento;

class annotation_user
{
private:
    CImg<float> calque;

public:
    annotation_user(CImg<float> _calque);

    annotation_user_memento *createMemento();
    void reinstateMemento(annotation_user_memento *mem);

    CImg<float> getCalque() const;
};

