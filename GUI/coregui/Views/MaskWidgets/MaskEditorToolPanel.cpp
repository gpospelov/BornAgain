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
#include <QVBoxLayout>
#include <QListView>
#include <QItemSelection>
#include <QModelIndexList>
#include <QDebug>

MaskEditorToolPanel::MaskEditorToolPanel(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView)
    , m_propertyEditor(new AwesomePropertyEditor)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setObjectName(QLatin1String("MaskEditorToolPanel"));

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

    connect(m_listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection, QItemSelection)));

}

void MaskEditorToolPanel::onSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    qDebug() << "MaskEditorToolPanel::onSessionSelectionChanged:";
    if(!m_model) return;

    QModelIndexList indices = selected.indexes();
    if(indices.size()) {
        ParameterizedItem *item = m_model->itemForIndex(indices.front());
        m_propertyEditor->setItem(item);
    }


}
