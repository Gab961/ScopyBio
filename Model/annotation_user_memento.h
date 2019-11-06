#pragma once

#include "CImg.h"

#include "calque.h"

using namespace cimg_library;

class annotation_user_memento
{

private:
  friend class calque;
  CImg<float> _calque;

public:

    annotation_user_memento(CImg<float> _cal)
    {
        _calque = _cal;
    }


    CImg<float> getCalque() const;
};



