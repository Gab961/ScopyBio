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
     * @brief getResultDisplayPath Get the display path for results
     * @return
     */
    std::string getResultDisplayPath() const;

    /**
     * @brief getResults Get the list of results from the full analysis
     * @return
     */
    std::vector<Resultat> getResults() const;

    /**
     * @brief calculPertinence Calculate the pertinence from a set of greyscale values and a minium white value
     *        All greyscale data under the whitevalue are not used
     * @param data Set of number corresponding to the greyscale values of each image in an area
     * @param whiteValue Minimum value, each data value under it is not used
     * @return
     */
    int calculPertinence(std::vector<float> data, int whiteValue);

    //TODO SUPPRIMER CELLE CI ET RENOMMER LA VERSION DEUX
    void processResultsWithCrops(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, int labelWidth, int labelHeight);

    /**
     * @brief processResultsWithCrops Process an analysis on a specific area
     * @param allPictures List of all pictures
     * @param pos1 Top left point of the area
     * @param pos2 Bottom right point of the area
     * @param whiteValue Minimum value used for the analysis
     * @param labelWidth Width of the label from which the area has been taken
     * @param labelHeight Height of the label from which the area has been taken
     * @param gestionnaire Manager of layers
     */
    void processResultsWithCropsVERSIONDEUX(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, int labelWidth, int labelHeight, gestionnaire_calque_model * gestionnaire);

    /**
     * @brief processResults Process an analysis on all the area
     * @param allPictures List of all pictures
     * @param whiteValue Minimum value used for the analysis
     * @param gestionnaire Manager of layers
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
     * @brief processLocalUserResults
     * @param allPictures
     * @param pos1
     * @param pos2
     * @param whiteValue
     * @param pos1Scaled
     * @param pos2Scaled
     * @return
     */
    int processLocalUserResults(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, QPoint pos1Scaled, QPoint pos2Scaled);

    /**
     * @brief createResultsDisplay
     * @param index
     * @param imagesSize
     * @param whiteValue
     */
    void createResultsDisplay(int index, int imagesSize, int whiteValue, bool isUserAnalysis);

    /**
     * @brief createAllResultsDisplay
     */
    void createAllResultsDisplay(int size, int whiteValue);

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
    int analyseForWhiteValue(CImg<float> middleImage);

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
     * @brief getDataFromZoomArea
     * @param area
     * @param labelWidth
     * @param labelHeight
     * @param zoomPath
     */
    void getDataFromZoomArea(QPoint area, int labelWidth, int labelHeight, std::string zoomPath);

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

    /**
     * @brief setCurrentAnalysisType
     * @param type
     */
    void setCurrentAnalysisType(bool type);

    /**
     * @brief getCurrentAnalysisType
     * @return
     */
    bool getCurrentAnalysisType();

    /**
     * @brief setErrorMargin
     * @param newValue
     */
    void setErrorMargin(int newValue);

    /**
     * @brief getErrorMargin
     */
    int getErrorMargin();

private:
    bool areaIsSelected;
    bool userAreaIsSelected;
    bool isDataReady;
    bool currentAnalysisIsAUserOne;
    int columnAmount;
    int linesAmount;
    int currentArea;
    int errorMargin;

    std::string pathOfResultsStorage = "tmp/saveAnalyse/resultDisplay";
    std::string pathOfResultsDisplay = "tmp/resultDisplay.tmp";
    std::vector<Resultat> results;
    std::vector<Resultat> userResults;
};

