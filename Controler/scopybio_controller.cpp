#include <QPoint>
#include "scopybio_controller.h"
#include <iostream>

ScopyBio_Controller::ScopyBio_Controller() : m_pileModel(new pile_model()), m_dessinModel(new dessin_model()), m_dataModel(new data_model())
{}

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

bool ScopyBio_Controller::fileReady()
{
    return m_pileModel->fileReady();
}


void ScopyBio_Controller::saveCurrent(int indiceEnCours)
{
    m_pileModel->setCurrentImage(indiceEnCours);
}

//=======================
// Dessin_Modele
//=======================
void ScopyBio_Controller::dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight)
{
    m_dessinModel->dessinerRectangle(pos1, pos2, labelWidth, labelHeight, m_pileModel->getCurrentImage());
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


void ScopyBio_Controller::applyGreenFilter()
{
    m_dessinModel->applyGreenFilter(m_pileModel->getCurrentImage());
}

void ScopyBio_Controller::removeGreenFilter()
{
    m_dessinModel->removeGreenFilter(m_pileModel->getCurrentImage());
}

//=======================
// Data_Modele
//=======================

std::string ScopyBio_Controller::getResultDisplayPath()
{
    return m_dataModel->getResultDisplayPath();
}

void ScopyBio_Controller::processResultsWithCrop(QPoint pos1, QPoint pos2)
{
    m_dataModel->processResultsWithCrops(m_pileModel->getImages(), pos1, pos2);
}

void ScopyBio_Controller::processResultsOnEverything()
{
    m_dataModel->processResults(m_pileModel->getImages());
}

void ScopyBio_Controller::getResults()
{
    m_dataModel->getResults();
}
