#pragma once
#include <QWidget>
#include "Model/pile_model.h"
#include "Model/dessin_model.h"
#include "Model/analyse_model.h"
#include "Model/faisceau_model.h"
#include "Model/save_model.h"
#include "Model/load_model.h"

#include <thread>


class ScopyBio_Controller : public QWidget
{    
    Q_OBJECT
signals:
    /**
     * @brief fullAnalysisEnded Signal emitted when the full analysis thread terminated
     */
    void fullAnalysisEnded();

    /**
     * @brief userAnalysisEnded Signal emitted when the local analysis thread terminated
     */
    void userAnalysisEnded();

public:
    ScopyBio_Controller();

    /**
     * @brief reinitAllModels Reinit models to initial state
     */
    void reinitAllModels();

    /** Partie affichage **/
    /**
     * @brief DisplayResultImage Load a image and apply all its layers
     * @param idImage Id of the image to show
     */
    void DisplayResultImage(int idImage);

    /**
     * @brief afficherCalque Show/hide a layer
     * @param id Id of the layer to show/hide
     * @param aff True to show, false to hide
     */
    void afficherCalque(int id, bool aff);

    /***********************************************************************************/
    /******************************** Partie pile_model ********************************/
    /***********************************************************************************/

    /**
     * @brief openProject Load a project file
     * @param pathProject Path of the project file
     */
    void openProject(std::string pathProject);

    /**
     * @brief loadNewTiffFile Load a multi-images tiff file
     * @param filename Path of the file
     */
    void loadNewTiffFile(std::string filename);

    /**
     * @brief getLoadedTiffList Getter for the CImgList of the tiff file
     * @return
     */
    CImgList<float> getLoadedTiffList();

    /**
     * @brief getCurrentTiff Getter for the currently selected image
     * @return
     */
    CImg<float> getCurrentTiff();

    /**
     * @brief is24Bits True if the tiff file is 24 bits
     * @return
     */
    bool is24Bits();

    /**
     * @brief getIconFilenames Getter to get all icons filename
     * @return
     */
    std::vector<std::string> getIconFilenames();

    /**
     * @brief getImageAtIndex Getter of the image of the CImgList at a precise index
     * @param i Index of the image
     * @return
     */
    CImg<float> getImageAtIndex(int i) const;

    /**
     * @brief fileReady True if a file or a project finished to initialize
     * @return
     */
    bool fileReady();

    /**
     * @brief saveCurrent Set the current image as the one at the given index
     * @param indiceEnCours Index of the new current image
     */
    void saveCurrent(int indiceEnCours);

    /**
     * @brief getCurrentImageIndex
     * @return
     */
    int getCurrentImageIndex();

    /***********************************************************************************/
    /******************************** Partie Calque ************************************/
    /***********************************************************************************/

    /**
     * @brief reinitUserPertinenceCalque Reinit the layer of pertinence over the zoom
     * @param width New width of layer
     * @param height New height of layer
     */
    void reinitUserPertinenceCalque(int width, int height);

    /**
     * @brief undoAction Undo the last action on current layer
     */
    void undoAction();

    /**
     * @brief redoAction Redo the last action on current layer
     */
    void redoAction();

    /**
     * @brief addMemento Add an action in the memento of the current layer
     */
    void addMemento();

    /**
     * @brief removeCalque Remove the layer with the given id
     * @param id Id of the layer to remove
     */
    void removeCalque(int id);

    /**
     * @brief setCurrentCalqueId Change the current layer id
     * @param newId New id of the layer
     */
    void setCurrentCalqueId(int newId);

    /**
     * @brief getCalquesIdFromImage Getter to get the layer ids for the given image id
     * @param image Image id
     * @return
     */
    std::vector<int> getCalquesIdFromImage(int image);

    /**
     * @brief isHidden Getter to know if the layer with the given id is hide or not
     * @param id Id of the layer
     * @return
     */
    bool isHidden(int id);

    /**
     * @brief CreerNouveauCalque Create a new layer from the min image to the max image
     * @param min Id of the first image covered by the layer
     * @param max Id of the last image covered by the layer
     * @return
     */
    bool CreerNouveauCalque(int min, int max);

