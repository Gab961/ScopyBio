#include <QPoint>
#include "scopybio_controller.h"
#include <iostream>

ScopyBio_Controller::ScopyBio_Controller() : m_pileModel(new pile_model()), m_dessinModel(new dessin_model())
{}

void ScopyBio_Controller::ecrireCoucou()
{
    std::cout << "Marche controler" << std::endl;
    testModele();
}

void ScopyBio_Controller::testModele()
{
    //    m_pileModel->loadNewFilename("Coucou le gentil modèle");
}

//=======================
// Pile_Modele
//=======================
void ScopyBio_Controller::loadNewTiffFile(std::string filename)
{
    if (filename.length()>0)
    {
        m_pileModel->loadNewFilename(filename);
    }
}

/**
 * @brief ScopyBio_Controller::getLoadedTiffList
 * @return
 */
CImgList<float> ScopyBio_Controller::getLoadedTiffList()
{
    return m_pileModel->getImages();
}

/**
 * @brief ScopyBio_Controller::getCurrentTiff
 * @return
 */
CImg<float> ScopyBio_Controller::getCurrentTiff()
{
    return m_pileModel->getCurrentImage();
}

std::vector<std::string> ScopyBio_Controller::getIconFilenames()
{
    return m_pileModel->getIconFilenames();
}

CImg<float> ScopyBio_Controller::getImageAtIndex(int i) const
{
    return m_pileModel->getImageAtIndex(i);
}


//=======================
// Dessin_Modele
//=======================
void ScopyBio_Controller::dessinerRectangle(QPoint pos1, QPoint pos2)
{
    m_dessinModel->dessinerRectangle(pos1, pos2, m_pileModel->getCurrentImage());
}

std::string ScopyBio_Controller::getMainDisplayPath()
{
    return m_dessinModel->getMainDisplayPath();
}

std::string ScopyBio_Controller::getZoomDisplayPath()
{
    return m_dessinModel->getZoomDisplayPath();
}


void ScopyBio_Controller::saveAsMainDisplay(int i)
{
    m_dessinModel->saveImageAsMainDisplay(m_pileModel->getImageAtIndex(i));
}
