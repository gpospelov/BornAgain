// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorPropertyPanel.cpp
//! @brief     Implements class MaskEditorPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorPropertyPanel.h"
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
#include <QLabel>
#include <QDebug>

MaskEditorPropertyPanel::MaskEditorPropertyPanel(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView)
    , m_maskPropertyEditor(new AwesomePropertyEditor)
    , m_plotPropertyEditor(new AwesomePropertyEditor)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setObjectName(QLatin1String("MaskEditorToolPanel"));

    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_listView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onCustomContextMenuRequested(const QPoint &)));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // stack of masks
    QLabel *stackLabel = new QLabel("Mask stack");
    stackLabel->setToolTip("List of created masks representing mask stacking order.");
    mainLayout->addWidget(stackLabel);
    mainLayout->addWidget(m_listView, 3);
    mainLayout->addSpacing(5);

    // mask properties
    QLabel *maskPropertyLabel = new QLabel("Mask properties");
    maskPropertyLabel->setToolTip("Property editor for currently selected mask.");
    mainLayout->addWidget(maskPropertyLabel);
    mainLayout->addWidget(m_maskPropertyEditor, 1);
    mainLayout->addSpacing(5);

    // plot properties
    QLabel *plotPropertyLabel = new QLabel("Plot properties");
    plotPropertyLabel->setToolTip("Plot properties editor");
    mainLayout->addWidget(plotPropertyLabel);
    mainLayout->addWidget(m_plotPropertyEditor, 3);
    setLayout(mainLayout);

}

void MaskEditorPropertyPanel::setModel(SessionModel *model, const QModelIndex &root_index)
{
    m_maskModel = model;
    m_rootIndex = root_index;
    m_listView->setModel(model);
    m_listView->setRootIndex(root_index);
    m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(m_listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection, QItemSelection)));

    m_plotPropertyEditor->setItem(m_maskModel->itemForIndex(m_rootIndex));

}

QItemSelectionModel *MaskEditorPropertyPanel::selectionModel()
{
    Q_ASSERT(m_listView);
    return m_listView->selectionModel();
}

//! Show/Hide panel. When panel is hidden, all property editors are disabled.
void MaskEditorPropertyPanel::setPanelHidden(bool value)
{
    this->setHidden(value);
    if(value) {
        m_maskPropertyEditor->setItem(0);
        m_plotPropertyEditor->setItem(0);
    } else {
        QModelIndexList indexes = selectionModel()->selectedIndexes();
        if(indexes.size()) {
            m_maskPropertyEditor->setItem(m_maskModel->itemForIndex(indexes.front()));
        }
        m_plotPropertyEditor->setItem(m_maskModel->itemForIndex(m_rootIndex));
    }
}

void MaskEditorPropertyPanel::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    if(selected.size()) {
        m_maskPropertyEditor->setItem(m_maskModel->itemForIndex(selected.indexes().front()));
    } else {
        m_maskPropertyEditor->setItem(0);
    }
}

void MaskEditorPropertyPanel::onCustomContextMenuRequested(const QPoint &point)
{
    emit itemContextMenuRequest(m_listView->mapToGlobal(point));
}

