#pragma once
#include "Model/pile_model.h"

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

private:
    pile_model *m_pileModel;
};
