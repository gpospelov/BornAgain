// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/CommonWidgets/ItemSelectorWidget.cpp
//! @brief     Implements class ItemSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ItemSelectorWidget.h"
#include "SessionModel.h"
#include "SessionItem.h"
#include <QListView>
#include <QVBoxLayout>
#include <QDebug>

ItemSelectorWidget::ItemSelectorWidget(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
    , m_model(0)
{
    setMinimumSize(128, 400);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_listView);
    setLayout(verticalLayout);
}

void ItemSelectorWidget::setModel(SessionModel *model)
{
    if(model == m_model)
        return;

    disconnectModel();
    m_model = model;
    connectModel();
}

QItemSelectionModel *ItemSelectorWidget::selectionModel()
{
    return m_listView->selectionModel();
}

void ItemSelectorWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    QModelIndexList indexes = selected.indexes();
    SessionItem *selectedItem(0);
    if(indexes.size()) {
        selectedItem = m_model->itemForIndex(indexes.back());
        qDebug() << "ItemSelectorWidget::onSelectionChanged" << selectedItem->displayName();
    }
    emit selectionChanged(selectedItem);
}

void ItemSelectorWidget::connectModel()
{
    if(!m_model)
        return;

    m_listView->setModel(m_model);

    connect(m_listView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
            this,
            SLOT(onSelectionChanged(const QItemSelection&, const QItemSelection&)),
            Qt::UniqueConnection
    );

}

void ItemSelectorWidget::disconnectModel()
{
    m_listView->setModel(0);
    m_model = 0;
}
