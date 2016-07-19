// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditor.cpp
//! @brief     Implements class MaterialEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialEditor.h"
#include "ComponentEditor.h"
#include "MaterialEditorToolBar.h"
#include "MaterialItem.h"
#include "MaterialModel.h"
#include <QListView>
#include <QSplitter>
#include <QVBoxLayout>

MaterialEditor::MaterialEditor(MaterialModel *materialModel, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(materialModel)
    , m_toolBar(new MaterialEditorToolBar(materialModel, this))
    , m_splitter(new QSplitter)
    , m_listView(new QListView)
    , m_componentEditor(new ComponentEditor)
    , m_model_was_modified(false)
{
    setWindowTitle("MaterialEditorWidget");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);

    m_splitter->addWidget(m_listView);
    m_splitter->addWidget(m_componentEditor);
    m_splitter->setCollapsible(0, false);
    m_splitter->setCollapsible(1, false);

    layout->addWidget(m_toolBar);
    layout->addWidget(m_splitter);

    setLayout(layout);

    init_views();
}

QItemSelectionModel *MaterialEditor::getSelectionModel()
{
    Q_ASSERT(m_listView);
    return m_listView->selectionModel();
}

MaterialItem *MaterialEditor::getSelectedMaterial()
{
    QModelIndexList selected = getSelectionModel()->selectedIndexes();
    if(selected.size()) {
        return m_materialModel->getMaterial(selected.front());
    }
    return nullptr;
}

//! Sets selection corresponding to initial material property
void MaterialEditor::setInitialMaterialProperty(const MaterialProperty &matProperty)
{
    if(MaterialItem *mat = m_materialModel->getMaterial(matProperty)) {
        getSelectionModel()->clearSelection();
        getSelectionModel()->select(m_materialModel->indexOfItem(mat),
                                    QItemSelectionModel::Select);
    }
}

bool MaterialEditor::isModelWasModified() const
{
    return m_model_was_modified;
}

void MaterialEditor::onSelectionChanged(const QItemSelection &selected,
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

void MaterialEditor::onDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)
{
    m_model_was_modified = true;
}

void MaterialEditor::onRowsInserted(const QModelIndex &, int, int)
{
    m_model_was_modified = true;
}

void MaterialEditor::onRowsRemoved(const QModelIndex &, int, int)
{
    m_model_was_modified = true;
}


//! Context menu reimplemented to supress default menu
void MaterialEditor::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}


void MaterialEditor::init_views()
{
    // connecting to the model
    connect(m_materialModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
               this, SLOT(onDataChanged(QModelIndex,QModelIndex,QVector<int>)));
    connect(m_materialModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
               this, SLOT(onRowsInserted(QModelIndex,int,int)));
    connect(m_materialModel, SIGNAL(rowsRemoved(QModelIndex,int,int)),
               this, SLOT(onRowsRemoved(QModelIndex,int,int)));

    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);
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

    connect(m_listView, SIGNAL(customContextMenuRequested(const QPoint &)),
            m_toolBar, SLOT(onCustomContextMenuRequested(const QPoint &)));

}
