#pragma once

#include <string>
#include <cstdlib>
#include <vector>
#include <map>

#include <iostream>

#include "definition.h"

class QPoint;

#include "calque.h"

using numImg = int;

class command_memento;

class gestionnaire_calque_model
{
public:
    gestionnaire_calque_model();

    /**
     * @brief init initialization of all variable
     * @param pileWidth width of the label
     * @param pileHeight height of the label
     */
    void init(int pileWidth, int pileHeight);

    /**
     * @brief initGlobalCalques initialization of all important layers
     * @param pileWidth width of the label
     * @param pileHeight height of the label
     */
    void initGlobalCalques(int _pileWidth, int _pileHeight);

    //TODO A supprimer?
    /**
     * @brief saveTmpforDisplay save layer temporarily for display on screen.
     * @param idCalque
     */
    void saveTmpforDisplay(int idCalque);

    /**
     * @brief existeCalque check if the layer exists or not
     * @param  id of the layer
     * @return true if exists, false else.
     */
    bool existeCalque(int id);

    /**
     * @brief creerCalque create calque of the user
     * @param width width of the layer
     * @param height height of the layer
     * @param min From which image the layer should be visible
     * @param max To which image the layer should be visible
     * @param taille size of the pile
     */
    void creerCalque(int width, int height, int min, int max, int taille);

    /**
     * @brief creerCalqueSpecial create special layer (not created by the user)
     * @param width width of the layer
     * @param height height of the layer
     * @param min From which image the layer should be visible (id negative for special layer)
     * @param max To which image the layer should be visible (id negative for special layer)
     * @param idCalque to force the layer to have a special id (id negative for special layer)
     */
    void creerCalqueSpecial(int width, int height, int min, int max, int idCalque);

    /**
     * @brief getCalqueIndex return index in the list of layers
     * @param id id of the layer what we are looking for
     * @return return the index, -1 if layer not found
     */
    int getCalqueIndex(int id);

    /**
     * @brief addCalques add layers in the list of layers /!\ USED ONLY BY LOAD_MODEL !
     * @param calques the list of layers
     * @param taille size of the pile
     */
    void addCalques(std::vector<calque> calques, int taille);

    //TODO rename?
    /**
     * @brief addCalqueSpecial set the image of a special layer /!\ USED ONLY BY LOAD_MODEL !
     * @param cal image to apply to the layer
     * @param id id of the special layer
     */
    void addCalqueSpecial(CImg<float> cal, int id);

    /**
     * @brief removeCalques remove a user layer from the list of layers
     * @param idCalque id of the layer to remove
     */
    void removeCalques(int idCalque);

    //TODO: rename
    /**
     * @brief calqueShowable set the layer to showable or not
     * @param idCalque id of the layer
     * @param show true can show, false can't
     */
    void calqueShowable(int idCalque, bool show);

    /**
     * @brief dessinerFaisceau draw in the correct layer a beam
     * @param pos1 point of origin
     * @param pos2 opposite point
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessineFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

    /**
     * @brief dessinText draw a text message on the correct layer at the position of the mouse
     * @param pos1 position of the mouse
     * @param text_a_ecrire text that should be displayed
     * @param fontSize size of the text
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessinText(QPoint pos1, std::string text, int fontSize, int labelWidth, int labelHeight);

    /**
     * @brief dessinCercle draw circle on the correct layer at the position of the mouse
     * @param posOrig position of the mouse
     * @param diameter diameter of the circle
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessinCercle(QPoint origPoint, int diameter, int labelWidth, int labelHeight);

    /**
     * @brief dessinCarre draw a square in the layer at the position of the mouse
     * @param posOrig position of the mouse
     * @param diameter size of the square
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     */
    void dessinCarre(QPoint origPoint, int diameter, int labelWidth, int labelHeight);

    /**
     * @brief reinitPertinenceCalque initialize the result layer
     */
    void reinitPertinenceCalque();

    /**
     * @brief reinitUserPertinenceCalque initialize the user result (in the beam) layer
     * @param width width of the label
     * @param height height of the label
     */
    void reinitUserPertinenceCalque(int width, int height);

    /**
     * @brief reinitFaisceauCalque initialize the beam layer
     */
    void reinitFaisceauCalque();

    //TODO
    void manageNewUserAnalyse(int pertinence, QPoint pos1, QPoint pos2);
    //TODO
    void manageNewAnalyse(int pertinence, QPoint pos1, QPoint pos2);

