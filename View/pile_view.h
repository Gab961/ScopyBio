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

        /**
         * @brief connections
         */
        void connections();

    signals:
        void pileInitDone();
        void rowClicked(int row);

    public slots:
        /**
         * @brief openFile : Load tiff file and for each picture,
         *                   create items of the list widget
         *                   with a preview of the picture as icon
         * @param path
         */
        void openFile(std::string path);

        /**
         * @brief changeToElement : Show the correct picture when an item is triggered
         * @param i
         */
        void changeToElement(int i);

        /**
         * @brief rowChanged
         * @param row
         */
        void rowChanged(int row);

    private:
        ScopyBio_Controller *m_scopybioController;
};
