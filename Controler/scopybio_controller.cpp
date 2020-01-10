#include <QPoint>
#include <iostream>
#include <string>
#include <vector>

#include "scopybio_controller.h"


ScopyBio_Controller::ScopyBio_Controller() : m_pileModel(new pile_model()), m_dessinModel(new dessin_model()), m_analyseModel(new analyse_model()), m_gestion_calque(new gestionnaire_calque_model), m_faisceauModel(new faisceau_model), m_saveModel(new save_model), m_loadModel(new load_model)
{}

void ScopyBio_Controller::reinitAllModels()
{
    m_analyseModel->init();
    m_gestion_calque->init(m_pileModel->getCurrentImage().width(),m_pileModel->getCurrentImage().height());
}

//=======================
// AFFICHAGE
//=======================

void ScopyBio_Controller::DisplayResultImage(int idImage){
    //Pour permettre un chargement plus efficace des affichages
    m_dessinModel->switchSaveLocation();
    m_gestion_calque->mergeCalques(m_gestion_calque->getListOfCalqueFromImage(idImage), m_pileModel->getCurrentImage(), m_dessinModel->getMainDisplayPath());
}

void ScopyBio_Controller::afficherCalque(int id, bool aff) {
    if(m_gestion_calque->existeCalque(id)){
        m_gestion_calque->calqueShowable(id,aff);
    }
}

//=======================
// Save_Model
//=======================

void ScopyBio_Controller::save_as(std::string path){
    m_saveModel->save_as(path,m_pileModel->getFileName(),m_gestion_calque->getAllCalques(),
                         m_analyseModel->dataReady(),m_analyseModel->getResults(),m_analyseModel->getLinesAmount(),m_analyseModel->getColumnAmount(),
                         m_gestion_calque->getCalqueForDisplay(RESULTAT_VIEW), m_dessinModel->getWhiteValue());
}

bool ScopyBio_Controller::save(){
    return m_saveModel->save(m_gestion_calque->getAllCalques(),
                             m_analyseModel->dataReady(),m_analyseModel->getResults(),m_analyseModel->getLinesAmount(),m_analyseModel->getColumnAmount(),
                             m_gestion_calque->getCalqueForDisplay(RESULTAT_VIEW), m_dessinModel->getWhiteValue());
}

void ScopyBio_Controller::saveCurrentDisplay(std::string path)
{
    m_saveModel->saveCurrentDisplay(path,m_dessinModel->getMainDisplayPath());
}


void ScopyBio_Controller::changeSavePaths(std::string newSavePath)
{
    m_saveModel->changeSavePaths(newSavePath);
}

