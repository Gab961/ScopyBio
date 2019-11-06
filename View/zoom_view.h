#pragma once
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>

class ScopyBio_Controller;

class Zoom_View : public QGroupBox
{
    Q_OBJECT

public slots:
    void setNewPicture(int zoneWidth, int zoneHeight);

    private:
        QGridLayout *m_layout;
        QLabel *m_image;
public:
    Zoom_View(QWidget* parent, ScopyBio_Controller *scopybioController);
    ScopyBio_Controller *m_scopybioController;
};
