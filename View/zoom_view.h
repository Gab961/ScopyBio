#pragma once
#include <QLabel>

class ScopyBio_Controller;

class Zoom_View : public QLabel
{
    Q_OBJECT

public slots:
    void setNewPicture(std::string path);

public:
    Zoom_View(QWidget* parent, ScopyBio_Controller *scopybioController);
    ScopyBio_Controller *m_scopybioController;
};
