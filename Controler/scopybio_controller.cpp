#include <QPoint>
#include <iostream>
#include <string>
#include <vector>

#include "scopybio_controller.h"


ScopyBio_Controller::ScopyBio_Controller() : m_pileModel(new pile_model()), m_dessinModel(new dessin_model()), m_analyseModel(new analyse_model()), m_gestion_calque(new gestionnaire_calque_model), m_faisceauModel(new faisceau_model), m_saveModel(new save_model), m_loadModel(new load_model)
{}


//=======================
// AFFICHAGE
//=======================

void ScopyBio_Controller::DisplayResultImage(int idImage){
    //Pour permettre un chargement plus efficace des affichages
    m_dessinModel->switchSaveLocation();
    m_gestion_calque->mergeCalques(m_gestion_calque->getListOfCalqueFromImage(idImage), m_pileModel->getCurrentImage(), m_dessinModel->getMainDisplayPath());
}

void ScopyBio_Controller::afficherCalque(int id, bool aff) {
    int min = m_gestion_calque->getCalqueForDisplay(id).getIntervalMin(),
            max = m_gestion_calque->getCalqueForDisplay(id).getIntervalMax();
    if(m_gestion_calque->existeCalque(min, max)){
        m_gestion_calque->calqueShowable(min,max,aff);
    }
}

//=======================
// Save_Model
//=======================

void ScopyBio_Controller::save_as(std::string path){
    m_saveModel->save_as(path,m_pileModel->getFileName(),m_gestion_calque->getAllCalques(), m_analyseModel->getResults(),m_analyseModel->getLinesAmount(),m_analyseModel->getColumnAmount());
}

bool ScopyBio_Controller::save(){
    return m_saveModel->save(m_gestion_calque->getAllCalques(), m_analyseModel->getResults(),m_analyseModel->getLinesAmount(),m_analyseModel->getColumnAmount());
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

    //Resultat
    m_analyseModel->init();
    std::vector<Resultat> res;
    res = m_loadModel->loadResults(pathProject);

    m_analyseModel->setResults(res);

    std::vector<int> rowcol = m_loadModel->loadColRowAmounts(pathProject);
    if(rowcol.empty()){
        m_analyseModel->setLinesAmount(0);
        m_analyseModel->setColumnAmount(0);
    }else{
        m_analyseModel->setLinesAmount(rowcol.front());
        m_analyseModel->setColumnAmount(rowcol.back());
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
    std::cout << "Control id = " << id << std::endl;
    int min = m_gestion_calque->getCalqueForDisplay(id).getIntervalMin(), max=m_gestion_calque->getCalqueForDisplay(id).getIntervalMax();

    std::cout << "min = " << min << " max = " << max << std::endl;
    m_gestion_calque->removeCalques(min, max);
    m_gestion_calque->removeFromDict(min,max,id);
}

void ScopyBio_Controller::setCurrentCalqueId(int newId){
    m_gestion_calque->setCurrentCalqueId(newId);
}

void ScopyBio_Controller::setCurrentCalqueIdMinMax(int min, int max){
    int currentId = m_gestion_calque->getCalqueForDisplay(min,max).getId();

    m_gestion_calque->setCurrentCalqueId(currentId);
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
    m_gestion_calque->dessineFaisceau(min,max,m_faisceauModel->getTopLeft(),m_faisceauModel->getBotRight(), labelWidth, labelHeight);

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
 * @param isDrawing
 */
void ScopyBio_Controller::dessinerLignePerso(int imageIndex, QPoint origPoint, QPoint pos, int labelWidth, int labelHeight, bool isDrawing)
{
    int min = imageIndex, max = imageIndex;
    int taille = m_pileModel->getImages().size();

    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(),min,max,taille);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    if (isDrawing)
        m_gestion_calque->dessinLigne(min, max, origPoint, pos, m_dessinModel->getPenSize(), labelWidth, labelHeight, isDrawing);
    else
        m_gestion_calque->dessinLigne(min, max, origPoint, pos, m_dessinModel->getEraserSize(), labelWidth, labelHeight, isDrawing);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::dessinerCercle(int imageIndex, QPoint origPoint, int labelWidth, int labelHeight)
{
    int min = imageIndex, max = imageIndex;
    int taille = m_pileModel->getImages().size();

    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(),min,max,taille);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessinCercle(min, max, origPoint, m_dessinModel->getShapeSize(), labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::dessinerCarre(int imageIndex, QPoint origPoint, int labelWidth, int labelHeight)
{
    int min = imageIndex, max = imageIndex;
    int taille = m_pileModel->getImages().size();

    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(),min,max,taille);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessinCarre(min, max, origPoint, m_dessinModel->getShapeSize(), labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
}

void ScopyBio_Controller::dessinerText(int imageIndex, std::string text, QPoint origPoint, int labelWidth, int labelHeight)
{
    int min = imageIndex, max = imageIndex;
    int taille = m_pileModel->getImages().size();

    //Verifier s'il existe dans le dico
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        m_gestion_calque->creerCalque(m_pileModel->getCurrentImage().width(), m_pileModel->getCurrentImage().height(),min,max,taille);
    }

    //On est sur que le calque existe, on dessine le rectangle.
    m_gestion_calque->dessinText(min, max, origPoint, text, m_dessinModel->getTextSize(), labelWidth, labelHeight);

    DisplayResultImage(m_pileModel->getCurrentImageIndex());
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
    //m_gestion_calque->afficheCalques();
    // -3 = filtre vert
    // Normalement le calque vert est déjà créé, cette fonction met juste à jour le dictionnaire de calque. il doit y avoir une fonction qui met à jour la view.
    // /!\ Bug parce que le remove est fait dans une autre fonction
    int min = -3, max = -3;
    int taille = m_pileModel->getImages().size();
    if(!m_gestion_calque->existeCalque(min,max)){
        //Si n'existe pas Creer le calque et mettre à jour le dico
        std::cout << "Calque vert n'existe pas" << std::endl;
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
// Aalyse_Modele
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
