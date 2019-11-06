#pragma once
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QPoint>
#include <QMouseEvent>
#include <vector>

class ScopyBio_Controller;

class Data_View : public QGroupBox
{
    Q_OBJECT

public slots:
    void processingResults(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

signals:
    void graphClic(int itemIndex);

public:
    Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);
    void mousePressEvent( QMouseEvent* ev );

private:
    void drawResults();

    ScopyBio_Controller *m_scopybioController;
    QGridLayout *m_layout;
    QLabel *m_image;
};
