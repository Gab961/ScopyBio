#pragma once
#include <QLabel>
#include <vector>

class Data_View : public QLabel
{
    Q_OBJECT

public slots:
    void setData(std::vector<int> vec);

public:
    Data_View(QWidget* parent = 0);

private:
    int calculPlacementY(int imageHeight, int y);
    void drawResults();

    std::string pathToResult = "tmp/result.bmp";
    std::vector<int> data;
};
