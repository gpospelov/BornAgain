// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SamplePropertyWidget.cpp
//! @brief     Implements class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SamplePropertyWidget.h"
#include "ComponentEditor.h"
#include "SessionItem.h"
#include <QDebug>
#include <QItemSelection>
#include <QModelIndexList>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>

SamplePropertyWidget::SamplePropertyWidget(QItemSelectionModel *selection_model, QWidget *parent)
    : QWidget(parent)
    , m_selection_model(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("SamplePropertyWidget"));

    setSelectionModel(selection_model);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_propertyEditor = new ComponentEditor;

    mainLayout->addWidget(m_propertyEditor);
    setLayout(mainLayout);
}

void SamplePropertyWidget::setSelectionModel(QItemSelectionModel *selection_model)
{
    if(selection_model != m_selection_model) {
        if(m_selection_model)
            disconnect(m_selection_model,
                    SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                    this,
                    SLOT(selectionChanged(QItemSelection,QItemSelection)) );

        m_selection_model = selection_model;

        connect(m_selection_model,
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this,
                SLOT(selectionChanged(QItemSelection,QItemSelection)) );

    }
}

// show property of currently selected object (triggered by the graphics scene)
// if more than one object is selected, show only last selected
void SamplePropertyWidget::selectionChanged(const QItemSelection & selected,
                                            const QItemSelection & deselected)
{
    (void)deselected;
    QModelIndexList indices = selected.indexes();

    if(indices.size()) {
        QSortFilterProxyModel *proxy = dynamic_cast<QSortFilterProxyModel*>(const_cast<QAbstractItemModel*>(indices[0].model()));
        QModelIndex index = indices.back();
        if (proxy) {
            index = proxy->mapToSource(index);
        }
        SessionItem *item = static_cast<SessionItem *>(
                index.internalPointer());
//        m_propertyEditor->setItem(item, item->modelType());
        if (item)
            m_propertyEditor->setItem(item, item->modelType());
    } else {
        m_propertyEditor->setItem(0);
    }
}
