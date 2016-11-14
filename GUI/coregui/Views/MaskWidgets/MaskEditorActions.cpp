// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorActions.cpp
//! @brief     Implement class MaskEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskEditorActions.h"
#include "MaskItems.h"
#include "SessionModel.h"
#include <QAction>
#include <QDebug>
#include <QItemSelectionModel>
#include <QMenu>

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

    // Actions for top toolbar
    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, SIGNAL(triggered()), this, SIGNAL(resetViewRequest()));

    m_savePlotAction = new QAction(this);
    m_savePlotAction->setText("Save");
    m_savePlotAction->setIcon(QIcon(":/images/toolbar16light_save.svg"));
    m_savePlotAction->setToolTip("Save Plot");
    connect(m_savePlotAction, SIGNAL(triggered()), this, SIGNAL(savePlotRequest()));

    m_togglePanelAction = new QAction(this);
    m_togglePanelAction->setText("Properties");
    m_togglePanelAction->setIcon(QIcon(":/images/toolbar16light_propertypanel.svg"));
    m_togglePanelAction->setToolTip("Toggle Property Panel");
    connect(m_togglePanelAction, SIGNAL(triggered()), this, SIGNAL(propertyPanelRequest()));
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

QAction *MaskEditorActions::sendToBackAction()
{
    return m_sendToBackAction;
}

QAction *MaskEditorActions::bringToFrontAction()
{
    return m_bringToFrontAction;
}

QList<QAction *> MaskEditorActions::topToolBarActions()
{
    return QList<QAction*>() << m_resetViewAction << m_savePlotAction << m_togglePanelAction;
}

//! Constructs MaskItem context menu following the request from MaskGraphicsScene
//! or MaskEditorInfoPanel
void MaskEditorActions::onItemContextMenuRequest(const QPoint &point)
{
    QMenu menu;
    initItemContextMenu(menu);
    menu.exec(point);
    setAllActionsEnabled(true);
}

//! Performs switch of mask value for all selected items (true -> false, false -> true)
void MaskEditorActions::onToggleMaskValueAction()
{
    Q_ASSERT(m_maskModel);
    Q_ASSERT(m_selectionModel);
    foreach(QModelIndex itemIndex, m_selectionModel->selectedIndexes()) {
        if(SessionItem *item =  m_maskModel->itemForIndex(itemIndex)) {
            bool old_value = item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
            item->setItemValue(MaskItem::P_MASK_VALUE, !old_value);
        }
    }
}

void MaskEditorActions::onBringToFrontAction()
{
    changeMaskStackingOrder(MaskEditorFlags::BRING_TO_FRONT);
}

void MaskEditorActions::onSendToBackAction()
{
    changeMaskStackingOrder(MaskEditorFlags::SEND_TO_BACK);
}

void MaskEditorActions::onDeleteMaskAction()
{
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
    if(!m_maskModel || !m_selectionModel) return;

    int change_in_row(0);
    if(value == MaskEditorFlags::BRING_TO_FRONT) change_in_row = -1;
    if(value == MaskEditorFlags::SEND_TO_BACK) change_in_row = 2;

    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    foreach(QModelIndex itemIndex, indexes) {
        if(SessionItem *item =  m_maskModel->itemForIndex(itemIndex)) {
            int new_row = itemIndex.row() + change_in_row;
            if(new_row >= 0 && new_row <= m_maskModel->rowCount(m_rootIndex)) {
                SessionItem *newItem = m_maskModel->moveParameterizedItem(
                            item,m_maskModel->itemForIndex(m_rootIndex), new_row);
                m_selectionModel->select(m_maskModel->indexOfItem(newItem),
                                         QItemSelectionModel::Select);
            }
        }
    }
}

//! Returns true if at least one of MaskItems in the selection can be moved one level up
//! (Naturally, it is always true, if selection contains more than one item. If selection contains
//! only one item, the result will depend on position of item on the stack.
//! Top item can't be moved up. Used to disable corresponding context menu line.)
bool MaskEditorActions::isBringToFrontPossible() const
{
    bool result(false);
    QModelIndexList indexes = m_selectionModel->selectedIndexes();
    if(indexes.size() == 1 && indexes.front().row() != 0) result=true;
    return result;
}

//! Returns true if at least one of MaskItems in the selection can be moved one level down.
bool MaskEditorActions::isSendToBackPossible() const
{
    bool result(false);
    QModelIndexList indexes = m_selectionModel->selectedIndexes();
    if(indexes.size() == 1) {
        SessionItem *item = m_maskModel->itemForIndex(indexes.front());
        if(indexes.front().row() != item->parent()->rowCount() -1) result = true;
    }
    return result;
}

void MaskEditorActions::setAllActionsEnabled(bool value)
{
    m_sendToBackAction->setEnabled(value);
    m_bringToFrontAction->setEnabled(value);
    m_toggleMaskValueAction->setEnabled(value);
    m_deleteMaskAction->setEnabled(value);
}

//! Init external context menu with currently defined actions.
//! Triggered from MaskGraphicsScene of MaskEditorInfoPanel (QListView)
void MaskEditorActions::initItemContextMenu(QMenu &menu)
{
    if(!m_rootIndex.isValid()) return;

    Q_ASSERT(m_maskModel);
    Q_ASSERT(m_selectionModel);

    if(m_selectionModel->selectedIndexes().isEmpty()) {
        setAllActionsEnabled(false);
    }
    m_sendToBackAction->setEnabled(isSendToBackPossible());
    m_bringToFrontAction->setEnabled(isBringToFrontPossible());

    menu.addAction(m_toggleMaskValueAction);
    menu.addAction(m_bringToFrontAction);
    menu.addAction(m_sendToBackAction);
    menu.addSeparator();
    menu.addAction(m_deleteMaskAction);
}
