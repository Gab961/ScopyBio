#pragma once
#include <string>
#include <vector>
#include "resultat.h"

#define cimg_use_tiff
#include "CImg.h"

class dessin_model;
class QPoint;
class gestionnaire_calque_model;
using namespace cimg_library;

class analyse_model
{
public:
    analyse_model();

    void init();

    /**
     * @brief getResultDisplayPath Renvoie le chemin de l'image contenant les résultats
     * @return
     */
    std::string getResultDisplayPath() const;

    /**
     * @brief getResults
     * @return
     */
    std::vector<Resultat> getResults() const;

    /**
     * @brief analyse_model::calculPertinence
     * @param data
     * @return
     */
    int calculPertinence(std::vector<float> data, int whiteValue);

    /**
     * @brief processResultsWithCrops Calcul les résultats depuis la fenêtre de sélection
     * @param allPictures
     * @param pos1
     * @param pos2
     * @param whiteValue
     * @param labelWidth
     * @param labelHeight
     */
    void processResultsWithCrops(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, int labelWidth, int labelHeight);

    //TODO
    void processResultsWithCropsVERSIONDEUX(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, int labelWidth, int labelHeight, gestionnaire_calque_model * gestionnaire);

    /**
     * @brief processResults Calcul les résultats dans toute la fenêtre partie par partie
     * @param allPictures
     * @param labelWidth
     * @param labelHeight
     */
    void processResults(CImgList<float> allPictures, int whiteValue, gestionnaire_calque_model * gestionnaire);

    /**
     * @brief processLocalResults
     * @param allPictures
     * @param pos1
     * @param pos2
     * @param whiteValue
     * @return
     */
    int processLocalResults(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue);

    /**
     * @brief createCropResultsDisplay
     * @param result
     * @param imagesSize
     * @param whiteValue
     */
    void createCropResultsDisplay(Resultat result, unsigned int imagesSize, int whiteValue);

    /**
     * @brief createResultsDisplay
     * @param index
     * @param imagesSize
     * @param whiteValue
     */
    void createResultsDisplay(int index, int imagesSize, int whiteValue);

    /**
     * @brief calculPlacementY Calcul le placement d'un point précis pour le positionner correctement sur le graph de données
     * @param imageHeight
     * @param y
     * @param valeurMediane
     * @param hauteurAbscisse
     * @return
     */
    int calculPlacementY(int imageHeight, int y, int valeurMediane, int hauteurAbscisse);

    /**
     * @brief getItemAtPoint Calcul et renvoie l'image correspondante à un point donné du graph
     * @param imagesAmount
     * @param posX
     * @param labelWidth
     * @return
     */
    int getItemAtPoint(int imagesAmount, int posX, int labelWidth);

    /**
     * @brief analyseForWhiteValue
     * @return
     */
    int analyseForWhiteValue();

    /**
     * @brief dataReady Renvoie vrai si une image existe dans la fenêtre de données
     * @return
     */
    bool dataReady();

    /**
     * @brief setColumnAmount
     * @param newColumn
     */
    void setColumnAmount(int newColumn);

    /**
     * @brief getColumnAmount
     * @return
     */
    int getColumnAmount();

    /**
     * @brief setLinesAmount
     * @param newLine
     */
    void setLinesAmount(int newLine);

    /**
     * @brief getLinesAmount
     * @return
     */
    int getLinesAmount();

    /**
     * @brief getDataFromArea Lors d'un clic sur une zone de l'image, affiche le graphe data et le zoom associés
     * @param area
     * @param labelWidth
     * @param labelHeight
     */
    void getDataFromArea(QPoint area, int labelWidth, int labelHeight, int imageWidth, int imageHeight, CImg<float> currentImage, dessin_model *dessin);

    /**
     * @brief getTopLeftPointOfCurrentArea
     * @return
     */
    QPoint getTopLeftPointOfCurrentArea() { return results[currentArea].getTopLeftPoint(); }

    /**
     * @brief getBottomRightPointOfCurrentArea
     * @return
     */
    QPoint getBottomRightPointOfCurrentArea() { return results[currentArea].getBottomRightPoint(); }

    /**
     * @brief getAreaIsSelected
     * @return
     */
    bool getAreaIsSelected();

    /**
     * @brief setAreaIsSelected
     * @param newValue
     */
    void setAreaIsSelected(bool newValue);

    /**
     * @brief getUserAreaIsSelected
     * @return
     */
    bool getUserAreaIsSelected();

    /**
     * @brief setUserAreaIsSelected
     * @param newValue
     */
    void setUserAreaIsSelected(bool newValue);

    void setResults(const std::vector<Resultat> &value);

private:
    bool areaIsSelected;
    bool userAreaIsSelected;
    bool isDataReady;
    int columnAmount;
    int linesAmount;
    int currentArea;
    int errorMargin;

    std::string pathOfResultsStorage = "tmp/saveAnalyse/resultDisplay";
    std::string pathOfResultsDisplay = "tmp/resultDisplay.tmp";
    std::vector<Resultat> results;
};

