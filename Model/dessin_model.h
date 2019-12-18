#pragma once
#include <string>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;
class QPoint;

class dessin_model
{
public:
    dessin_model();

    /**
     * @brief getMainDisplayPath Renvoie le chemin de l'image s'affichant dans le display principal
     * @return
     */
    std::string getMainDisplayPath() const;

    /**
     * @brief getZoomDisplayPath Renvoie le chemin de l'image s'affichant dans le display principal
     * @return
     */
    std::string getZoomDisplayPath() const;

    /**
     * @brief dessinerRectangle Dessine un rectangle sur une image en paramètre (calque)
     * @param pos1
     * @param pos2
     * @param labelWidth
     * @param labelHeight
     * @param currentPicture
     * @return
     */
    CImg<float> dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> &currentPicture);

    /**
     * @brief dessinerRond
     * @param pos1
     * @param labelWidth
     * @param labelHeight
     * @param currentPicture
     * @return
     */
    CImg<float> dessinerRond(QPoint pos1, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief dessinerRectanglePertinence
     * @param pos1
     * @param pos2
     * @param pertinence
     * @param currentPicture
     * @return
     */
    CImg<float> dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence, CImg<float> & currentPicture);

    /**
     * @brief dessinerRond
     * @param pos1
     * @param labelWidth
     * @param labelHeight
     * @param currentPicture
     * @return
     */
    CImg<float> dessinerRond(QPoint pos1, int pertinence, CImg<float> & currentPicture);

    /**
     * @brief dessinerLigne
     * @param pos1
     * @param pos2
     * @param labelWidth
     * @param labelHeight
     * @param currentPicture
     * @return
     */
    CImg<float> dessinerLigne(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief applyQuadrillageFilter
     * @param picture
     * @return
     */
    CImg<float> applyQuadrillageFilter(int columns, int lines, CImg<float> picture);

    /**
     * @brief saveZoomFromPicture Enregistre la partie sélectionnée de l'image dans l'image zoomée
     * @param pos1
     * @param pos2
     * @param labelWidth
     * @param labelHeight
     * @param currentPicture
     */
    void saveZoomFromPicture(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> currentPicture);

    /**
     * @brief saveZoomFromArea
     * @param pos1
     * @param pos2
     * @param currentPicture
     */
    void saveZoomFromArea(QPoint pos1, QPoint pos2, CImg<float> currentPicture);

    /**
     * @brief savePics Je sais pas
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @param color
     * @param currentPicture
     */
    void savePics(int x1, int y1, int x2, int y2, unsigned char color, CImg<float> currentPicture);

    /**
     * @brief saveImageAsMainDisplay Enregistre l'image en paramètre en tant que main display
     * @param pictureToShow
     */
    void saveImageAsMainDisplay(CImg<float> pictureToShow);

    //Filtres
        //Filtre vert
    CImg<float> applyGreenFilter(CImg<float> picture);
        //Filtre contraste
    CImg<float> applyHistogramFilter(CImg<float> picture);

    /**
     * @brief manageNewWhiteColor Calcul la position du clic et extrait la couleur du pixel
     * @param pos
     * @param labelWidth
     * @param labelHeight
     * @param zoomView
     */
    void manageNewWhiteColor(QPoint pos, int labelWidth, int labelHeight, bool zoomView);

    /**
     * @brief manageNewWhiteColor Met une nouvelle couleur de blanc
     * @param newWhite
     */
    void manageNewWhiteColor(int newWhite);

    int getWhiteValue() const;
    void setWhiteValue(int color);

    //Vrai si on attend un clic
    bool getListenPipetteClick() const;
    void setListenPipetteClick(bool pipetteClick);

    /**
     * @brief getZoomReady Vrai si il existe une image dans le zoom display
     * @return
     */
    bool getZoomReady() const;

    /**
     * @brief getBaseColorGiven Vrai si une couleur de base a déjà été donnée
     * @return
     */
    bool getBaseColorGiven() const;
    void setBaseColorGiven();

    void switchSaveLocation();

private:
    int pathOfMainDisplayIndex = 0;
    std::string pathOfMainDisplay = "tmp/mainDisplay/mainDisplay0.bmp";
    std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";

    bool zoomReady;

    bool baseColorGiven;
    bool listenPipetteClick;
    int whiteColor;
};
