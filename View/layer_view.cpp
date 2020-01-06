#include "layer_view.h"

#include <iostream>
#include <QListWidgetItem>
#include <QMenu>
#include "Controler/scopybio_controller.h"

LayerView::LayerView(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{
    //this->setContextMenuPolicy(Qt::CustomContextMenu);
    connections();
}

void LayerView::connections() {
   // QObject::connect(m_delete, &QPushButton::clicked, this, &LayerView::removeLayer);
}

void LayerView::loadLayers(int currentRow)
{
    setCursor(Qt::PointingHandCursor);
    clear();
    std::vector<int> layerList;

    std::cout << "Je suis là avec l'id : " << currentRow << std::endl;
    layerList = m_scopybioController->getCalquesIdFromImage(currentRow);

    for (unsigned int i = 0; i < layerList.size(); i++) {
        QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
        m_itemLayout = new QGridLayout(this);

        m_delete = new QPushButton(QIcon("../../Resources/Icons/delete-cross.svg"), "", this);
        m_delete->setStyleSheet(buttonStyle);
        m_delete->setIconSize(QSize(20,20));
        m_delete->setMinimumSize(25,25);
        m_delete->setMaximumSize(25,25);
        m_itemLayout->addWidget(m_delete, 0, 1);

        m_hide = new QPushButton(QIcon("../../Resources/Icons/visibility.svg"), "", this);
        m_hide->setStyleSheet(buttonStyle);
        m_hide->setIconSize(QSize(20,20));
        m_hide->setMinimumSize(25,25);
        m_hide->setMaximumSize(25,25);
        m_itemLayout->addWidget(m_hide, 0, 2);

        m_line = new QWidget();
        m_line->setFixedHeight(50);
        m_layerId = new QLabel(QString::number(layerList[i]));
        m_itemLayout->addWidget(m_layerId, 0, 0);

        QListWidgetItem *item = new QListWidgetItem(this);
        m_line->setLayout(m_itemLayout);
        m_line->setFixedWidth(this->size().width());

        this->setItemWidget(item, m_line);

        this->insertItem(0, item);
    }


    this->update();
}

void LayerView::removeLayer(int currentRow)
{

    m_scopybioController->removeCalque(currentRow, currentRow);
    //this->removeItemWidget(itemAt(currentRow));
}