    /**
     * @brief dessinLigne draw a line in the layer between 2 positions of the mouse
     * @param pos1 begin of the line
     * @param pos2 end of the line
     * @param brushSize width of the line
     * @param labelWidth width of the label
     * @param labelHeight height of the label
     * @param isDrawing TODO
     */
    void dessinLigne(QPoint pos1, QPoint pos2, int brushSize, int labelWidth, int labelHeight, bool isDrawing);

    /**
     * @brief updateCalqueVert switch the possibility to display the green layer
     */
    void updateCalqueVert();

    /**
     * @brief updateHistogram switch the possibility to display the histogram
     */
    void updateHistogram();

    /**
     * @brief updateResultat switch the possibility to display the result
     */
    void updateResultat();

    /**
     * @brief updateZoomResultat switch the possibility to display the user result
     */
    void updateZoomResultat();

    //TODO
    /**
     * @brief updateQuadrillage
     * @param columns
     * @param lines
     */
    void updateQuadrillage(int columns, int lines);

    //TODO
    void updateUserQuadrillage(int columns, int lines);

    /**
     * @brief getCalqueForDisplay return the layer to display the image containing in it
     * @param id
     * @return the calque class
     */
    calque getCalqueForDisplay(int id);
    calque getPertinenceCalque();
    std::vector<calque> getAllCalques() const;
    int getCurrentCalqueId();
    void setCurrentCalqueId(int newId);
    void setShowResultat(bool newValue);

    /**
     * @brief mergeUserAnalysis merge the zoom image to the result user (beam) layer
     * @param zoom image from the beam
     * @param zoomPath result layer from the beam
     */
    void mergeUserAnalysis(CImg<float> zoom, std::string zoomPath);

    /**
     * @brief mergeCalques merge the current image of the pile with all layers (user + special)
     * @param ids id of all layers that should be displayed with the current image
     * @param currentDisplayedImage current image displayed
     * @param pathOfMainDisplay Path to save the image with layers to display on the screen
     */
    void mergeCalques(std::vector<int> ids, CImg<float> currentDisplayedImage, std::string pathOfMainDisplay);


    //MEMENTO
    /**
     * @brief undo find the current layer to apply undo function
     */
    void undo();

    /**
     * @brief redo find the current layer to apply redo function
     */
    void redo();

    /**
     * @brief addMemento find the current layer to apply addMemento function
     */
    void addMemento();


    //          Fonction pour le dictionnaire
    /**
     * @brief addInDict Add into the dict the id of the layer to know which image should show the layer
     * @param min From which image the layer should be merged
     * @param max To which image the layer should be merged
     * @param taille size of the pile
     * @param id id of the layer
     */
    void addInDict(int min, int max, int taille, int id);

    /**
     * @brief addInDict Add into the dict the id of the layer to know which image should show the layer /!\ USED ONLY BY LOAD_MODEL !
     * @param cal the layer class (calque)
     * @param taille size of the layer
     */
    void addInDict(calque cal, int taille);

    /**
     * @brief removeFromDict remove from the dict the layer (after the user delete it)
     * @param min From which image the layer was to be merged
     * @param max To which image the layer was to be merged
     * @param id id of the layer
     */
    void removeFromDict(int min, int max, int id);

    /**
     * @brief getListOfCalqueFromImage get the id of layer that should be merged with the current image to display
     * @param idImage id of the current image
     * @return return a list of the id of layers to apply to the image
     */
    std::vector<int> getListOfCalqueFromImage(int idImage);

    /*
     * Permet d'afficher le dictionnaire
     *
     * */

    /**
     * @brief afficheDic display the dict in the terminal for debug
     */
    void afficheDic();

    /**
     * @brief afficheCalques display the list of layers in the terminal for debug
     */
    void afficheCalques();


protected:
    int pileWidth;
    int pileHeight;
    std::map<numImg,std::vector<int>> dictionnaireImgMap;// Associate the images to a list of layers
    std::vector<calque> listOfCalque;// Save all layers
    int id; // Allow creation of all layer with a unique id
    bool isGreen; // Allow to display the green filter
    bool isHistogram; //Allow to display the histogram filter
    bool isResultat; // Allow to display the result filter
    bool isZoomResultat; // Allow to display the user result (beam) filter
    std::string pathOfHistogramSave = "tmp/histogram.bmp";
    int idPertinenceCalque;
    int idUserPertinenceCalque;
    int idCurrentCalque; // To know which layer is currently used
};
