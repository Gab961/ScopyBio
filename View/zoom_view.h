#pragma once
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>

class ScopyBio_Controller;
class QMouseEvent;

class Zoom_View : public QGroupBox
{
    Q_OBJECT

    public:
        Zoom_View(QWidget* parent, ScopyBio_Controller *scopybioController);
        void mousePressEvent( QMouseEvent* ev );
        void readyForClick();
        void createView();

    public slots:
        void setNewPicture(int zoneWidth, int zoneHeight);
        void setPictureFromFile();
        void enableDisplay();

    signals:
        void processResultsFromZoom();
        void pipetteClicked();

    private:
        QGridLayout *m_layout;
        QLabel *m_image;
        ScopyBio_Controller *m_scopybioController;
        bool readyToShow;
};
