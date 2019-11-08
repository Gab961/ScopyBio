#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>


class ScopyBio_Controller;

class CompareView: public QWidget
{
    Q_OBJECT

    public:
        CompareView(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void connections();


    private:
        QGridLayout *m_mainLayout;
        QLabel *m_firstImage;
        QLabel *m_secondImage;

        ScopyBio_Controller *m_scopybioController;
};
