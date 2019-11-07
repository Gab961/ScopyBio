#include "layer_view.h"

#include <iostream>
#include <QListWidgetItem>
#include "Controler/scopybio_controller.h"

LayerView::LayerView(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{}

void LayerView::loadLayers(std::string path)
{
    //TODO
}
