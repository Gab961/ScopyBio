#ifndef ANNOTATION_USER_MEMENTO_H
#define ANNOTATION_USER_MEMENTO_H

#include "../CImg.h"

#include "annotation_user.h"

using namespace cimg_library;

class annotation_user_memento
{

private:
  friend class annotation_user;
  CImg<float> calque;

public:

    annotation_user_memento(CImg<float> _calque)
    {
        calque = _calque;
    }


};

#endif // ANNOTATION_USER_MEMENTO_H

