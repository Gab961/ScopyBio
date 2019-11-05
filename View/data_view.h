#pragma once
#include <QLabel>
#include <vector>

class ScopyBio_Controller;

class Data_View : public QLabel
{
    Q_OBJECT

public slots:
    void processingResults(QPoint pos1, QPoint pos2);

public:
    Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);

private:
    void drawResults();

    ScopyBio_Controller *m_scopybioController;
};
