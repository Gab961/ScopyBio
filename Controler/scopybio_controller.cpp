#include <QPoint>
#include <iostream>
#include <string>

#include "scopybio_controller.h"


ScopyBio_Controller::ScopyBio_Controller() : m_pileModel(new pile_model()), m_dessinModel(new dessin_model()), m_dataModel(new data_model()), m_gestion_calque(new gestionnaire_calque_model), m_faisceauModel(new faisceau_model), m_saveModel(new save_model)
{}


//=======================
// AFFICHAGE
//=======================

void ScopyBio_Controller::DisplayResultImage(int idImage){
    //Pour permettre un chargement plus efficace des affichages
    m_dessinModel->switchSaveLocation();
    m_gestion_calque->mergeCalques(m_gestion_calque->getListOfCalqueFromImage(idImage), m_pileModel->getCurrentImage(), m_dessinModel->getMainDisplayPath());

}

void ScopyBio_Controller::save_as(std::string path){
    path = "/home/etudiant/Bureau/cc";
    std::cout << path << std::endl;
    m_saveModel->save_as(path,m_pileModel->getFileName(),m_gestion_calque->getAllCalques());
}

bool ScopyBio_Controller::save(){
    if(m_saveModel->getCanSave()){
        m_saveModel->save(m_gestion_calque->getAllCalques());
        return true;
    }else{
        return false;
    }
}

//=======================
// Pile_Modele
//=======================
void ScopyBio_Controller::loadNewTiffFile(std::string filename)
{
    if (filename.length()>0)
    {
        m_pileModel->loadNewFilename(filename);
        m_gestion_calque->initGlobalCalques(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height());
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
    m_pileModel->setCurrentImageIndex(indiceEnCours);
}


int ScopyBio_Controller::getCurrentImageIndex()
{
    return m_pileModel->getCurrentImageIndex();
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
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(), min,max,taille);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessineFaisceau(min,max,m_faisceauModel->getTopLeft(),m_faisceauModel->getBotRight(),labelWidth,labelHeight);

    saveZoom(labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());

}

/**
 * @brief ScopyBio_Controller::dessinerLignePerso
 * @param imageIndex
 * @param origPoint
 * @param pos
 * @param labelWidth
 * @param labelHeight
 */
void ScopyBio_Controller::dessinerLignePerso(int imageIndex, QPoint origPoint, QPoint pos, int labelWidth, int labelHeight)
{
    int min = imageIndex, max = imageIndex;
    int taille = m_pileModel->getImages().size();

    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(),min,max,taille);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessinLigne(min, max, origPoint, pos, labelWidth, labelHeight);


    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::saveZoom(int labelWidth, int labelHeight)
{
    //Necessaire pour afficher le zoom.
    m_dessinModel->saveZoomFromPicture(m_faisceauModel->getTopLeft(), m_faisceauModel->getBotRight(), labelWidth, labelHeight, m_pileModel->getCurrentImage());

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
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(),min,max,taille);
    }

    m_gestion_calque->updateCalqueVert(min,max,taille);
    //      gestion_calque.afficheDic();

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

/* fonction de mise à jour de la vue
 *
 * La fonction reçoit le numéro de l'image.
 * appelle une fonction dans le gestionnaire qui retourne la liste de calque s'appliquant à l'image genre vector : { 0,2,6 } c'est à dire que les images calques calque0, calque2 et calque6 doivent etre affichés
 *
 * */

void ScopyBio_Controller::applyHistogramFilter()
{
    m_gestion_calque->updateHistogram(-4,-4,m_pileModel->getImages().size());
    DisplayResultImage(m_pileModel->getCurrentImageIndex());
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