    /***********************************************************************************/
    /******************************* Partie dessin_model *******************************/
    /***********************************************************************************/
    /**
     * @brief dessinerFaisceau Draw a beam on a layer
     * @param labelWidth Width of the label from which the clic came
     * @param labelHeight Height of the label from which the clic came
     */
    void dessinerFaisceau(int labelWidth, int labelHeight);

    /**
     * @brief dessinerCercle Draw a circle on a layer
     * @param origPoint Center point of the circle
     * @param labelWidth Width of the label from which the clic came
     * @param labelHeight Height of the label from which the clic came
     * @return
     */
    bool dessinerCercle(QPoint origPoint, int labelWidth, int labelHeight);

    /**
     * @brief dessinerCarre Draw a square on a layer
     * @param origPoint Center point of the square
     * @param labelWidth Width of the label from which the clic came
     * @param labelHeight Height of the label from which the clic came
     * @return
     */
    bool dessinerCarre(QPoint origPoint, int labelWidth, int labelHeight);

    /**
     * @brief dessinerLignePerso Draw a line between two points
     * @param origPoint Point of the start of the line
     * @param pos Point of the end of the line
     * @param labelWidth Width of the label from which the clic came
     * @param labelHeight Height of the label from which the clic came
     * @param isDrawing True if drawing with color, false if it's the eraser
     * @return
     */
    bool dessinerLignePerso(QPoint origPoint, QPoint pos, int labelWidth, int labelHeight, bool isDrawing);

    /**
     * @brief dessinerText Draw a text on a layer
     * @param text Data which must be drawn
     * @param origPoint Point where the text must be placed
     * @param labelWidth Width of the label from which the clic came
     * @param labelHeight Height of the label from which the clic came
     * @return
     */
    bool dessinerText(std::string text, QPoint origPoint, int labelWidth, int labelHeight);

    /**
     * @brief saveZoom Save zoom from the user selected area
     * @param labelWidth Width of the label from which the clic came
     * @param labelHeight Height of the label from which the clic came
     */
    void saveZoom(int labelWidth, int labelHeight);

    /**
     * @brief saveZoomOfUserArea Save the zoom from the user selected area
     */
    void saveZoomOfUserArea();

    /**
     * @brief saveZoomOfCurrentArea Save the zoom from the area where the user clicked (predefined area)
     */
    void saveZoomOfCurrentArea();

    /**
     * @brief getMainDisplayPath Get the main display path
     * @return
     */
    std::string getMainDisplayPath();

    /**
     * @brief getZoomDisplayPath Get the zoom display path
     * @return
     */
    std::string getZoomDisplayPath();

    /**
     * @brief saveAsMainDisplay Save the image of index i from the CImgList as main display image
     * @param i Index of the new image
     */
    void saveAsMainDisplay(int i);

    /**
     * @brief applyGreenFilter Apply green filter over every image
     */
    void applyGreenFilter();

    /**
     * @brief applyHistogramFilter Apply histogram filter over every image
     */
    void applyHistogramFilter();

    /**
     * @brief applyResultatFilter Apply results filter over every image
     */
    void applyResultatFilter();

    /**
     * @brief applyZoomResultatFilter Apply results filter over zoom image
     */
    void applyZoomResultatFilter();

    /**
     * @brief removeHistogramFilter Remove histogram filter over every image
     */
    void removeHistogramFilter();

    /**
     * @brief manageNewWhite Change the white value
     * @param pos Position of where the clic is done
     * @param labelWidth Width of the label from where the clic was done
     * @param labelHeight Height of the label from where the clic was done
     * @param isZoomView True if if comes from the zoom, false otherwise
     */
    void manageNewWhite(QPoint pos, int labelWidth, int labelHeight, bool isZoomView);

    /**
     * @brief getWhiteColor Get the white value from model
     * @return
     */
    int getWhiteColor();

    /**
     * @brief setWhiteColor Set the white value to model
     * @param value New whiteValue value
     */
    void setWhiteColor(int value);

    /**
     * @brief setPipetteClick Set that a pipette clic is waited to the model
     * @param pipetteClick True is a clic is waited, false otherwise
     */
    void setPipetteClick(bool pipetteClick);

