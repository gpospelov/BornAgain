// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorActions.cpp
//! @brief     Implement class MaskEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorActions.h"
#include "SessionModel.h"
#include "MaskItems.h"
#include <QItemSelectionModel>
#include <QAction>
#include <QMenu>
#include <QDebug>

MaskEditorActions::MaskEditorActions(QWidget *parent)
    : QObject(parent)
    , m_maskModel(0)
    , m_selectionModel(0)
{

    m_toggleMaskValueAction = new QAction(QStringLiteral("Toggle mask value"), parent);
    connect(m_toggleMaskValueAction, SIGNAL(triggered()), this, SLOT(onToggleMaskValueAction()));

    m_bringToFrontAction = new QAction(QStringLiteral("Rise mask up"), parent);
    m_bringToFrontAction->setIcon(QIcon(":/MaskWidgets/images/maskeditor_bringtofront.svg"));
    m_bringToFrontAction->setToolTip("Rise selected mask one level up (PgUp)");
    m_bringToFrontAction->setShortcuts(QKeySequence::MoveToPreviousPage);
    connect(m_bringToFrontAction, SIGNAL(triggered()), this, SLOT(onBringToFrontAction()));

    m_sendToBackAction = new QAction(QStringLiteral("Lower mask down"), parent);
    m_sendToBackAction->setIcon(QIcon(":/MaskWidgets/images/maskeditor_sendtoback.svg"));
    m_sendToBackAction->setToolTip("Lower selected mask one level down (PgDown)");
    m_sendToBackAction->setShortcuts(QKeySequence::MoveToNextPage);
    connect(m_sendToBackAction, SIGNAL(triggered()), this, SLOT(onSendToBackAction()));

    m_deleteMaskAction = new QAction(QStringLiteral("Remove mask"), parent);
    m_deleteMaskAction->setToolTip("Remove selected mask (Del)");
    m_deleteMaskAction->setShortcuts(QKeySequence::Delete);
    parent->addAction(m_deleteMaskAction);
    connect(m_deleteMaskAction, SIGNAL(triggered()), this, SLOT(onDeleteMaskAction()));

}

void MaskEditorActions::setModel(SessionModel *maskModel, const QModelIndex &rootIndex)
{
    m_maskModel = maskModel;
    m_rootIndex = rootIndex;
}

void MaskEditorActions::setSelectionModel(QItemSelectionModel *selectionModel)
{
    m_selectionModel = selectionModel;
}

QAction *MaskEditorActions::getSendToBackAction()
{
    return m_sendToBackAction;
}

QAction *MaskEditorActions::getBringToFrontAction()
{
    return m_bringToFrontAction;
}

void MaskEditorActions::onItemContextMenuRequest(const QPoint &point)
{
    QMenu menu;
    initItemContextMenu(menu);
    menu.exec(point);
}

//! Performs switch of mask value for all selected items
void MaskEditorActions::onToggleMaskValueAction()
{
    qDebug() << "MaskEditorActions::onToggleMaskValueAction()";
    Q_ASSERT(m_maskModel);
    Q_ASSERT(m_selectionModel);
    foreach(QModelIndex itemIndex, m_selectionModel->selectedIndexes()) {
        if(ParameterizedItem *item =  m_maskModel->itemForIndex(itemIndex)) {
            bool old_value = item->getRegisteredProperty(MaskItem::P_MASK_VALUE).toBool();
            item->setRegisteredProperty(MaskItem::P_MASK_VALUE, !old_value);
        }
    }
}

void MaskEditorActions::onBringToFrontAction()
{
    qDebug() << "MaskEditorActions::onBringToFrontAction()";
    changeMaskStackingOrder(MaskEditorFlags::BRING_TO_FRONT);
}

void MaskEditorActions::onSendToBackAction()
{
    qDebug() << "MaskEditorActions::onSendToBackAction()";
    changeMaskStackingOrder(MaskEditorFlags::SEND_TO_BACK);
}

void MaskEditorActions::onDeleteMaskAction()
{
    qDebug() << "MaskEditorActions::onDeleteMaskAction()";
    Q_ASSERT(m_maskModel);
    Q_ASSERT(m_selectionModel);

    QModelIndexList indexes = m_selectionModel->selectedIndexes();
    while (indexes.size()) {
        m_maskModel->removeRows(indexes.back().row(), 1, indexes.back().parent());
        indexes = m_selectionModel->selectedIndexes();
    }
}

//! Lower mask one level down or rise one level up in the masks stack
void MaskEditorActions::changeMaskStackingOrder(MaskEditorFlags::Stacking value)
{
    Q_ASSERT(m_maskModel);
    Q_ASSERT(m_selectionModel);

    int change_in_row(0);
    if(value == MaskEditorFlags::BRING_TO_FRONT) change_in_row = -1;
    if(value == MaskEditorFlags::SEND_TO_BACK) change_in_row = 2;

    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    foreach(QModelIndex itemIndex, indexes) {
        if(ParameterizedItem *item =  m_maskModel->itemForIndex(itemIndex)) {
            int new_row = itemIndex.row() + change_in_row;
            if(new_row >= 0 && new_row <= m_maskModel->rowCount(m_rootIndex)) {
                ParameterizedItem *newItem = m_maskModel->moveParameterizedItem(
                            item,m_maskModel->itemForIndex(m_rootIndex), new_row);
                m_selectionModel->select(m_maskModel->indexOfItem(newItem),
                                         QItemSelectionModel::Select);
            }
        }
    }
}

//! Init external context menu with currently defined actions.
//! Triggered from MaskGraphicsScene of MaskEditorInfoPanel (QListView)
void MaskEditorActions::initItemContextMenu(QMenu &menu)
{
    Q_ASSERT(m_maskModel);
    Q_ASSERT(m_selectionModel);

    menu.addAction(m_toggleMaskValueAction);
    menu.addAction(m_bringToFrontAction);
    menu.addAction(m_sendToBackAction);
    menu.addSeparator();
    menu.addAction(m_deleteMaskAction);
}
