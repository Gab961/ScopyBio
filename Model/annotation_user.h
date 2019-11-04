#ifndef ANNOTATION_USER_H
#define ANNOTATION_USER_H

#include <../CImg.h>
#include "annotation_user_memento.h"

using namespace cimg_library;

class annotation_user
{
private:
    CImg<float> calque;

public:
    annotation_user(CImg<float> _calque);


    void save();
    annotation_user_memento *createMemento();
    void reinstateMemento(annotation_user_memento *mem);

    CImg<float> getCalque() const;
};

#endif // ANNOTATION_USER_H
