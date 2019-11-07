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
        void nouveauClicCreerRectangle(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

        void mousePressEvent( QMouseEvent* ev );
        void mouseReleaseEvent( QMouseEvent* ev);

    signals:
        void drawCircleOnMouse( const QPoint& );
        void drawRectOnMouse(const QPoint&, const QPoint&, int labelWidth, int labelHeight);
        void changeZoomedPicture(int zoneWidth, int zoneHeight);
        void processResults(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

    public slots:
        void setNewPicture();        
        void readyForPipetteClick();

    private:
        QPoint origPoint;
        quint64 TEMPS_CLIC_LONG;
        quint64 temps_pression_orig;

        bool listenPipetteClick;

        ScopyBio_Controller *m_scopybioController;
        QGridLayout *m_layout;
        QLabel *m_image;
};
