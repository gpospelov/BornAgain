// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpacePanel.cpp
//! @brief     Implements class RealSpacePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpacePanel.h"
#include "mainwindow_constants.h"
#include "ComponentEditor.h"
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

    connect(m_model, &SampleModel::rowsInserted, this, [=](){m_treeView->expandAll();});

    connect(m_treeView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &RealSpacePanel::onSelectionChanged, Qt::UniqueConnection);
}

QSize RealSpacePanel::sizeHint() const
{
    return QSize(static_cast<int>(Constants::hint_panel_width*1.3), 256);

}

QSize RealSpacePanel::minimumSizeHint() const
{
    return QSize(static_cast<int>(Constants::hint_panel_width*1.3), 63);
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
        m_componentEditor->setItem(item);
        emit selectionChanged(index);
    } else {
        m_componentEditor->setItem(nullptr);
        emit selectionChanged(QModelIndex());
    }
}
