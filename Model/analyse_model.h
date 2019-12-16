#pragma once
#include <string>
#include <vector>

#define cimg_use_tiff
#include "CImg.h"

class QPoint;
class gestionnaire_calque_model;
using namespace cimg_library;

class analyse_model
{
public:
    analyse_model();

    /**
     * @brief getResultDisplayPath Renvoie le chemin de l'image contenant les résultats
     * @return
     */
    std::string getResultDisplayPath() const;

    /**
     * @brief getResults
     * @return
     */
    std::vector<std::vector<float>> getResults() const;

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
     * @brief createResultsDisplay Créé l'image correspondant aux résultats calculés
     * @param whiteValue
     */
    void createResultsDisplay(int index, int whiteValue);

    /************************************/

    void createResultsDisplayDEBUG(int index, int imagesSize, int whiteValue);

    /***********************************/
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
     * @param posX
     * @param labelWidth
     * @return
     */
    int getItemAtPoint(int posX, int labelWidth);

    /**
     * @brief dataReady Renvoie vrai si une image existe dans la fenêtre de données
     * @return
     */
    bool dataReady();

private:
    bool isDataReady;


    std::string pathOfResultsDisplayDEBUG = "tmp/DEBUG/resultDisplay";

    std::string pathOfResultsDisplay = "tmp/resultDisplay.bmp";
    std::vector<std::vector<float>> results;

    int columnAmount = 30;
    int linesAmount = 30;
};

