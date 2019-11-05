#pragma once
#include <QLabel>
#include <vector>

class ScopyBio_Controller;

class Data_View : public QLabel
{
    Q_OBJECT

public slots:
    void drawResults();

public:
    Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);

private:
    int calculPlacementY(int imageHeight, int y);

    ScopyBio_Controller *m_scopybioController;
};
