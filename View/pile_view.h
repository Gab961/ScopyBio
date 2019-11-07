#pragma once

#include <iostream>
#include <QLayout>
#include <QListWidget>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;
class ScopyBio_Controller;

class Pile_View: public QListWidget
{
    Q_OBJECT

    public:
        Pile_View(QWidget *parent, ScopyBio_Controller *scopybioController);
        CImg<float> getImage(int i);

    signals:
        void pileInitDone();

    public slots:
        void openFile(std::string path);
        void changeToElement(int i);

    private:
        ScopyBio_Controller *m_scopybioController;
};
