#pragma once
#include "Model/pile_model.h"
#include "Model/dessin_model.h"
#include "Model/analyse_model.h"
#include "Model/faisceau_model.h"
#include "Model/save_model.h"


class ScopyBio_Controller
{

public:
    ScopyBio_Controller();

    /** Partie affichage **/
    void DisplayResultImage(int idImage);

    /***********************************************************************************/
    /******************************** Partie pile_model ********************************/
    /***********************************************************************************/
    /**
     * @brief loadNewTiffFile Charge un tif multi-image
     * @param filename
     */
    void loadNewTiffFile(std::string filename);

    /**
     * @brief getLoadedTiffList Récupère la liste CImgList du tif
     * @return
     */
    CImgList<float> getLoadedTiffList();

    /**
     * @brief getCurrentTiff Récupère l'image affichée dans le mainDisplay
     * @return
     */
    CImg<float> getCurrentTiff();

    /**
     * @brief getIconFilenames Récupère la liste des tous les fichiers enregistrés pour la pile
     * @return
     */
    std::vector<std::string> getIconFilenames();

    /**
     * @brief getImageAtIndex Récupère l'image CImg à l'emplacement i du CImgList
     * @param i
     * @return
     */
    CImg<float> getImageAtIndex(int i) const;

    /**
     * @brief fileReady Vrai si un fichier tif ou un projet est ouvert
     * @return
     */
    bool fileReady();

    /**
     * @brief saveCurrent Sauvegarde l'image en cours je suppose :)
     * @param indiceEnCours
     */
    void saveCurrent(int indiceEnCours);

    /**
     * @brief getCurrentImageIndex
     * @return
     */
    int getCurrentImageIndex();

    /***********************************************************************************/
    /******************************* Partie dessin_model *******************************/
    /***********************************************************************************/
    /**
     * @brief dessinerFaisceau Dessine le faisceau sur un calque
     * @param labelWidth
     * @param labelHeight
     */
    void dessinerFaisceau(int labelWidth, int labelHeight);

    /**
     * @brief dessinerLignePerso
     * @param imageIndex
     * @param pos
     * @param labelWidth
     * @param labelHeight
     */
    void dessinerLignePerso(int imageIndex, QPoint origPoint, QPoint pos, int labelWidth, int labelHeight);

    /**
     * @brief saveZoom Enregistre l'image zoomée depuis la sélection
     * @param labelWidth
     * @param labelHeight
     */
    void saveZoom(int labelWidth, int labelHeight);

    /**
     * @brief saveZoomOfCurrentArea Enregistre le zoom de la zone actuellement sélectionnée
     */
    void saveZoomOfCurrentArea();
    /**
     * @brief getMainDisplayPath Renvoie le chemin de l'image du display principal
     * @return
     */
    std::string getMainDisplayPath();

    /**
     * @brief getZoomDisplayPath Renvoie le chemin de l'image du display zoom
     * @return
     */
    std::string getZoomDisplayPath();

    /**
     * @brief saveAsMainDisplay Enregistre l'image i du CImgList en tant qu'affichage principal
     * @param i
     */
    void saveAsMainDisplay(int i);

    /**
     * @brief applyGreenFilter Applique le filtre vert sur l'ensemble des images
     */
    void applyGreenFilter();

    /**
     * @brief applyHistogramFilter Applique le contraste à l'ensemble des images
     */
    void applyHistogramFilter();

    /**
     * @brief removeHistogramFilter Supprime le contraste à l'ensemble des images
     */
    void removeHistogramFilter();

    /**
     * @brief manageNewWhite Modifie le blanc par défaut (après clic sur pipette)
     * @param pos
     * @param labelWidth
     * @param labelHeight
     * @param isZoomView
     */
    void manageNewWhite(QPoint pos, int labelWidth, int labelHeight, bool isZoomView);

    /**
     * @brief getWhiteColor Récupère le blanc actuel
     * @return
     */
    int getWhiteColor();

    /**
     * @brief setPipetteClick Pour indiquer qu'un clic de pipette est attendu
     * @param pipetteClick
     */
    void setPipetteClick(bool pipetteClick);

    /**
     * @brief getPipetteClick Récupère si un clic de pipette est attendu ou non
     * @return
     */
    bool getPipetteClick();

    /**
     * @brief getZoomReady Récupère si il existe une image dans la fenêtre de zoom
     * @return
     */
    bool getZoomReady();

    /**
     * @brief getBaseColorGiven Récupère si une couleur de blanc a été donnée
     * @return
     */
    bool getBaseColorGiven();

    /***********************************************************************************/
    /******************************** Partie analyse_model ********************************/
    /***********************************************************************************/
    /**
     * @brief getResultDisplayPath Récupère le chemin de l'image s'affichant dans le data display
     * @return
     */
    std::string getResultDisplayPath();

    /**
     * @brief processResultsWithCrop Calcul et produit le résultat pour la zone sélectionnée
     * @param labelWidth
     * @param labelHeight
     */
    void processResultsWithCrop(int labelWidth, int labelHeight);

    /**
     * @brief processResults Calcul et produit tous les résultats de l'image
     * @param labelWidth
     * @param lavelHeight
     */
    void processResults();

    /**
     * @brief getItemAtPoint Renvoie l'item correspondant à l'axe des abscisses sur le graph de données
     * @param posX
     * @param labelWidth
     * @return
     */
    int getItemAtPoint(int posX, int labelWidth);

    /**
     * @brief dataReady Renvoie vrai si il existe une image dans le data display
     * @return
     */
    bool dataReady();

    /**
     * @brief getDataFromArea Lors d'un clic sur une zone de l'image, affiche le graphe data et le zoom associés
     * @param area
     * @param labelWidth
     * @param labelHeight
     */
    void getDataFromArea(QPoint area, int labelWidth, int labelHeight);


    /***********************************************************************************/
    /****************************** Partie faisceau_model ******************************/
    /***********************************************************************************/
    /**
     * @brief setFaisceau Enregistre les points cliqués pour le faisceau
     * @param pos1
     * @param pos2
     */
    void setFaisceau(QPoint pos1, QPoint pos2);

    /***********************************************************************************/
    /******************************** Partie save_model ********************************/
    /***********************************************************************************/
    /**
     * @brief save_as
     * @param path
     */
    void save_as(std::string path);

    /**
     * @brief save
     * @return
     */
    bool save();

    /**
     * @brief changeSavePath
     * @param newSavePath
     */
    void changeSavePath(std::string newSavePath);

private:
    pile_model *m_pileModel;
    dessin_model *m_dessinModel;
    analyse_model *m_analyseModel;
    gestionnaire_calque_model *m_gestion_calque;
    faisceau_model *m_faisceauModel;
    save_model *m_saveModel;
};
