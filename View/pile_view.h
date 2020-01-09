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
        /**
         * @brief Pile_View
         * @param parent
         * @param scopybioController
         */
        Pile_View(QWidget *parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief getImage
         * @param i
         * @return
         */
        CImg<float> getImage(int i);
        void connections();

    signals:
        void pileInitDone();
        void rowClicked(int row);

    public slots:
        void openFile(std::string path);
        void changeToElement(int i);
        void rowChanged(int row);

    private:
        ScopyBio_Controller *m_scopybioController;
};
