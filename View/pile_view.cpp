#include "pile_view.h"

#include <iostream>
#include <QListWidgetItem>
#include <QIcon>

Pile_View::Pile_View(QWidget *parent)
{}

void Pile_View::openFile(std::string path)
{
    std::cout << "C'est arrivé ici : " << path << std::endl;
    m_imgList.load_tiff(path.c_str());
    std::cout << m_imgList.size() << std::endl;

    this->setIconSize(QSize(200,200));

    //Enregistrement dans un fichier temporaire
    for (unsigned int i=0; i<m_imgList.size(); i++)
    {
        CImg<float> img = m_imgList[i];

        //TODO
        //TBD où on l'enregistre à terme
        //Enregistrement dans un fichier temporaire en tmp
        std::string chemin = "tmp/" + std::to_string(i) + ".bpm";
        img.save_bmp(chemin.c_str());

        //Obtention d'un QIcon depuis le fichier temporaire
        QPixmap imagepx(chemin.c_str());
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
    return m_imgList[i];
}
