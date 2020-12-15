// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALTREEVIEW_H
#define DAREFL_MATERIALEDITOR_MATERIALTREEVIEW_H

#include <QTreeView>
#include <darefl/darefl_export.h>

namespace DaRefl
{

//! Extension of QTreeView for material editing.
//! Provide better user experinece while navigating between cells.
//! Part of MaterialTableWidget.

class DAREFLCORE_EXPORT MaterialTreeView : public QTreeView
{
public:
    using QTreeView::QTreeView;

    explicit MaterialTreeView(QWidget* parent = nullptr);
    ~MaterialTreeView() override;

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

#endif // DAREFL_MATERIALEDITOR_MATERIALTREEVIEW_H