    /**
     * @brief getPipetteClick Set if a pipette clic is waited from the model
     * @return
     */
    bool getPipetteClick();

    /**
     * @brief getListenPenClick Get if a pen clic is waited from the model
     * @return
     */
    bool getListenPenClick() const;

    /**
     * @brief setListenPenClick Set that a pen clic is waited to the model
     * @param newValue True if a pen clic is waited, false otherwise
     */
    void setListenPenClick(bool newValue);

    /**
     * @brief getListenSelectionClick Get if a selection clic is waited from the model
     * @return
     */
    bool getListenSelectionClick() const;

    /**
     * @brief setListenSelectionClick Set that a selection clic is waited to the model
     * @param newValue True if a selection clic is waited, false otherwise
     */
    void setListenSelectionClick(bool newValue);

    /**
     * @brief getListenEraserClick Get if a eraser clic is waited from the model
     * @return
     */
    bool getListenEraserClick() const;

    /**
     * @brief setListenEraserClick Set that a eraser clic is waited to the model
     * @param newValue True if a eraser clic is waited, false otherwise
     */
    void setListenEraserClick(bool newValue);

    /**
     * @brief getListenShapeClick Get if a shape clic is waited from the model
     * @return
     */
    bool getListenShapeClick() const;

    /**
     * @brief setListenShapeClick Set that a shape clic is waited to the model
     * @param newValue True if a shape clic is waited, false otherwise
     */
    void setListenShapeClick(bool newValue);

    /**
     * @brief getListenTextClick Get if a text clic is waited from the model
     * @return
     */
    bool getListenTextClick() const;

    /**
     * @brief setListenTextClick Set that a text clic is waited to the model
     * @param newValue True if a text clic is waited, false otherwise
     */
    void setListenTextClick(bool newValue);

    /**
     * @brief getZoomReady Get if a picture is ready to be shown in zoom area
     * @return
     */
    bool getZoomReady();

    /**
     * @brief getBaseColorGiven Get if a whiteValue has been given to the model
     * @return
     */
    bool getBaseColorGiven();

    /**
     * @brief getPenSize Get the pen size from the model
     * @return
     */
    int getPenSize();

    /**
     * @brief setPenSize Set the pen size to the model
     * @param newValue New value of pen size
     */
    void setPenSize(int newValue);

    /**
     * @brief getShapeSize Get the shape size from the model
     * @return
     */
    int getShapeSize();

    /**
     * @brief setShapeSize Set the shape size to the model
     * @param newValue New value of shape size
     */
    void setShapeSize(int newValue);

    /**
     * @brief getTextSize Get the text size from the model
     * @return
     */
    int getTextSize();

    /**
     * @brief setTextSize Set the text size to the model
     * @param newValue New value of text size
     */
    void setTextSize(int newValue);

    /**
     * @brief getEraserSize Get the eraser size from the model
     * @return
     */
    int getEraserSize();

    /**
     * @brief setEraserSize Set the eraser size to the model
     * @param newValue New value of eraser size
     */
    void setEraserSize(int newValue) ;

    /**
     * @brief getCircleIsSelected Get if the circle is selected from the model
     * @return True if circle, false if square
     */
    bool getCircleIsSelected();

    /**
     * @brief setCircleIsSelected Set if the circle is selected in the panel to the model
     * @param newValue True if circle is selected, false if square is selected
     */
    void setCircleIsSelected(bool newValue);

    /***********************************************************************************/
    /******************************** Partie analyse_model *****************************/
    /***********************************************************************************/
    /**
     * @brief areaIsSelected True if an area is selected by the user (predefined area)
     * @return
     */
    bool areaIsSelected();

    /**
     * @brief setAreaIsSelected Set if an area has been selected by the user (predefined area)
     */
    void setAreaIsSelected();

    /**
     * @brief setAnalysisErrorMargin Change the error margin of the analysis
     * @param newValue New margin error
     */
    void setAnalysisErrorMargin(int newValue);

    /**
     * @brief getAnalysisErrorMargin Get the error margin from the model
     */
    int getAnalysisErrorMargin();

    /**
     * @brief userAreaIsSelected Get if the user made a user selection
     * @return True if user selection made, false otherwise
     */
    bool userAreaIsSelected();

