#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>

class ScopyBio_Controller;
class CompareView;

class ComparePopup: public QWidget
{
    Q_OBJECT

    public:
        ComparePopup(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void connections();
        void fillComboBoxes();

    public slots:
        void createComparePopup();
        void openCompareView();


    private:
        QGridLayout *m_mainLayout;

        QGridLayout *m_layoutComboBox;
        QComboBox *m_firstImage;
        QComboBox *m_secondImage;

        QGridLayout *m_layoutButtons;
        QPushButton *m_accept;
        QPushButton *m_cancel;

        CompareView *m_compareWindow;

        ScopyBio_Controller *m_scopybioController;
};
