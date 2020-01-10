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
     * @brief processLocalResults Process results for a specific area (one bloc of a full analysis)
     * @param allPictures List of all pictures
     * @param pos1 Top left point of the local area
     * @param pos2 Bottom right point of the local area
     * @param whiteValue Minimum value used for the analysis
     * @return
     */
    int processLocalResults(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue);

    /**
     * @brief processLocalUserResults Process results for a specific area (one bloc of a user analysis)
     * @param allPictures List of all pictures
     * @param pos1 Top left point of the local area
     * @param pos2 Bottom right point of the local area
     * @param whiteValue Minimum value used for the analysis
     * @param pos1Scaled Scaled point depending of the size of the label
     * @param pos2Scaled Scaled point depending of the size of the label
     * @return
     */
    int processLocalUserResults(CImgList<float> allPictures, QPoint pos1, QPoint pos2, int whiteValue, QPoint pos1Scaled, QPoint pos2Scaled);

    /**
     * @brief createResultsDisplay Create the result display picture of a result given in index
     * @param index Index of the result to display
     * @param imagesSize Amount of images in the list
     * @param whiteValue Minimum value used for the analysis
     */
    void createResultsDisplay(int index, int imagesSize, int whiteValue, bool isUserAnalysis);

    /**
     * @brief createAllResultsDisplay Create the results displays pictures for all results
     */
    void createAllResultsDisplay(int size, int whiteValue);

    /**
     * @brief calculPlacementY Calculate the placement of a point in the Y axis to be place correctly on the graph
     * @param imageHeight Height of the graph image
     * @param y Y axis of the point
     * @param valeurMediane Value of the abcisse axis
     * @param hauteurAbscisse Y axis scaled
     * @return
     */
    int calculPlacementY(int imageHeight, int y, int valeurMediane, int hauteurAbscisse);

    /**
     * @brief getItemAtPoint Return the image index corresponding to the point clicked on the graph display
     * @param imagesAmount Amount of images in the list
     * @param posX Position of the clic on the result display
     * @param labelWidth Width of the label of result display
     * @return
     */
    int getItemAtPoint(int imagesAmount, int posX, int labelWidth);

    /**
     * @brief analyseForWhiteValue Make a quick analysis to get a first white value to set
     * @return
     */
    int analyseForWhiteValue(CImg<float> middleImage);

    /**
     * @brief dataReady Return true if some data is available to be shown in the data display
     * @return
     */
    bool dataReady();

    /**
     * @brief setColumnAmount Set the amount of columns for the analysis
     * @param newColumn New columns value
     */
    void setColumnAmount(int newColumn);

    /**
     * @brief getColumnAmount Get the amount of columns for the analysis from the model
     * @return
     */
    int getColumnAmount();

    /**
     * @brief setLinesAmount Set the amount of lines for the analysis
     * @param newLine
     */
    void setLinesAmount(int newLine);

    /**
     * @brief getLinesAmount Get the amount of lines for the analysis from the model
     * @return
     */
    int getLinesAmount();

    /**
     * @brief getDataFromArea Show the data and the zoom from the point clicked on an area
     * @param area Position of the click
     * @param labelWidth Width of the label from which the clic come from
     * @param labelHeight Height of the label from which the clic come from
     */
    void getDataFromArea(QPoint area, int labelWidth, int labelHeight, int imageWidth, int imageHeight, CImg<float> currentImage, dessin_model *dessin);

    /**
     * @brief getDataFromZoomArea Show the data from the point clicked on an area from the zoom
     * @param area Position of the click
     * @param labelWidth labelWidth Width of the label from which the clic come from
     * @param labelHeight labelHeight Height of the label from which the clic come from
     * @param zoomPath Path of the zoom display
     */
    void getDataFromZoomArea(QPoint area, int labelWidth, int labelHeight, std::string zoomPath);

    /**
     * @brief getTopLeftPointOfCurrentArea Return the top left point of the currently selected area (from full analysis)
     * @return
     */
    QPoint getTopLeftPointOfCurrentArea() { return results[currentArea].getTopLeftPoint(); }

    /**
     * @brief getBottomRightPointOfCurrentArea Return the bottom right point of the currently selected area (from full analysis)
     * @return
     */
    QPoint getBottomRightPointOfCurrentArea() { return results[currentArea].getBottomRightPoint(); }

    /**
     * @brief getAreaIsSelected Return true if an area from full analysis is selected
     * @return
     */
    bool getAreaIsSelected();

    /**
     * @brief setAreaIsSelected Set if an area from full analysis is selected
     * @param newValue New value of selection
     */
    void setAreaIsSelected(bool newValue);

    /**
     * @brief getUserAreaIsSelected Return true if an area from user analysis is selected
     * @return
     */
    bool getUserAreaIsSelected();

    /**
     * @brief setUserAreaIsSelected Set if an area from user analysis is selected
     * @param newValue New value of selection
     */
    void setUserAreaIsSelected(bool newValue);

    void setResults(const std::vector<Resultat> &value);

    /**
     * @brief setCurrentAnalysisType Set the type of the current analysis
     * @param type True if user analysis, false otherwise
     */
    void setCurrentAnalysisType(bool type);

    /**
     * @brief getCurrentAnalysisType Return the type of the current analysis
     * @return
     */
    bool getCurrentAnalysisType();

    /**
     * @brief setErrorMargin Set a value to the error margin
     * @param newValue New error margin value
     */
    void setErrorMargin(int newValue);

    /**
     * @brief getErrorMargin Return the error margin
     * @return
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

    std::string pathOfResultsStorage;
    std::string pathOfResultsDisplay;
    std::vector<Resultat> results;
    std::vector<Resultat> userResults;
};

