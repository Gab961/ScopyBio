#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QPushButton>

class ScopyBio_Controller;

class AnalysisPopup: public QWidget
{
    Q_OBJECT

    public:
        AnalysisPopup(QWidget *parent, ScopyBio_Controller *scopybioController);
        void createView();
        void connections();


    private:
        QGridLayout *m_mainLayout;

        QGridLayout *m_layoutButtons;
        QTextEdit *m_rows;
        QTextEdit *m_span;
        QPushButton *m_launch;

        ScopyBio_Controller *m_scopybioController;
};
