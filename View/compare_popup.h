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
        /**
         * @brief ComparePopup
         * @param parent
         * @param scopybioController
         */
        ComparePopup(QWidget *parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief createView : Create the empty view
         */
        void createView();

        /**
         * @brief connections
         */
        void connections();

        /**
         * @brief fillComboBoxes : Fill the combo boxes with the list of all pictures
         */
        void fillComboBoxes();

    public slots:
        /**
         * @brief createComparePopup : Call fillComboBoxes() and show the popup
         */
        void createComparePopup();

        /**
         * @brief openCompareView : Send the two selected pictures to the compare view and close
         *                          the popup. Return a message box if the two selected pictures
         *                          are the same.
         */
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
