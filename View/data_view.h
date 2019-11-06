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

    public:
        Data_View(QWidget* parent, ScopyBio_Controller *scopybioController);
        void createView();
        void mousePressEvent( QMouseEvent* ev );

    signals:
        void graphClic(int itemIndex);

    public slots:
        void processingResults(QPoint pos1, QPoint pos2, int labelWidth, int labelHeight);

    private:
        void drawResults();

        ScopyBio_Controller *m_scopybioController;
        QGridLayout *m_layout;
        QLabel *m_image;
};
