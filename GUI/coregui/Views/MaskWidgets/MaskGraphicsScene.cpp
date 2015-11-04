// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsScene.cpp
//! @brief     Implements class MaskGraphicsScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskGraphicsScene.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "MaskGraphicsProxy.h"
#include <QDebug>

namespace {
const QRectF default_scene_rect(0, 0, 800, 600);
//const QRectF default_scene_rect(0, 0, 2.0, 2.0);
}

MaskGraphicsScene::MaskGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_model(0)
{
    setSceneRect(default_scene_rect);

//    QGraphicsRectItem *b_rect = new QGraphicsRectItem(0, 0, default_scene_rect.width(), default_scene_rect.height());
//    b_rect->setPos(0, 0);
//    b_rect->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
//    addItem(b_rect);

//    qreal width = default_scene_rect.width()*0.99;
//    qreal height = default_scene_rect.height()*0.99;
////    QGraphicsRectItem *b_rect2 = new QGraphicsRectItem(0, 0, 796, 596);
//    QGraphicsRectItem *b_rect2 = new QGraphicsRectItem(0, 0,width, height);
//    qreal xpos = (default_scene_rect.width() - width)/2.;
//    qreal ypos = (default_scene_rect.height() - height)/2.;
////    b_rect2->setPos(2, 2);
//    b_rect2->setPos(xpos, ypos);
//    b_rect2->setPen(QPen(Qt::red));
//    addItem(b_rect2);

}

void MaskGraphicsScene::setModel(SessionModel *model)
{
    if (model != m_model) {

        if (m_model) {
            disconnect(m_model, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            disconnect(m_model, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                       SLOT(onRowsInserted(QModelIndex, int, int)));
            disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            disconnect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsRemoved(QModelIndex, int, int)));
            disconnect(m_model, SIGNAL(modelReset()), this, SLOT(updateScene()));
        }

        m_model = model;

        if(m_model) {
            connect(m_model, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            connect(m_model, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                SLOT(onRowsInserted(QModelIndex, int, int)));
            connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsRemoved(QModelIndex, int, int)));
            connect(m_model, SIGNAL(modelReset()), this, SLOT(updateScene()));
        }

        resetScene();
        updateScene();
    }

}

void MaskGraphicsScene::resetScene()
{

}

void MaskGraphicsScene::updateScene()
{
    if(!m_model) return;
    updateViews();
}

void MaskGraphicsScene::updateViews(const QModelIndex &parentIndex)
{
    Q_ASSERT(m_model);
    qDebug() << "MaskGraphicsScene::updateViews()";

    IntensityDataItem *item = dynamic_cast<IntensityDataItem *>(m_model->getTopItem());
    Q_ASSERT(item);

    MaskGraphicsProxy *proxy = new MaskGraphicsProxy;
    proxy->setItem(item);
    proxy->setPos(0,0);
    proxy->resize(800, 600);
    addItem(proxy);


    QGraphicsRectItem *b_rect = new QGraphicsRectItem(0, 0, default_scene_rect.width(), default_scene_rect.height());
    b_rect->setPos(0, 0);
    b_rect->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    addItem(b_rect);

    qreal width = default_scene_rect.width()*0.99;
    qreal height = default_scene_rect.height()*0.99;
//    QGraphicsRectItem *b_rect2 = new QGraphicsRectItem(0, 0, 796, 596);
    QGraphicsRectItem *b_rect2 = new QGraphicsRectItem(0, 0,width, height);
    qreal xpos = (default_scene_rect.width() - width)/2.;
    qreal ypos = (default_scene_rect.height() - height)/2.;
//    b_rect2->setPos(2, 2);
    b_rect2->setPos(xpos, ypos);
    b_rect2->setPen(QPen(Qt::red));
    addItem(b_rect2);



    QModelIndex intensityDataIndex = m_model->indexOfItem(item);

    for (int i_row = 0; i_row < m_model->rowCount(intensityDataIndex); ++i_row) {
        QModelIndex itemIndex = m_model->index(i_row, 0, intensityDataIndex);

        if (ParameterizedItem *item = m_model->itemForIndex(itemIndex)) {
            qDebug() << "aaa:" << item->modelType();
        }
    }

}
