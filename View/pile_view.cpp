#include "pile_view.h"

#include <iostream>
#include <QListWidgetItem>
#include <QIcon>
#include "Controler/scopybio_controller.h"

Pile_View::Pile_View(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{
    this->setIconSize(QSize(125, 125));
}

void Pile_View::openFile(std::string path)
{

    clear();
    m_scopybioController->loadNewTiffFile(path);
    std::vector<std::string> iconsfilenames = m_scopybioController->getIconFilenames();

    for (unsigned int i=0; i<iconsfilenames.size();i++)
    {
        //Obtention d'un QIcon depuis le fichier temporaire
        QPixmap imagepx(iconsfilenames[i].c_str());
        QIcon imageIc(imagepx);

        //Création du WidgetItem depuis l'icon et ajout dans la liste
        QListWidgetItem *item = new QListWidgetItem(imageIc, QString::number(i), this);
        this->insertItem(0, item);
    }

    emit pileInitDone();

    this->update();
}


CImg<float> Pile_View::getImage(int i)
{
    return m_scopybioController->getImageAtIndex(i);
}


void Pile_View::changeToElement(int i)
{
    if (m_scopybioController->fileReady())
    {
        setCurrentRow(i);
        getImage(i);
    }
}
