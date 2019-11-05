#include "data_view.h"
#include "scopybio_controller.h"
#include <iostream>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Data_View::Data_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QLabel( parent ), m_scopybioController(scopybioController)
{}

void Data_View::drawResults()
{
    std::cout << "On est dans drawResults" << std::endl;
    QPixmap pm(m_scopybioController->getResultDisplayPath().c_str());
    this->setPixmap(pm);
    this->setScaledContents(true);
    update();
}

void Data_View::processingResults(QPoint pos1, QPoint pos2)
{
    std::cout << "On est dans processing results" << std::endl;
    m_scopybioController->processResultsWithCrop(pos1, pos2);
    drawResults();
}

