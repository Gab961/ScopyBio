#include <QPoint>
#include "scopybio_controller.h"
#include <iostream>

ScopyBio_Controller::ScopyBio_Controller() : m_pileModel(new pile_model()), m_dessinModel(new dessin_model()), m_dataModel(new data_model()), m_gestion_calque(new gestionnaire_calque_model)
{}
//=======================
// AFFICHAGE
//=======================

void ScopyBio_Controller::DisplayResultImage(int idImage){
    m_gestion_calque->mergeCalques(m_gestion_calque->getListOfCalqueFromImage(idImage), m_pileModel->getCurrentImage(), m_dessinModel->getMainDisplayPath());
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

/**
 * @brief ScopyBio_Controller::dessinerFaisceau dessine un rectangle dans un calque et le créer si besoin.
 * @param labelWidth largeur de la fenetre
 * @param labelHeight longueur de la fenetre
 */
void ScopyBio_Controller::dessinerFaisceau(int labelWidth, int labelHeight)
{
    int min = -2, max = -2;
    int taille = m_pileModel->getImages().size();

    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalque(min,max,taille);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessineFaisceau(min,max,pos1,pos2,labelWidth,labelHeight);
    gestion_calque.dessineFaisceau(min,max,m_faisceauModel->getTopLeft(),m_faisceauModel->getBotRight(),labelWidth,labelHeight);

    //Necessaire pour afficher le zoom.
    m_dessinModel->saveZoomFromPicture(m_faisceauModel->getTopLeft(), m_faisceauModel->getBotRight(), labelWidth, labelHeight, m_pileModel->getCurrentImage());

    DisplayResultImage(0);

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

/**
 * @brief ScopyBio_Controller::applyGreenFilter active le filtre vert
 */
void ScopyBio_Controller::applyGreenFilter()
{
    // -3 = filtre vert
    // Normalement le calque vert est déjà créé, cette fonction met juste à jour le dictionnaire de calque. il doit y avoir une fonction qui met à jour la view.
    // /!\ Bug parce que le remove est fait dans une autre fonction
    int min = -3, max = -3;
    int taille = m_pileModel->getImages().size();
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalque(min,max,taille);
    }

        m_gestion_calque->updateCalqueVert(min,max,taille);
  //      gestion_calque.afficheDic();

    DisplayResultImage(0);
}

/* fonction de mise à jour de la vue
 *
 * La fonction reçoit le numéro de l'image.
 * appelle une fonction dans le gestionnaire qui retourne la liste de calque s'appliquant à l'image genre vector : { 0,2,6 } c'est à dire que les images calques calque0, calque2 et calque6 doivent etre affichés
 *
 * */

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

bool ScopyBio_Controller::getBaseColorGiven()
{
    return m_dessinModel->getBaseColorGiven();
}

//=======================
// Data_Modele
//=======================

std::string ScopyBio_Controller::getResultDisplayPath()
{
    return m_dataModel->getResultDisplayPath();
}

void ScopyBio_Controller::processResultsWithCrop(int labelWidth, int labelHeight)
{
    m_dataModel->processResultsWithCrops(m_pileModel->getImages(), m_faisceauModel->getTopLeft(), m_faisceauModel->getBotRight(), m_dessinModel->getWhiteValue(), labelWidth, labelHeight);
}

void ScopyBio_Controller::processResultsOnEverything()
{
    m_dataModel->processResults(m_pileModel->getImages());
}

int ScopyBio_Controller::getItemAtPoint(int posX, int labelWidth)
{
    return m_dataModel->getItemAtPoint(posX, labelWidth);
}

bool ScopyBio_Controller::dataReady()
{
    return m_dataModel->dataReady();
}


//=======================
// Faisceau_Modele
//=======================

void ScopyBio_Controller::setFaisceau(QPoint pos1, QPoint pos2)
{
    m_faisceauModel->setFaisceau(pos1, pos2);
}
