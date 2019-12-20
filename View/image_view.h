#pragma once
#include <string>
#include <chrono>

#include <QGridLayout>
#include <QLabel>
#include <QPoint>
#include <QGroupBox>

using namespace std::chrono;

class ScopyBio_Controller;

class Image_View : public QGroupBox
{
    Q_OBJECT

public:
    Image_View( QWidget* parent, ScopyBio_Controller *scopybioController);
    void createView();
    void connections();

    void updateZoomOnly();

    void mousePressEvent( QMouseEvent* ev );
    void mouseReleaseEvent( QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

signals:
    void drawCircleOnMouse( const QPoint& );
    void drawRectOnMouse(const QPoint&, const QPoint&, int labelWidth, int labelHeight);
    void changeZoomedPicture(int zoneWidth, int zoneHeight);
    void processResults(int labelWidth, int labelHeight);
    void pipetteClicked();
    void getDataFromArea(const QPoint&, int labelWidth, int labelHeight);
    void changeZoomPicture();
    void changeGraphPicture();
    void userAnalyseReady();
    void activateLocalAnalyse();
    void desactiveLocalAnalyse();

public slots:
    void setNewPicture();
    void readyForPipetteClick();
    void readyForPenDraw();
    void cancelPenDraw();
    void askProcessFromZoom();
    void nouvelleAnalyseUtilisateur(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);
    void getData(QPoint area, int labelWidth, int labelHeight);

private:
    QPoint origPoint;
    QPoint secondPoint;
    quint64 TEMPS_CLIC_LONG;
    quint64 TEMPS_CLIC_DESSIN;
    quint64 temps_pression_orig;

    bool listenPipetteClick;
    bool listenPenClick = false;
    bool firstPenDraw = true;

    ScopyBio_Controller *m_scopybioController;
    QGridLayout *m_layout;
    QLabel *m_image;

    int m_zoneWidth;
    int m_zoneHeight;
};
