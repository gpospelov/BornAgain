// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditorWidget.cpp
//! @brief     Implements class MaterialEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaterialEditorWidget.h"
#include "MaterialEditorToolBar.h"
#include "ComponentEditor.h"
#include "MaterialModel.h"
#include <QListView>
#include <QSplitter>
#include <QVBoxLayout>

MaterialEditorWidget::MaterialEditorWidget(MaterialModel *materialModel, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(materialModel)
    , m_toolBar(new MaterialEditorToolBar(materialModel, this))
    , m_splitter(new QSplitter)
    , m_listView(new QListView)
    , m_componentEditor(new ComponentEditor)
{
    setWindowTitle("MaterialEditorWidget");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    m_splitter->addWidget(m_listView);
    m_splitter->addWidget(m_componentEditor);

    layout->addWidget(m_toolBar);
    layout->addWidget(m_splitter);

    setLayout(layout);

    init_views();
}

QItemSelectionModel *MaterialEditorWidget::getSelectionModel()
{
    Q_ASSERT(m_listView);
    return m_listView->selectionModel();
}

void MaterialEditorWidget::onSelectionChanged(const QItemSelection &selected,
                                              const QItemSelection &)
{
    QModelIndexList indices = selected.indexes();

    if(indices.isEmpty()) {
        m_componentEditor->setItem(0);
    } else {
        if(SessionItem *item = m_materialModel->itemForIndex(indices.at(0))) {
            m_componentEditor->setItem(item);
        }
    }
}

//! Context menu reimplemented to supress default menu
void MaterialEditorWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}


void MaterialEditorWidget::init_views()
{
    m_listView->setModel(m_materialModel);
    m_listView->setMovement(QListView::Static);
    m_listView->setMinimumWidth(50);
    m_listView->setMaximumWidth(220);
    m_listView->setSpacing(5);

    m_toolBar->setSelectionModel(getSelectionModel());

    connect(getSelectionModel(),
            SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
            this,
            SLOT(onSelectionChanged(const QItemSelection&, const QItemSelection&)),
            Qt::UniqueConnection
    );


    // making first material selected
    if (!getSelectionModel()->hasSelection()) {
        QModelIndex itemIndex = m_materialModel->index(0, 0, QModelIndex());
        getSelectionModel()->select(itemIndex, QItemSelectionModel::Select);
    }


}
