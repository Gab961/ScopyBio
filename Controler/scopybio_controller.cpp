#include "scopybio_controller.h"
#include "Model/pile_model.h"
#include <iostream>

ScopyBio_Controller::ScopyBio_Controller()
{
    pileModel = new pile_model();
}

void ScopyBio_Controller::ecrireCoucou()
{
    std::cout << "Marche controler" << std::endl;
    testModele();
}

void ScopyBio_Controller::testModele()
{
    pileModel->setFilename("Coucou le gentil modèle");
}
