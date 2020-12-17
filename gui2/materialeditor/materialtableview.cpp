//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/materialeditor/materialtableview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/materialeditor/materialtableview.h"
#include <QHeaderView>
#include <QMouseEvent>

namespace gui2 {

MaterialTableView::~MaterialTableView() = default;

void MaterialTableView::setModel(QAbstractItemModel* model)
{
    QTableView::setModel(model);
    setAlternatingRowColors(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void MaterialTableView::keyPressEvent(QKeyEvent* event)
{
    if (!event || event->key() != Qt::Key_Return || state() == QAbstractItemView::EditingState)
        return QTableView::keyPressEvent(event);

    const QModelIndex index = currentIndex();
    if (isKeyboardEditable(index))
        edit(index);
}

QModelIndex MaterialTableView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
    const QModelIndex current_index = currentIndex();
    bool filtered_action = cursorAction == QAbstractItemView::MoveNext
                           || cursorAction == QAbstractItemView::MovePrevious;

    if (!current_index.isValid() || !isTextField(current_index) || !filtered_action)
        return QTableView::moveCursor(cursorAction, modifiers);

    QModelIndex next = current_index;
    do {
        setCurrentIndex(next);
        next = QTableView::moveCursor(cursorAction, modifiers);
    } while (!isTextField(next));
    return next;
}

bool MaterialTableView::isTextField(const QModelIndex& index) const
{
    return index.isValid() && index.column() > 1; // color and checkbox are not keyboard editable
}

bool MaterialTableView::isKeyboardEditable(const QModelIndex& index) const
{
    return index.isValid();
}

} // namespace gui2
