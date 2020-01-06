#include "layer_view.h"

#include <iostream>
#include <QListWidgetItem>
#include <QMenu>
#include <QPoint>
#include "Controler/scopybio_controller.h"

LayerView::LayerView(QWidget *parent, ScopyBio_Controller *scopybioController) : m_scopybioController(scopybioController)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setAttribute(Qt::WA_Hover, true);
    connections();
}

void LayerView::connections() {

}

void LayerView::loadLayers(int currentRow)
{
    setCursor(Qt::PointingHandCursor);
    clear();

    layerIdList = m_scopybioController->getCalquesIdFromImage(currentRow);

    for (unsigned int i = 0; i < layerIdList.size(); i++) {
        QString buttonStyle = "QPushButton{border:none;background-color:rgba(255, 255, 255,100);} QPushButton:hover{background-color:rgba(255, 151, 49,100);}";
        m_itemLayout = new QGridLayout(this);

        m_delete = new QPushButton(QIcon("../../Resources/Icons/delete-cross.svg"), "", this);
        m_delete->setStyleSheet(buttonStyle);
        m_delete->setIconSize(QSize(20,20));
        m_delete->setMinimumSize(25,25);
        m_delete->setMaximumSize(25,25);
        m_itemLayout->addWidget(m_delete, 0, 1);

        QObject::connect(m_delete, &QPushButton::clicked, this, &LayerView::removeLayer);

        m_hide = new QPushButton(QIcon("../../Resources/Icons/visibility.svg"), "", this);
        m_hide->setStyleSheet(buttonStyle);
        m_hide->setIconSize(QSize(20,20));
        m_hide->setMinimumSize(25,25);
        m_hide->setMaximumSize(25,25);
        m_itemLayout->addWidget(m_hide, 0, 2);

        m_line = new QWidget();
        m_layerId = new QLabel(QString::number(layerIdList[i]));

        m_itemLayout->addWidget(m_layerId, 0, 0);

        QListWidgetItem *item = new QListWidgetItem(this);
        m_line->setLayout(m_itemLayout);

        this->setItemWidget(item, m_line);
        QSize itemSize(this->size().width(), 50);
        item->setSizeHint(itemSize);

        this->insertItem(0, item);
    }

//    this->setMouseTracking(true);

    this->update();
}

void LayerView::hoverEnter(QHoverEvent * event) { }
void LayerView::hoverLeave(QHoverEvent * event) { }
void LayerView::hoverMove(QHoverEvent * event) {
    QPoint pos = event->pos();
    QModelIndex index = this->indexAt(pos);
    if (index.row() >= 0)
        rowChanged(index.row());
}
bool LayerView::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(e));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(e));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(e);
}

void LayerView::rowChanged(int row)
{
    currentLayerRow = row;
}

void LayerView::removeLayer()
{
    std::cout << "Item selectionné = " << currentLayerRow << std::endl;
    std::cout << "Id à supprimer = " << layerIdList[currentLayerRow] << std::endl;
    m_scopybioController->removeCalque(layerIdList[currentLayerRow]);
    this->removeItemWidget(item(currentLayerRow));
}
