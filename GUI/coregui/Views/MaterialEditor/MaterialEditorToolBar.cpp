// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditorToolBar.cpp
//! @brief     Implements class MaterialEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialEditorToolBar.h"
#include "MaterialItem.h"
#include "MaterialModel.h"
#include <QAction>
#include <QDebug>
#include <QItemSelectionModel>
#include <QListView>
#include <QMenu>
#include <QVariant>

namespace {
const int toolbar_icon_size = 32;
}

MaterialEditorToolBar::MaterialEditorToolBar(MaterialModel *materialModel,
                                             QWidget *parent)
    : QToolBar(parent)
    , m_materialModel(materialModel)
    , m_selectionModel(0)
    , m_newMaterialAction(0)
    , m_cloneMaterialAction(0)
    , m_removeMaterialAction(0)

{
    setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

    m_newMaterialAction = new QAction(QStringLiteral("Add new material"), parent);
    m_newMaterialAction->setIcon(QIcon(":/images/toolbar32dark_newitem.svg"));
    m_newMaterialAction->setToolTip(QStringLiteral("Add new material"));
    connect(m_newMaterialAction, SIGNAL(triggered()), this,
            SLOT(onNewMaterialAction()));
    addAction(m_newMaterialAction);

    m_cloneMaterialAction = new QAction(QStringLiteral("Clone material"), parent);
    m_cloneMaterialAction->setIcon(
        QIcon(":/images/toolbar32dark_cloneitem.svg"));
    m_cloneMaterialAction->setToolTip(QStringLiteral("Clone selected material"));
    connect(m_cloneMaterialAction, SIGNAL(triggered()), this,
            SLOT(onCloneMaterialAction()));
    addAction(m_cloneMaterialAction);

    m_removeMaterialAction = new QAction(QStringLiteral("Remove selected material"), parent);
    m_removeMaterialAction->setIcon(QIcon(":/images/toolbar32dark_remove.svg"));
    m_removeMaterialAction->setToolTip(QStringLiteral("Remove selected material"));
    connect(m_removeMaterialAction, SIGNAL(triggered()), this,
            SLOT(onRemoveMaterialAction()));
    addAction(m_removeMaterialAction);
}

void MaterialEditorToolBar::setSelectionModel(QItemSelectionModel *selectionModel)
{
    m_selectionModel = selectionModel;
}

void MaterialEditorToolBar::onCustomContextMenuRequested(const QPoint &point)
{
    QListView *listView = qobject_cast<QListView *>(sender());
    Q_ASSERT(listView);
    QPoint global = listView->mapToGlobal(point);

    QMenu menu;
    initItemContextMenu(menu);
    menu.exec(global);
//    setAllActionsEnabled(true);

}

void MaterialEditorToolBar::onNewMaterialAction()
{
    m_materialModel->addMaterial("unnamed");
}

void MaterialEditorToolBar::onCloneMaterialAction()
{
    QModelIndexList selected = m_selectionModel->selectedIndexes();
    if(selected.size()) {
        QModelIndex selectedIndex = selected.front();
        m_materialModel->cloneMaterial(selectedIndex);
    }
}

void MaterialEditorToolBar::onRemoveMaterialAction()
{
    Q_ASSERT(m_materialModel);
    Q_ASSERT(m_selectionModel);

    QModelIndexList selected = m_selectionModel->selectedIndexes();
    if(selected.size()) {
        m_materialModel->removeRows(selected.front().row(), 1, selected.back().parent());
    }
}

void MaterialEditorToolBar::initItemContextMenu(QMenu &menu)
{
    menu.addAction(m_newMaterialAction);
    menu.addAction(m_cloneMaterialAction);
    menu.addSeparator();
    menu.addAction(m_removeMaterialAction);

}
