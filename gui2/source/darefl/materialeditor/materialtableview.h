// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALTABLEVIEW_H
#define DAREFL_MATERIALEDITOR_MATERIALTABLEVIEW_H

#include <QTableView>
#include <darefl/darefl_export.h>

namespace DaRefl {

//! Extension of QTableView for material editing.
//! Provide better user experinece while navigating between cells.
//! Part of MaterialTableWidget.

class DAREFLCORE_EXPORT MaterialTableView : public QTableView {
public:
    using QTableView::QTableView;
    ~MaterialTableView() override;

    void setModel(QAbstractItemModel* model) override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers) override;

private:
    bool isTextField(const QModelIndex& index) const;
    bool isKeyboardEditable(const QModelIndex& index) const;
};

} // namespace DaRefl

#endif // DAREFL_MATERIALEDITOR_MATERIALTABLEVIEW_H
