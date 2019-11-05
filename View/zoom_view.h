#pragma once
#include <QLabel>
#include <QGridLayout>

class ScopyBio_Controller;

class Zoom_View : public QLabel
{
    Q_OBJECT

public slots:
    void setNewPicture();

    private:
        QGridLayout *m_layout;
        QLabel *m_image;
public:
    Zoom_View(QWidget* parent, ScopyBio_Controller *scopybioController);
    ScopyBio_Controller *m_scopybioController;
};
