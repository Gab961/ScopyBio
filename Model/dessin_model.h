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
     * @brief saveZoomFromPicture Enregistre la partie sélectionnée de l'image dans l'image zoomée
     * @param pos1
     * @param pos2
     * @param labelWidth
     * @param labelHeight
     * @param currentPicture
     */
    void saveZoomFromPicture(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> currentPicture);

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
    void removeGreenFilter(CImg<float> picture);    
        //Filtre contraste
    void applyHistogramFilter(CImg<float> picture);
    void removeHistogramFilter(CImg<float> picture);

    /**
     * @brief manageNewWhiteColor Calcul la position du clic et extrait la couleur du pixel
     * @param pos
     * @param labelWidth
     * @param labelHeight
     * @param zoomView
     */
    void manageNewWhiteColor(QPoint pos, int labelWidth, int labelHeight, bool zoomView);

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

private:
    std::string pathOfMainDisplay = "tmp/mainDisplay.bmp";
    std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";
    bool zoomReady;

    bool baseColorGiven;
    bool listenPipetteClick;
    int whiteColor;
};
