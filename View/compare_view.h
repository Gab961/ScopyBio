#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QSlider>

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
        void setImages(QString image1, QString image2);

    public slots:
        void compare();

    private:
        float valeurSlide = 50;

        QGridLayout *m_displayLayout;
        QGridLayout *m_sliderLayout;
        QGridLayout *m_mainLayout;
        QLabel *m_display;

        QPixmap *m_firstImageFull;
        QPixmap *m_secondImageFull;
        QPixmap *m_resultImage;

        QSlider *m_slider;

        QLineEdit *m_tempTextEdit;
        QPushButton *m_boutonTest;

        ScopyBio_Controller *m_scopybioController;
};
