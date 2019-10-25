#pragma once

#include <iostream>
#include <QWidget>


#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

class Pile_View: public QWidget
{
    Q_OBJECT

    public:
        Pile_View();

    signals:

    public slots:
        void openFile(std::string path);

    private:
        std::string *m_path;
        CImgList<float> m_imgList;
};
