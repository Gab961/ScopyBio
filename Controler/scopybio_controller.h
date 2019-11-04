#pragma once
#include "Model/pile_model.h"

class ScopyBio_Controller
{
public:
    ScopyBio_Controller();
    void ecrireCoucou();
    void testModele();

private:
    pile_model *pileModel;
};
