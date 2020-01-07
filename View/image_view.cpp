#include "image_view.h"
#include <iostream>
#include <QMouseEvent>
#include <QDateTime>
#include "scopybio_controller.h"

#define cimg_use_tiff
#include "CImg.h"

using namespace cimg_library;

Image_View::Image_View( QWidget * parent, ScopyBio_Controller *scopybioController) : QGroupBox( parent ), m_scopybioController(scopybioController)
{
    createView();

    connections();
}

void Image_View::createView()
{
    setTitle("Main view");

    m_layout = new QGridLayout(this);
    m_image = new QLabel(this);

    m_layout->addWidget(m_image);
    //m_layout->setMargin(0);
    m_image->setAlignment(Qt::AlignCenter);

    TEMPS_CLIC_LONG=100;
    TEMPS_CLIC_DESSIN=1;

    setLayout(m_layout);
}

void Image_View::connections()
{
    //Affichage du rectangle
    QObject::connect(this, &Image_View::drawRectOnMouse, this, &Image_View::nouvelleSelectionUtilisateur);

    // récupère la courbe et la zoom view de la zone sélectionnée issue de l'analyse automatique
    QObject::connect(this, &Image_View::getDataFromArea, this, &Image_View::getData);
}

void Image_View::mousePressEvent( QMouseEvent* ev )
{

    temps_pression_orig = QDateTime::currentMSecsSinceEpoch();
    origPoint = ev->pos();

    origPoint.setX(origPoint.x()-m_image->x());
    origPoint.setY(origPoint.y()-m_image->y());

    if (listenPenClick || m_scopybioController->getListenEraserClick())
        firstPenDraw = true;
}

/**
 * @brief Image_View::mouseReleaseEvent
 * Dans le cas d'un clic court, on demande l'affichage d'un point
 * Dans le cas d'un clic long, on demande l'affichage d'un rectangle entre le point de début et le point de fin
 * @param ev
 */
void Image_View::mouseReleaseEvent( QMouseEvent* ev )
{
    if (m_scopybioController->fileReady() && m_scopybioController->is24Bits())
    {
        //Si on est pas en train de dessiner ni de choisir avec la pipette
        if (!listenPenClick && !m_scopybioController->getPipetteClick())
        {
            quint64 temps = QDateTime::currentMSecsSinceEpoch() - temps_pression_orig;
            int widthOfLabel = m_image->width();
            int heightOfLabel = m_image->height();

            //Si c'est un clic long
            if (temps > TEMPS_CLIC_LONG)
            {
                secondPoint = ev->pos();

                secondPoint.setX(secondPoint.x()-m_image->x());
                secondPoint.setY(secondPoint.y()-m_image->y());

                if (!(origPoint.x() == secondPoint.x() && origPoint.y() == secondPoint.y()))
                    emit drawRectOnMouse(origPoint,secondPoint,widthOfLabel, heightOfLabel);
            }
            else
            {
                emit getDataFromArea(origPoint, widthOfLabel, heightOfLabel);
            }
        }
        //Si on sélectionnait une couleur avec la pipette
        if (m_scopybioController->getPipetteClick())
        {
            m_scopybioController->setPipetteClick(false);
            m_scopybioController->manageNewWhite(origPoint, m_image->width(), m_image->height(), false);

            emit pipetteClicked();
        }
        if (m_scopybioController->getListenEraserClick())
        {
            //TODO
            std::cout << "ON VEUT EFFACER" << std::endl;
        }
        if (m_scopybioController->getListenShapeClick())
        {
            QPoint pos = ev->pos();
            pos.setX(pos.x()-m_image->x());
            pos.setY(pos.y()-m_image->y());
            setNewPicture();
            if (m_scopybioController->getCircleIsSelected())
                m_scopybioController->dessinerCercle(m_scopybioController->getCurrentImageIndex(),pos,m_image->width(),m_image->height());
            else
                m_scopybioController->dessinerCarre(m_scopybioController->getCurrentImageIndex(),pos,m_image->width(),m_image->height());
            setNewPicture();
        }
        if (m_scopybioController->getListenTextClick())
        {
            QPoint pos = ev->pos();
            pos.setX(pos.x()-m_image->x());
            pos.setY(pos.y()-m_image->y());

            //On récupère le contenu du texte à écrire avant de dessiner le texte
            emit askTextContent();

            m_scopybioController->dessinerText(m_scopybioController->getCurrentImageIndex(),textContent.toStdString(),pos,m_image->width(),m_image->height());
            setNewPicture();
        }
        //Si on était en train de dessiner
            else
            {
                //TODO Gestion min max
                //m_scopybioController->setCurrentCalqueId(m_scopybioController->get);
                m_scopybioController->addMemento();
            }
    }
}

