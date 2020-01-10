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
     * @brief init Initialize the model
     */
    void init();

    /**
     * @brief getMainDisplayPath return path of the image displayed in the main view
     * @return
     */
    std::string getMainDisplayPath() const;

    /**
     * @brief getZoomDisplayPath return path of the image displayed in the zoom view
     * @return
     */
    std::string getZoomDisplayPath() const;

    /**
     * @brief ecrireText draw a text message on the layer at the position of the mouse
     * @param pos1 position of the mouse
     * @param text_a_ecrire text that should be displayed
     * @param fontSize size of the text
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> ecrireText(QPoint pos1, std::string text_a_ecrire, int fontSize, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief dessinerRectangle draw on the layer a rectangle
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> &currentPicture);

    /**
     * @brief dessinerFaisceau draw on the layer a beam
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> dessinerFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief dessinerRond draw round on the layer at the position of the mouse
     * @param posOrig position of the mouse
     * @param diameter diameter of the circle
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> dessinerRond(QPoint pos1, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief dessinerRectanglePertinence draw on the layer a rectangle for displaying user results
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param pertinence level of pertinence
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> dessinerRectanglePertinence(QPoint pos1, QPoint pos2, int pertinence, CImg<float> & currentPicture);

    /**
     * @brief dessinerRond draw a circle at the position of the mouse
     * @param pos position of the mouse
     * @param pertinence level of pertinence
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> dessinerRond(QPoint pos1, int pertinence, CImg<float> & currentPicture);

    /**
     * @brief dessinerLigne draw a line on the layer between 2 positions of the mouse
     * @param pos1 begin of the line
     * @param pos2 end of the line
     * @param isDrawing to know if we draw (true) or erase (false)
     * @param brushSize width of the line
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     * @return
     */
    CImg<float> dessinerLigne(QPoint pos1, QPoint pos2, bool isDrawing, int brushSize, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief dessinerCarre draw a square in the layer at the position of the mouse
     * @param posOrig position of the mouse
     * @param diameter size of the square
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> dessinerCarre(QPoint posOrig, int diameter, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief dessinerCercle draw circle on the layer at the position of the mouse
     * @param posOrig position of the mouse
     * @param diameter diameter of the circle
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> dessinerCercle(QPoint posOrig, int diameter, int labelWidth, int labelHeight, CImg<float> & currentPicture);

    /**
     * @brief drawThickLine draw thick lines
     * @param image the layer to draw in
     * @param x1 Position on x axe of the begining of the line
     * @param y1 Position on y axe of the begining of the line
     * @param x2 Position on x axe of the ending of the line
     * @param y2 Position on y axe of the ending of the line
     * @param line_width width of the line
     * @param isDrawing know if it's drawing, false to erase
     */
    void drawThickLine(CImg<float>& image, const int x1, const int y1, const int x2, const int y2, const unsigned int line_width, bool isDrawing);

    /**
     * @brief applyQuadrillageFilter draw the grid for the result layers
     * @param columns number of columns to draw
     * @param lines number of lines to draw
     * @param picture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> applyQuadrillageFilter(int columns, int lines, CImg<float> picture);

    /**
     * @brief saveZoomFromPicture Save the selected area with the beam in the zoom view
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param currentPicture current picture used to do the zoom
     */
    void saveZoomFromPicture(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight, CImg<float> currentPicture);

    //TODO
    /**
     * @brief saveZoomFromArea
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param currentPicture
     */
    CImg<float> saveZoomFromArea(QPoint pos1, QPoint pos2, CImg<float> currentPicture);

//    /**
//     * @brief savePics Je sais pas
//     * @param x1
//     * @param y1
//     * @param x2
//     * @param y2
//     * @param color
//     * @param currentPicture
//     */
//    void savePics(int x1, int y1, int x2, int y2, unsigned char color, CImg<float> currentPicture);

    /**
     * @brief saveImageAsMainDisplay Enregistre l'image en paramètre en tant que main display
     * @param pictureToShow
     */
    void saveImageAsMainDisplay(CImg<float> pictureToShow);

    //Filtres
    /**
     * @brief applyGreenFilter apply green filter on the image
     * @param picture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> applyGreenFilter(CImg<float> picture);

    /**
     * @brief applyHistogramFilter change the contrast of the image
     * @param picture the layer to draw in
     * @return the layer with the new draw
     */
    CImg<float> applyHistogramFilter(CImg<float> picture);

    /**
     * @brief manageNewWhiteColor Calcul la position du clic et extrait la couleur du pixel
     * @param pos
     * @param labelWidth
     * @param labelHeight
     * @param zoomView
     */
    void manageNewWhiteColor(QPoint pos, int labelWidth, int labelHeight, bool zoomView, CImg<float> currentImage);

    /**
     * @brief manageNewWhiteColor Met une nouvelle couleur de blanc
     * @param newWhite
     */
    void manageNewWhiteColor(int newWhite);

    int getWhiteValue() const;
    void setWhiteValue(int color);

    /**
     * @brief shutdownAllListening Annule toutes les écoutes de clic
     */
    void shutdownAllListening();

    //Vrai si on attend un clic
    bool getListenPipetteClick() const;
    void setListenPipetteClick(bool newValue);
    bool getListenPenClick() const;
    void setListenPenClick(bool newValue);
    bool getListenEraserClick() const;
    void setListenEraserClick(bool newValue);
    bool getListenShapeClick() const;
    void setListenShapeClick(bool newValue);
    bool getListenTextClick() const;
    void setListenTextClick(bool newValue);
    bool getListenSelectionClick() const;
    void setListenSelectionClick(bool newValue);

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

    int getPenSize();
    void setPenSize(int newValue);
    int getShapeSize();
    void setShapeSize(int newValue);
    int getTextSize();
    void setTextSize(int newValue);
    int getEraserSize();
    void setEraserSize(int newValue);
    bool getCircleIsSelected();
    void setCircleIsSelected(bool newValue);


private:
    int pathOfMainDisplayIndex = 0;
    std::string pathOfMainDisplay = "tmp/mainDisplay/mainDisplay0.bmp";
    std::string pathOfZoomedDisplay = "tmp/zoomedDisplay.bmp";

    bool zoomReady;

    bool baseColorGiven;
    bool listenPipetteClick;
    bool listenEraserClick;
    bool listenPenClick;
    bool listenShapeClick;
    bool listenTextClick;
    bool listenSelectionClick;
    int whiteColor;

    int penSize;
    int shapeSize;
    int textSize;
    int eraserSize;
    bool circleIsSelected;
};