//=======================
// Pile_Modele
//=======================
void ScopyBio_Controller::openProject(std::string pathProject){
    //Calques !
    m_gestion_calque->init(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height());
    std::vector<calque> calques;

    calques = m_loadModel->loadCalques(pathProject);

    m_gestion_calque->addCalques(calques,m_pileModel->getImages().size());

    m_dessinModel->setWhiteValue(m_loadModel->loadWhiteValue(pathProject));

    //Resultat
    m_analyseModel->init();
    std::vector<Resultat> res;
    res = m_loadModel->loadResults(pathProject);

    std::cout << "TAILLE RES = " << res.size() << std::endl;

    if(res.size() != 0){
        m_analyseModel->setResults(res);
        m_analyseModel->createAllResultsDisplay(m_pileModel->getImages().size(),m_dessinModel->getWhiteValue());

        std::vector<int> rowcol = m_loadModel->loadColRowAmounts(pathProject);
        if(rowcol.empty()){
            m_analyseModel->setLinesAmount(0);
            m_analyseModel->setColumnAmount(0);
        }else{
            m_analyseModel->setLinesAmount(rowcol.front());
            m_analyseModel->setColumnAmount(rowcol.back());
        }

        std::string resCalque = m_loadModel->loadResultCalque(pathProject);

        if(!resCalque.empty()){
            CImg<float> resCal;
            resCal.load_cimg(resCalque.c_str());
            m_gestion_calque->addCalqueSpecial(resCal,RESULTAT_VIEW);
            m_gestion_calque->setShowResultat(true);
        }
    }

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

bool ScopyBio_Controller::is24Bits()
{
    return m_pileModel->is24Bits();
}

void ScopyBio_Controller::loadNewTiffFile(std::string filename)
{
    if (filename.length()>0)
    {
        m_pileModel->loadNewFilename(filename);
        //TODO SAUVEGARDE NOUVEAU TIFF
        std::cout << "Tiff = " << filename << std::endl;
        m_saveModel->saveInLocal(filename);

        m_gestion_calque->init(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height());

        int middleIndex = m_pileModel->getImages().size() / 2;
        m_dessinModel->manageNewWhiteColor(m_analyseModel->analyseForWhiteValue(m_pileModel->getImageAtIndex(middleIndex)));
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
// Calque
//=======================

void ScopyBio_Controller::removeCalque(int id){
    int min = m_gestion_calque->getCalqueForDisplay(id).getIntervalMin(),
            max = m_gestion_calque->getCalqueForDisplay(id).getIntervalMax();
    std::cout << "Control id = " << id << std::endl;
    m_gestion_calque->removeCalques(id);
    m_gestion_calque->removeFromDict(min,max,id);
}

void ScopyBio_Controller::setCurrentCalqueId(int newId){
    m_gestion_calque->setCurrentCalqueId(newId);
}


std::vector<int> ScopyBio_Controller::getCalquesIdFromImage(int image) {
    return m_gestion_calque->getListOfCalqueFromImage(image);
}


bool ScopyBio_Controller::isHidden(int id) {
    return !m_gestion_calque->getCalqueForDisplay(id).getCanShow();
}

void ScopyBio_Controller::undoAction(){
    //Verifier s'il existe dans le dico
    if(m_gestion_calque->existeCalque(m_gestion_calque->getCurrentCalqueId())){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->undo();
    }

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::redoAction(){
    //Verifier s'il existe dans le dico
    if(m_gestion_calque->existeCalque(m_gestion_calque->getCurrentCalqueId())){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->redo();
    }
}


void ScopyBio_Controller::addMemento()
{
    m_gestion_calque->addMemento();
}

bool ScopyBio_Controller::CreerNouveauCalque(int min, int max){
    int taille = m_pileModel->getImages().size();

    if(min > max){
        int tmp = min;
        min = max;
        max = tmp;
    }


    if(min < 0 || max < 0 || min >= taille || max >= taille){
        return false;
    } else {
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(),min,max,taille);

        return true;
    }
    return false;
}

//=======================
// Dessin_Modele
//=======================

/**
 * @brief ScopyBio_Controller::dessinerFaisceau dessine un rectangle dans un calque et le créer si besoin.
 * @param labelWidth largeur de la fenetre
 * @param labelHeight longueur de la fenetre
 */
void ScopyBio_Controller::dessinerFaisceau(int labelWidth, int labelHeight)
{
    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(FAISCEAU)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalqueSpecial(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(), FAISCEAU,FAISCEAU,FAISCEAU);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessineFaisceau(m_faisceauModel->getTopLeft(),m_faisceauModel->getBotRight(), labelWidth, labelHeight);

    saveZoom(labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

/**
 * @brief ScopyBio_Controller::dessinerLignePerso
 * @param origPoint
 * @param pos
 * @param labelWidth
 * @param labelHeight
 * @param isDrawing
 */
bool ScopyBio_Controller::dessinerLignePerso(QPoint origPoint, QPoint pos, int labelWidth, int labelHeight, bool isDrawing)
{
    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(m_gestion_calque->getCurrentCalqueId())){
        return false;
    }

    //On est sur que le calque existe, on dessine le rectangle.
    if (isDrawing)
        m_gestion_calque->dessinLigne(origPoint, pos, m_dessinModel->getPenSize(), labelWidth, labelHeight, isDrawing);
    else
        m_gestion_calque->dessinLigne(origPoint, pos, m_dessinModel->getEraserSize(), labelWidth, labelHeight, isDrawing);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());

    return true;
}

bool ScopyBio_Controller::dessinerCercle(QPoint origPoint, int labelWidth, int labelHeight)
{
    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(m_gestion_calque->getCurrentCalqueId())){
        return false;
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessinCercle(origPoint, m_dessinModel->getShapeSize(), labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());

    return true;
}

bool ScopyBio_Controller::dessinerCarre(QPoint origPoint, int labelWidth, int labelHeight)
{
    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(m_gestion_calque->getCurrentCalqueId())){
        return false;
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessinCarre(origPoint, m_dessinModel->getShapeSize(), labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());

    return true;
}

bool ScopyBio_Controller::dessinerText(std::string text, QPoint origPoint, int labelWidth, int labelHeight)
{
    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(m_gestion_calque->getCurrentCalqueId())){
        return false;
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessinText(origPoint, text, m_dessinModel->getTextSize(), labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());

    return true;
}

void ScopyBio_Controller::saveZoom(int labelWidth, int labelHeight)
{
    //Necessaire pour afficher le zoom.
    m_dessinModel->saveZoomFromPicture(m_faisceauModel->getTopLeft(), m_faisceauModel->getBotRight(), labelWidth, labelHeight, m_pileModel->getCurrentImage());
}

void ScopyBio_Controller::saveZoomOfCurrentArea()
{
    if (m_analyseModel->dataReady())
    {
        CImg<float> zoom = m_dessinModel->saveZoomFromArea(m_analyseModel->getTopLeftPointOfCurrentArea(),m_analyseModel->getBottomRightPointOfCurrentArea(),m_pileModel->getCurrentImage());
        m_gestion_calque->mergeUserAnalysis(zoom,m_dessinModel->getZoomDisplayPath());
    }
}

void ScopyBio_Controller::saveZoomOfUserArea()
{
    CImg<float> zoom = m_dessinModel->saveZoomFromArea(m_faisceauModel->getScaledTopLeft(),m_faisceauModel->getScaledBotRight(),m_pileModel->getCurrentImage());
    m_gestion_calque->mergeUserAnalysis(zoom,m_dessinModel->getZoomDisplayPath());
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
    m_gestion_calque->updateCalqueVert();
    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

/* fonction de mise à jour de la vue
 *
 * La fonction reçoit le numéro de l'image.
 * appelle une fonction dans le gestionnaire qui retourne la liste de calque s'appliquant à l'image genre vector : { 0,2,6 } c'est à dire que les images calques calque0, calque2 et calque6 doivent etre affichés
 *
 * */

void ScopyBio_Controller::reinitUserPertinenceCalque(int width, int height)
{
    m_gestion_calque->reinitUserPertinenceCalque(width, height);
}

void ScopyBio_Controller::applyHistogramFilter()
{
    m_gestion_calque->updateHistogram();
    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::applyResultatFilter()
{
    m_gestion_calque->updateResultat();
    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::applyZoomResultatFilter() {
    if (m_analyseModel->dataReady())
    {
        CImg<float> zoom;
        if (userAreaIsSelected())
            zoom = m_dessinModel->saveZoomFromArea(m_faisceauModel->getScaledTopLeft(),m_faisceauModel->getScaledBotRight(),m_pileModel->getCurrentImage());
        else
            zoom = m_dessinModel->saveZoomFromArea(m_analyseModel->getTopLeftPointOfCurrentArea(),m_analyseModel->getBottomRightPointOfCurrentArea(),m_pileModel->getCurrentImage());
        m_gestion_calque->updateZoomResultat();
        m_gestion_calque->mergeUserAnalysis(zoom,m_dessinModel->getZoomDisplayPath());
    }
}

void ScopyBio_Controller::manageNewWhite(QPoint pos, int labelWidth, int labelHeight, bool isZoomView)
{
    m_dessinModel->manageNewWhiteColor(pos, labelWidth, labelHeight, isZoomView, m_pileModel->getCurrentImage());
}

int ScopyBio_Controller::getWhiteColor()
{
    return m_dessinModel->getWhiteValue();
}

void ScopyBio_Controller::setWhiteColor(int value) {
    m_dessinModel->setWhiteValue(value);
}

void ScopyBio_Controller::setPipetteClick(bool pipetteClick)
{
    m_dessinModel->setListenPipetteClick(pipetteClick);
}

bool ScopyBio_Controller::getPipetteClick()
{
    return m_dessinModel->getListenPipetteClick();
}

bool ScopyBio_Controller::getListenSelectionClick() const { return m_dessinModel->getListenSelectionClick(); }
void ScopyBio_Controller::setListenSelectionClick(bool newValue) { m_dessinModel->setListenSelectionClick(newValue); }
bool ScopyBio_Controller::getListenPenClick() const { return m_dessinModel->getListenPenClick(); }
void ScopyBio_Controller::setListenPenClick(bool newValue) { m_dessinModel->setListenPenClick(newValue); }
bool ScopyBio_Controller::getListenEraserClick() const { return  m_dessinModel->getListenEraserClick(); }
void ScopyBio_Controller::setListenEraserClick(bool newValue) { m_dessinModel->setListenEraserClick(newValue); }
bool ScopyBio_Controller::getListenShapeClick() const { return  m_dessinModel->getListenShapeClick(); }
void ScopyBio_Controller::setListenShapeClick(bool newValue) { m_dessinModel->setListenShapeClick(newValue); }
bool ScopyBio_Controller::getListenTextClick() const {  return m_dessinModel->getListenTextClick(); }
void ScopyBio_Controller::setListenTextClick(bool newValue) { m_dessinModel->setListenTextClick(newValue); }

bool ScopyBio_Controller::getZoomReady()
{
    return m_dessinModel->getZoomReady();
}

bool ScopyBio_Controller::getBaseColorGiven()
{
    return m_dessinModel->getBaseColorGiven();
}

int ScopyBio_Controller::getPenSize()
{
    return m_dessinModel->getPenSize();
}

void ScopyBio_Controller::setPenSize(int newValue)
{
    m_dessinModel->setPenSize(newValue);
}
int ScopyBio_Controller::getShapeSize()
{
    return m_dessinModel->getShapeSize();
}
void ScopyBio_Controller::setShapeSize(int newValue)
{
    m_dessinModel->setShapeSize(newValue);
}
int ScopyBio_Controller::getTextSize()
{
    return m_dessinModel->getTextSize();
}
void ScopyBio_Controller::setTextSize(int newValue)
{
    m_dessinModel->setTextSize(newValue);
}
int ScopyBio_Controller::getEraserSize()
{
    return m_dessinModel->getEraserSize();
}
void ScopyBio_Controller::setEraserSize(int newValue)
{
    m_dessinModel->setEraserSize(newValue);
}

bool ScopyBio_Controller::getCircleIsSelected()
{
    return m_dessinModel->getCircleIsSelected();
}

void ScopyBio_Controller::setCircleIsSelected(bool newValue)
{
    m_dessinModel->setCircleIsSelected(newValue);
}

//=======================
// Analyse_Modele
//=======================

bool ScopyBio_Controller::areaIsSelected()
{
    return m_analyseModel->getAreaIsSelected();
}

void ScopyBio_Controller::setAreaIsSelected()
{
    m_analyseModel->setAreaIsSelected(true);
    m_analyseModel->setUserAreaIsSelected(false);
}

void ScopyBio_Controller::setAnalysisErrorMargin(int newValue)
{
    m_analyseModel->setErrorMargin(newValue);
}

int ScopyBio_Controller::getAnalysisErrorMargin()
{
    return m_analyseModel->getErrorMargin();
}

bool ScopyBio_Controller::userAreaIsSelected()
{
    return m_analyseModel->getUserAreaIsSelected();
}

void ScopyBio_Controller::setUserAreaIsSelected()
{
    m_analyseModel->setUserAreaIsSelected(true);
    m_analyseModel->setAreaIsSelected(false);
}

std::string ScopyBio_Controller::getResultDisplayPath()
{
    return m_analyseModel->getResultDisplayPath();
}

void ScopyBio_Controller::processResultsWithCrop(int labelWidth, int labelHeight)
{
    try{
        background_task = std::thread(&analyse_model::processResultsWithCropsVERSIONDEUX,m_analyseModel,m_pileModel->getImages(), m_faisceauModel->getTopLeft(), m_faisceauModel->getBotRight(), m_dessinModel->getWhiteValue(), labelWidth, labelHeight,m_gestion_calque);
        //background_task.detach();

        listener = std::thread(&ScopyBio_Controller::listenUserAnalysis,this);
        listener.detach();
    }catch(...){
        std::cout << "fini dans controleur" << std::endl;
        background_task.join();
        listener.join();
    }
}

void ScopyBio_Controller::processResults()
{
    if (m_faisceauModel->faisceauIsActive())
    {
        m_gestion_calque->reinitFaisceauCalque();
        m_faisceauModel->setFaisceauInactive();
    }

    try{
        background_task = std::thread(&analyse_model::processResults,m_analyseModel,m_pileModel->getImages(),m_dessinModel->getWhiteValue(), m_gestion_calque);
        //background_task.detach();

        listener = std::thread(&ScopyBio_Controller::listenFullAnalysis,this);
        listener.detach();
    }catch(...){
        std::cout << "fini dans controleur" << std::endl;
        background_task.join();
        listener.join();
    }
}

int ScopyBio_Controller::getItemAtPoint(int posX, int labelWidth)
{
    return m_analyseModel->getItemAtPoint(m_pileModel->getImages().size(), posX, labelWidth);
}

bool ScopyBio_Controller::dataReady()
{
    return m_analyseModel->dataReady();
}

bool ScopyBio_Controller::getAnalysisType()
{
    return m_analyseModel->getCurrentAnalysisType();
}

void ScopyBio_Controller::setAnalysisTypeIsUser(bool type)
{
    m_analyseModel->setCurrentAnalysisType(type);
}

void ScopyBio_Controller::getDataFromArea(QPoint area, int labelWidth, int labelHeight) {
    int imageWidth = m_pileModel->getCurrentImage().width();
    int imageHeight = m_pileModel->getCurrentImage().height();

    if (m_faisceauModel->faisceauIsActive())
    {
        m_gestion_calque->reinitFaisceauCalque();
        m_faisceauModel->setFaisceauInactive();
    }

    m_analyseModel->getDataFromArea(area, labelWidth, labelHeight, imageWidth, imageHeight, m_pileModel->getCurrentImage(), m_dessinModel);
    saveZoomOfCurrentArea();

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::getDataFromZoomArea(QPoint area, int labelWidth, int labelHeight) {
    if (m_faisceauModel->faisceauIsActive())
    {
        m_analyseModel->getDataFromZoomArea(area, labelWidth, labelHeight, m_dessinModel->getZoomDisplayPath());
    }
}

int ScopyBio_Controller::getLineAmount() {
    return m_analyseModel->getLinesAmount();
}

int ScopyBio_Controller::getColumnAmount() {
    return m_analyseModel->getColumnAmount();
}

void ScopyBio_Controller::setLineAmount(int value) {
    m_analyseModel->setLinesAmount(value);
}

void ScopyBio_Controller::setColumnAmount(int value) {
    m_analyseModel->setColumnAmount(value);
}


//=======================
// Faisceau_Modele
//=======================

void ScopyBio_Controller::setFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight)
{
    m_faisceauModel->setFaisceau(pos1, pos2, m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(), labelWidth, labelHeight);
}


//=======================
// THREAD
//=======================
void ScopyBio_Controller::listenFullAnalysis(){

    if(background_task.joinable()){
        background_task.join();
    }

    m_gestion_calque->setShowResultat(true);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());

    emit fullAnalysisEnded();
    std::cout << "Thread total fini" << std::endl;

}

void ScopyBio_Controller::listenUserAnalysis(){

    if(background_task.joinable()){
        background_task.join();
    }

    emit userAnalysisEnded();
    std::cout << "Thread user fini" << std::endl;

}
