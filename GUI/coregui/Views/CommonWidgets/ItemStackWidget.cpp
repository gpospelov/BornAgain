// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/CommonWidgets/ItemStackWidget.cpp
//! @brief     Implements class ItemStackWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ItemStackWidget.h"
#include "SessionModel.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDebug>

ItemStackWidget::ItemStackWidget(QWidget *parent)
    : QWidget(parent)
    , m_stackedWidget(new QStackedWidget)
    , m_model(0)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_stackedWidget);
    setLayout(layout);
}

void ItemStackWidget::setModel(SessionModel *model)
{
    if(model == m_model)
        return;

    disconnectModel();
    m_model = model;
    connectModel();
}

void ItemStackWidget::onModelAboutToBeReset()
{
    qDebug() << "ItemStackWidget::onModelAboutToBeReset()";
}

void ItemStackWidget::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int)
{
    qDebug() << "ItemStackWidget::onRowsAboutToBeRemoved()";
    SessionItem *item = m_model->itemForIndex(m_model->index(first, 0, parent));
    removeWidgetForItem(item);
}

void ItemStackWidget::onSelectionChanged(SessionItem *item)
{
    qDebug() << "ItemStackWidget::onSelectionChanged(SessionItem *item)" << item->displayName();
    setItem(item);
}


void ItemStackWidget::connectModel()
{
    if(!m_model) return;

    connect(m_model, SIGNAL(modelAboutToBeReset()),
            this, SLOT(onModelAboutToBeReset()),
            Qt::UniqueConnection);

    connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)),
            this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)),
            Qt::UniqueConnection);
}

void ItemStackWidget::disconnectModel()
{
    if(!m_model) return;

    disconnect(m_model, SIGNAL(modelAboutToBeReset()),
            this, SLOT(onModelAboutToBeReset()));

    disconnect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)),
            this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
}
