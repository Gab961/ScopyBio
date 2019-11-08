#pragma once
#include "Model/pile_model.h"
#include "Model/dessin_model.h"
#include "Model/data_model.h"
#include "Model/faisceau_model.h"

class ScopyBio_Controller
{


public:
    ScopyBio_Controller();


    /** Partie pile_model **/
    void loadNewTiffFile(std::string filename);
    CImgList<float> getLoadedTiffList();
    CImg<float> getCurrentTiff();
    std::vector<std::string> getIconFilenames();
    CImg<float> getImageAtIndex(int i) const;
    bool fileReady();
    void saveCurrent(int indiceEnCours);

    /** Partie dessin_model **/
    void dessinerFaisceau(int labelWidth, int labelHeight);
    std::string getMainDisplayPath();
    std::string getZoomDisplayPath();
    void saveAsMainDisplay(int i);
    void applyGreenFilter();
    void removeGreenFilter();
    void applyHistogramFilter();
    void removeHistogramFilter();
    void manageNewWhite(QPoint pos, int labelWidth, int labelHeight, bool isZoomView);
    int getWhiteColor();
    void setPipetteClick(bool pipetteClick);
    bool getPipetteClick();
    bool getZoomReady();
    bool getBaseColorGiven();


    /** Partie data_model **/
    std::string getResultDisplayPath();
    void processResultsWithCrop(int labelWidth, int labelHeight);
    void processResultsOnEverything();
    void getResults();
    int getItemAtPoint(int posX, int labelWidth);
    bool dataReady();


    /** Partie faisceau_model **/
    void setFaisceau(QPoint pos1, QPoint pos2);


private:
    pile_model *m_pileModel;
    dessin_model *m_dessinModel;
    data_model *m_dataModel;
    faisceau_model *m_faisceauModel;
    gestionnaire_calque_model gestion_calque;
};
