#pragma once

#include <iostream>
#include <QLayout>
#include <QListWidget>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

class Pile_View: public QListWidget
{
    Q_OBJECT

    public:
        Pile_View(QWidget *parent);
        CImg<float> getImage(int i);

    signals:
        void pileInitDone();

    public slots:
        void openFile(std::string path);

    private:
        std::string *m_path;
        CImgList<float> m_imgList;
};
