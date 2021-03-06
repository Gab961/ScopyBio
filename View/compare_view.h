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
        /**
         * @brief CompareView
         * @param parent
         * @param scopybioController
         */
        CompareView(QWidget *parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief createView : Create the empty view
         */
        void createView();

        /**
         * @brief connections
         */
        void connections();

        /**
         * @brief drawSlider : Create a picture with two other in order to compare them
         *                     and place it in the view
         */
        void drawSlider();

        /**
         * @brief setImages : Get the two images to compare from compare_popup and
         *                    call drawSlider to build the initial view
         * @param image1
         * @param image2
         */
        void setImages(QString image1, QString image2);

    public slots:
        /**
         * @brief compare : Get the value from the QSlider and call drawSlider to build
         *                  the corresponding view
         */
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
