#pragma once
#include <QLabel>
#include <vector>
#include <QGroupBox>
#include <QGridLayout>

class ScopyBio_Controller;

class Data_View : public QGroupBox
{
    Q_OBJECT

public slots:
    void processingResults(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

public:
    Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);

private:
    void drawResults();

    ScopyBio_Controller *m_scopybioController;
    QGridLayout *m_layout;
    QLabel *m_image;
};
