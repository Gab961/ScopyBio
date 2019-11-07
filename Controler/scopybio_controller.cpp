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

void dessinerAnnotation(int min, int max,QPoint pos1, QPoint pos2, int labelWidth, int labelHeight){

}

void ScopyBio_Controller::dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight)
{
    int min = -2, max = -2;
    int taille = m_pileModel->getImages().size();

    //Verifier s'il existe dans le dico
    if(!gestion_calque.existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        gestion_calque.creerCalque(min,max,taille);
    }

    gestion_calque.dessineFaisceau(min,max,pos1,pos2,labelWidth,labelHeight);


    m_dessinModel->saveZoomFromPicture(pos1, pos2, labelWidth, labelHeight, m_pileModel->getCurrentImage());

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
    int min = -3, max = -3;
    int taille = m_pileModel->getImages().size();
    if(!gestion_calque.existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        gestion_calque.creerCalque(min,max,taille);
    }

        gestion_calque.updateCalqueVert(min,max,taille);
        gestion_calque.afficheDic();
}

void ScopyBio_Controller::removeGreenFilter()
{
    m_dessinModel->removeGreenFilter(m_pileModel->getCurrentImage());
}


void ScopyBio_Controller::applyHistogramFilter()
{
    m_dessinModel->applyHistogramFilter(m_pileModel->getCurrentImage());
}

void ScopyBio_Controller::removeHistogramFilter()
{
    m_dessinModel->removeHistogramFilter(m_pileModel->getCurrentImage());
}

void ScopyBio_Controller::manageNewWhite(QPoint pos, int labelWidth, int labelHeight, bool isZoomView)
{
    m_dessinModel->manageNewWhiteColor(pos, labelWidth, labelHeight, isZoomView);
}

int ScopyBio_Controller::getWhiteColor()
{
    return m_dessinModel->getWhiteValue();
}

void ScopyBio_Controller::setPipetteClick(bool pipetteClick)
{
    m_dessinModel->setListenPipetteClick(pipetteClick);
}

bool ScopyBio_Controller::getPipetteClick()
{
    return m_dessinModel->getListenPipetteClick();
}

bool ScopyBio_Controller::getZoomReady()
{
    return m_dessinModel->getZoomReady();
}

//=======================
// Data_Modele
//=======================

std::string ScopyBio_Controller::getResultDisplayPath()
{
    return m_dataModel->getResultDisplayPath();
}

void ScopyBio_Controller::processResultsWithCrop(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight)
{
    m_dataModel->processResultsWithCrops(m_pileModel->getImages(), pos1, pos2, m_dessinModel->getWhiteValue(), labelWidth, labelHeight);
}

void ScopyBio_Controller::processResultsOnEverything()
{
    m_dataModel->processResults(m_pileModel->getImages());
}

void ScopyBio_Controller::getResults()
{
    m_dataModel->getResults();
}

int ScopyBio_Controller::getItemAtPoint(int posX, int labelWidth)
{
    return m_dataModel->getItemAtPoint(posX, labelWidth);
}

bool ScopyBio_Controller::dataReady()
{
    return m_dataModel->dataReady();
}
