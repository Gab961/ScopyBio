#include "data_view.h"
#include "scopybio_controller.h"
#include <iostream>

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Data_View::Data_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController)
{
    setTitle("Datas view");

    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);

    m_layout->addWidget(m_image);
    m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    setLayout(m_layout);
}

void Data_View::drawResults()
{
    std::cout << "On est dans drawResults" << std::endl;
    QPixmap pm(m_scopybioController->getResultDisplayPath().c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);
    update();
}

void Data_View::processingResults(QPoint pos1, QPoint pos2)
{
    std::cout << "On est dans processing results" << std::endl;
    m_scopybioController->processResultsWithCrop(pos1, pos2);
    drawResults();
}

