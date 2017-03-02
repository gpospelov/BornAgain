// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpacePanel.cpp
//! @brief     Implements class RealSpacePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealSpacePanel.h"
#include "mainwindow_constants.h"
#include "ComponentBoxEditor.h"
#include "FilterPropertyProxy.h"
#include "SampleModel.h"
#include <QTreeView>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QDebug>

RealSpacePanel::RealSpacePanel(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_componentEditor(new ComponentEditor)
    , m_model(nullptr)
    , m_proxy(nullptr)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(m_treeView);
    layout->addWidget(m_componentEditor);

    setLayout(layout);


}

void RealSpacePanel::setModel(SampleModel* model)
{
    m_model = model;

    delete m_proxy;
    m_proxy = new FilterPropertyProxy(1, this);
    m_proxy->setSourceModel(model);
    m_treeView->setModel(m_proxy);
    m_treeView->setAttribute(Qt::WA_MacShowFocusRect, false);

    m_treeView->expandAll();

    connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)),
            m_treeView, SLOT(expandAll()), Qt::UniqueConnection);

    connect(m_treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this, SLOT(onSelectionChanged(QItemSelection, QItemSelection)), Qt::UniqueConnection);

}

QSize RealSpacePanel::sizeHint() const
{
    return QSize(Constants::hint_panel_width*1.3, 256);

}

QSize RealSpacePanel::minimumSizeHint() const
{
    return QSize(Constants::hint_panel_width*1.3, 63);
}

void RealSpacePanel::onSelectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    qDebug() << "RealSpacePanel::onSelectionChanged";
    Q_ASSERT(m_proxy);
    Q_ASSERT(m_model);
    QModelIndexList indices = selected.indexes();

    if(indices.size()) {
        QModelIndex index = m_proxy->mapToSource(indices.back());
        SessionItem* item = m_model->itemForIndex(index);
        Q_ASSERT(item);
        m_componentEditor->setItem(item, item->modelType());
    } else {
        m_componentEditor->setItem(0);
    }
}
