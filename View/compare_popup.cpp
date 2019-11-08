#include "compare_popup.h"
#include "Controler/scopybio_controller.h"

#include <QDesktopWidget>

ComparePopup::ComparePopup(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{
    createView();
    connections();
}

void ComparePopup::createView()
{
    setFixedSize(400, 100);

    m_mainLayout = new QGridLayout();
    m_layoutComboBox = new QGridLayout();
    m_layoutButtons = new QGridLayout();

    m_firstImage = new QComboBox(this);
    m_firstImage->setFixedWidth(190);
    m_layoutComboBox->addWidget(m_firstImage, 0, 0);

    m_secondImage = new QComboBox(this);
    m_secondImage->setFixedWidth(190);
    m_layoutComboBox->addWidget(m_secondImage, 0, 1);

    m_cancel = new QPushButton("Cancel", this);
    m_cancel->setFixedWidth(100);
    m_layoutButtons->addWidget(m_cancel, 1, 0);

    m_accept = new QPushButton("Ok", this);
    m_accept->setFixedWidth(100);
    m_layoutButtons->addWidget(m_accept, 1, 1);

    m_mainLayout->addLayout(m_layoutComboBox, 0, 0);
    m_mainLayout->addLayout(m_layoutButtons, 1, 0);

    setLayout(m_mainLayout);
}

void ComparePopup::connections()
{

}

void ComparePopup::fillComboBoxes()
{
    QString imageName;
    std::vector<std::string> iconsfilenames = m_scopybioController->getIconFilenames();

    for (unsigned int i=0; i<iconsfilenames.size(); i++)
    {
        //TODO Voir si les dossiers seront a terme dans tmp sinon modifier le substr
        imageName = QString::fromStdString(iconsfilenames[i].substr(4,iconsfilenames[i].length()-1));
        m_firstImage->addItem(imageName);
        m_secondImage->addItem(imageName);
    }
}

void ComparePopup::createComparePopup()
{
    if(m_scopybioController->fileReady())
    {
        fillComboBoxes();
        show();
    }
}
