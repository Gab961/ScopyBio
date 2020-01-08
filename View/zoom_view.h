#pragma once
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>

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
        void getData(QPoint area, int labelWidth, int labelHeight);

    public slots:
        void setNewPicture(int zoneWidth, int zoneHeight);
        void setPictureFromFile();
        void enableDisplay();
        void resetZoomView();

    signals:
        void processResultsFromZoom();
        void pipetteClicked();
        void changeGraphPicture();

    private:
        QGridLayout *m_layout;
        QLabel *m_image;
        QPushButton *m_hide;
        ScopyBio_Controller *m_scopybioController;
        bool readyToShow;
};
