#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QCloseEvent>

class ScopyBio_Controller;

class LoopView: public QWidget
{
    Q_OBJECT

    public:
        /**
         * @brief LoopView
         * @param parent
         * @param scopybioController
         */
        LoopView(QWidget *parent, ScopyBio_Controller *scopybioController);

        /**
         * @brief createView
         */
        void createView();

        /**
         * @brief connections : Launch the loop
         */
        void connections();

        /**
         * @brief launchTimer
         */
        void launchTimer();

        /**
         * @brief loop : Construct the loop
         */
        void loop();

    public slots:
        /**
         * @brief createLoopView : Launch the timer and show the loop
         */
        void createLoopView();

    private:
        /**
         * @brief closeEvent : Stop the timer
         * @param ev
         */
        void closeEvent(QCloseEvent *ev);

        QGridLayout *m_mainLayout;
        QLabel *m_loop;

        QTimer *timer;
        int value = -1;

        ScopyBio_Controller *m_scopybioController;
};