void Image_View::mouseMoveEvent(QMouseEvent* ev) {
    if (m_scopybioController->getListenPenClick() || m_scopybioController->getListenEraserClick())
    {
        if (firstPenDraw)
        {
            firstPenDraw = false;
            QPoint pos = ev->pos();
            origPoint.setX(pos.x()-m_image->x());
            origPoint.setY(pos.y()-m_image->y());
        }
        else
        {
            QPoint pos = ev->pos();
            pos.setX(pos.x()-m_image->x());
            pos.setY(pos.y()-m_image->y());

            if (m_scopybioController->getListenPenClick())
                m_scopybioController->dessinerLignePerso(m_scopybioController->getCurrentImageIndex(),origPoint,pos,m_image->width(),m_image->height(), true);
            else
                m_scopybioController->dessinerLignePerso(m_scopybioController->getCurrentImageIndex(),origPoint,pos,m_image->width(),m_image->height(), false);


            setNewPicture();
            origPoint = pos;
        }
    }
}

void Image_View::readyForPenDraw() { listenPenClick = true; }
void Image_View::cancelPenDraw() { listenPenClick = false; }
void Image_View::readyForPipetteClick() { m_scopybioController->setPipetteClick(true); }

/**
 * @brief Image_View::setNewPicture Modifie l'image affichée dans le label par l'image située au chemin donné
 * @param path
 */

void Image_View::setNewPicture()
{
    float ratio = 0.0;

    setCursor(Qt::CrossCursor);

    // Sert à créer une image qui va prendre un maximum de place possible
    // sans empiéter sur les autres widgets
    if (m_scopybioController->getCurrentTiff().width() >= m_scopybioController->getCurrentTiff().height()) {
        if (m_scopybioController->getCurrentTiff().width() >= size().width()) {
            ratio = (float)m_scopybioController->getCurrentTiff().width() / (float)size().width();
            m_image->setFixedWidth(size().width());
            m_image->setFixedHeight(static_cast<int>(m_scopybioController->getCurrentTiff().height()/ratio));
        } else {
            ratio = (float)size().width() / (float)m_scopybioController->getCurrentTiff().height();
            m_image->setFixedWidth(size().width());
            m_image->setFixedHeight(static_cast<int>(m_scopybioController->getCurrentTiff().height()*ratio));
        }
    }
    else {
        if (m_scopybioController->getCurrentTiff().height() >= size().height()) {
            ratio = (float)m_scopybioController->getCurrentTiff().height() / (float)size().height();
            m_image->setFixedWidth(static_cast<int>(m_scopybioController->getCurrentTiff().width()/ratio));
            m_image->setFixedHeight(size().height());
        } else {
            ratio = (float)size().width() / (float)m_scopybioController->getCurrentTiff().height();
            m_image->setFixedWidth(static_cast<int>(m_scopybioController->getCurrentTiff().width()*ratio));
            m_image->setFixedHeight(size().height());
        }
    }

    QPixmap pm(m_scopybioController->getMainDisplayPath().c_str());
    m_image->setPixmap(pm);
    m_image->setScaledContents(true);

    update();
}

void Image_View::startUserAnalysis()
{
    emit processResults(m_image->width(),m_image->height());

    //MAJ des interfaces
    emit userAnalyseReady();
    emit changeGraphPicture();
    emit changeZoomPicture();

    update();
}

void Image_View::nouvelleSelectionUtilisateur(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight)
{
    //Dessine le rectangle sur l'image et créer l'image zoomée
    m_scopybioController->setFaisceau(pos1, pos2, labelWidth, labelHeight);
    m_scopybioController->dessinerFaisceau(labelWidth, labelHeight);
    m_scopybioController->setUserAreaIsSelected();
    setNewPicture();


    emit activateLocalAnalyse();
    emit clearDataView();

    //Demande de rafraichir le zoom
    m_zoneWidth = pos1.x() - pos2.x();
    if (m_zoneWidth < 0) m_zoneWidth = m_zoneWidth * -1;
    m_zoneHeight = pos1.y() - pos2.y();
    if (m_zoneHeight < 0) m_zoneHeight = m_zoneHeight * -1;
    emit changeZoomPicture();

    update();
}

void Image_View::updateZoomOnly()
{
    emit changeZoomPicture();
}

void Image_View::askProcessFromZoom()
{
    //Demande de calculer les résultats pour la zone si une couleur de base a été donnée
    if (m_scopybioController->getBaseColorGiven())
        emit processResults(m_image->width(),m_image->height());

}

void Image_View::getData(QPoint area, int labelWidth, int labelHeight) {
    if (m_scopybioController->dataReady())
    {
        m_scopybioController->setAreaIsSelected();
        m_scopybioController->getDataFromArea(area, labelWidth, labelHeight);

        setNewPicture();
        emit desactivateLocalAnalyse();

        //MAJ des interfaces
        emit userAnalyseReady();
        emit changeZoomPicture();
        emit changeGraphPicture();

        update();
    }
}


void Image_View::receiveTextContent(QString content)
{
    textContent = content;
}
