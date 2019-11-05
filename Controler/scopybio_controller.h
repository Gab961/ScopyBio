#pragma once
#include "Model/pile_model.h"
#include "Model/dessin_model.h"

class ScopyBio_Controller
{


public:
    ScopyBio_Controller();
    void ecrireCoucou();
    void testModele();

    /** Partie pile_model **/
    void loadNewTiffFile(std::string filename);
    CImgList<float> getLoadedTiffList();
    CImg<float> getCurrentTiff();
    std::vector<std::string> getIconFilenames();
    CImg<float> getImageAtIndex(int i) const;


    /** Partie dessin_model **/
    void dessinerRectangle(QPoint pos1, QPoint pos2);
    std::string getMainDisplayPath();
    std::string getZoomDisplayPath();

private:
    pile_model *m_pileModel;
    dessin_model *m_dessinModel;
};
