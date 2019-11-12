#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>

class QPushButton;
class QLineEdit;

class ScopyBio_Controller;

class CompareView: public QWidget
{
    Q_OBJECT

    public:
        CompareView(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void connections();
        void drawSlider();

    public slots:
        void blabla();

    private:
        float valeurSlide = 50;

        QGridLayout *m_mainLayout;
        QLabel *m_display;

        QPixmap *m_firstImageFull;
        QPixmap *m_secondImageFull;
        QPixmap *m_resultImage;

        QLineEdit *m_tempTextEdit;
        QPushButton *m_boutonTest;

        ScopyBio_Controller *m_scopybioController;
};