    /**
     * @brief setUserAreaIsSelected Set if the user made a user selection
     */
    void setUserAreaIsSelected();

    /**
     * @brief getResultDisplayPath Get the path the the data display image
     * @return
     */
    std::string getResultDisplayPath();

    /**
     * @brief processResultsWithCrop Calculate the results for the user selected area
     * @param labelWidth Width of the label from which the selection has been made
     * @param labelHeight Height of the label from which the selection has been made
     */
    void processResultsWithCrop(int labelWidth, int labelHeight);

    /**
     * @brief processResults Calculate the results for the entire area
     */
    void processResults();

    /**
     * @brief getItemAtPoint Get the item index corresponding to the data image abscisse
     * @param posX Position clicked on the data image
     * @param labelWidth Width of the data label
     * @return
     */
    int getItemAtPoint(int posX, int labelWidth);

    /**
     * @brief dataReady True if an image can be shown in the data view
     * @return
     */
    bool dataReady();

    /**
     * @brief getDataFromArea Show the data and zoom from the area where the user clicked (main display view)
     * @param area Position where the user clicked
     * @param labelWidth Width of the label from where the user clicked
     * @param labelHeight Height of the label from where the user clicked
     */
    void getDataFromArea(QPoint area, int labelWidth, int labelHeight);

    /**
     * @brief getDataFromZoomArea Show the data and zoom from the area where the user clicked (zoom display view)
     * @param area Position where the user clicked
     * @param labelWidth Width of the label from where the user clicked
     * @param labelHeight Height of the label from where the user clicked
     */
    void getDataFromZoomArea(QPoint area, int labelWidth, int labelHeight);

    /**
     * @brief getLineAmount Get the number of lines for the analysis from the model
     * @return
     */
    int getLineAmount();

    /**
     * @brief getColumnAmount Get the number of columns for the analysis from the model
     * @return
     */
    int getColumnAmount();

    /**
     * @brief setLineAmount Set the number of lines for the analysis to the model
     * @param value
     */
    void setLineAmount(int value);

    /**
     * @brief setColumnAmount Set the number of columns for the analysis to the model
     * @param value
     */
    void setColumnAmount(int value);

    /**
     * @brief getAnalysisType Get if the analysis is a user one or a predefined one
     * @return
     */
    bool getAnalysisType();

    /**
     * @brief setAnalysisTypeIsUser Set if the analysis is a user one or a predefined one
     * @param type
     * @return
     */
    void setAnalysisTypeIsUser(bool type);


    /***********************************************************************************/
    /****************************** Partie faisceau_model ******************************/
    /***********************************************************************************/
    /**
     * @brief setFaisceau Set the data of the beam to the model
     * @param pos1 First point of the beam
     * @param pos2 Second point of the beam
     * @param labelWidth Width of the label from which the beam has been selected
     * @param labelHeight Height of the label from which the beam has been selected
     */
    void setFaisceau(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

    /***********************************************************************************/
    /******************************** Partie save_model ********************************/
    /***********************************************************************************/
    /**
     * @brief save_as Save the project in a folder defined by the user
     * @param path Save location
     */
    void save_as(std::string path);

    /**
     * @brief saveCurrentDisplay Save the current displayed image with its layers in a folder defined by the user
     * @param path Save location
     */
    void saveCurrentDisplay(std::string path);

    /**
     * @brief save Save the project in the folder of the project
     * @return
     */
    bool save();

    /**
     * @brief changeSavePath Change the save locations to the model
     * @param newSavePath Save location
     */
    void changeSavePaths(std::string newSavePath);

    /***********************************************************************************/
    /******************************** Partie THREAD ************************************/
    /*************************************************************************************/
    /**
     * @brief listenFullAnalysis Thread doing the full analysis
     */
    void listenFullAnalysis();

    /**
     * @brief listenUserAnalysis Thread doing the user analysis
     */
    void listenUserAnalysis();

private:
    pile_model *m_pileModel;
    dessin_model *m_dessinModel;
    analyse_model *m_analyseModel;
    gestionnaire_calque_model *m_gestion_calque;
    faisceau_model *m_faisceauModel;
    save_model *m_saveModel;
    load_model * m_loadModel;
    std::thread listener;
    std::thread background_task;
};
