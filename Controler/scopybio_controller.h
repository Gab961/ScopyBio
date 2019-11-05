#pragma once
#include "Model/pile_model.h"
#include "Model/dessin_model.h"
#include "Model/data_model.h"

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
    void dessinerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    std::string getMainDisplayPath();
    std::string getZoomDisplayPath();
    void saveAsMainDisplay(int i);


    /** Partie data_model **/
    std::string getResultDisplayPath();
    void processResultsWithCrop(QPoint pos1, QPoint pos2);
    void processResultsOnEverything();
    void getResults();

private:
    pile_model *m_pileModel;
    dessin_model *m_dessinModel;
    data_model *m_dataModel;
};
