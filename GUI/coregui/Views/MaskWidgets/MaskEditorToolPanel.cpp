// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorToolPanel.cpp
//! @brief     Implements class MaskEditorToolPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorToolPanel.h"
#include "SessionModel.h"
#include "AwesomePropertyEditor.h"
#include "MaskEditorFlags.h"
#include <QVBoxLayout>
#include <QListView>
#include <QItemSelection>
#include <QModelIndexList>
#include <QButtonGroup>
#include <QToolButton>
#include <QPushButton>
#include <QGridLayout>
#include <QDebug>

MaskEditorToolPanel::MaskEditorToolPanel(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView)
    , m_propertyEditor(new AwesomePropertyEditor)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setObjectName(QLatin1String("MaskEditorToolPanel"));

    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_listView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenuRequested(const QPoint &)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_propertyEditor);
    mainLayout->addWidget(m_listView);
    setLayout(mainLayout);

}

void MaskEditorToolPanel::setModel(SessionModel *model, const QModelIndex &root_index)
{
    m_model = model;
    m_listView->setModel(model);
    m_listView->setRootIndex(root_index);
    m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(m_listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection, QItemSelection)));

}

QItemSelectionModel *MaskEditorToolPanel::selectionModel()
{
    Q_ASSERT(m_listView);
    return m_listView->selectionModel();
}

void MaskEditorToolPanel::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    if(selected.size()) {
        m_propertyEditor->setItem(m_model->itemForIndex(selected.indexes().front()));
    } else {
        m_propertyEditor->setItem(0);
    }
}

void MaskEditorToolPanel::onCustomContextMenuRequested(const QPoint &point)
{
    emit itemContextMenuRequest(m_listView->mapToGlobal(point));
}

