#include <iostream>

#include "loop_view.h"
#include "Controler/scopybio_controller.h"

#include <QDesktopWidget>

LoopView::LoopView(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{
    createView();

    connections();

    launchTimer();
}

void LoopView::createView()
{
    QDesktopWidget dw;
    int screenHeight = dw.height()*0.7;
    setFixedSize(screenHeight, screenHeight);

    m_mainLayout = new QGridLayout();

    m_loop = new QLabel(this);
    m_mainLayout->addWidget(m_loop);

    setLayout(m_mainLayout);
}

void LoopView::connections()
{
    timer = new QTimer(this);
    timer->setInterval(70);
    timer->setSingleShot(false);

    QObject::connect(timer, &QTimer::timeout, this, &LoopView::loop);
}

void LoopView::launchTimer()
{
    timer->start();
}

void LoopView::loop()
{
    int nbImg = m_scopybioController->getIconFilenames().size();

    if (value == nbImg-1)
        value = 0;
    else
        value++;

    std::string currentPath = m_scopybioController->getIconFilenames()[value];
    QPixmap pm(currentPath.c_str());
    m_loop->setPixmap(pm);
    m_loop->setScaledContents(true);

    update();
}
