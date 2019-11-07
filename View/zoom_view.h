#pragma once
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>

class ScopyBio_Controller;
class QMouseEvent;

class Zoom_View : public QGroupBox
{
    Q_OBJECT

    void readyForClick();
        void createView();

    public slots:
        void setNewPicture(int zoneWidth, int zoneHeight);

    private:
        QGridLayout *m_layout;
        QLabel *m_image;
        bool listenClick;
        ScopyBio_Controller *m_scopybioController;
    Zoom_View(QWidget* parent, ScopyBio_Controller *scopybioController);
    void mousePressEvent( QMouseEvent* ev );
};
