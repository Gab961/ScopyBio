#pragma once
#include <QLabel>
#include <vector>

class ScopyBio_Controller;

class Data_View : public QLabel
{
    Q_OBJECT

public slots:
    void setData(std::vector<int> vec);

public:
    Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);

private:
    int calculPlacementY(int imageHeight, int y);
    void drawResults();

    std::string pathToResult = "tmp/result.bmp";
    std::vector<int> data;
    ScopyBio_Controller *m_scopybioController;
};
