//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/itemstreeview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ITEMSTREEVIEW_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ITEMSTREEVIEW_H

#include "mvvm/view_export.h"
#include <QWidget>
#include <memory>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

namespace ModelView {

class SessionItem;
class ViewModel;
class ViewModelDelegate;

//! Tree view to show items of SessionModel via ViewModel mechanism.
//! Provides notification mechanism for SessionItem selections, use custom delegate.

class MVVM_VIEW_EXPORT ItemsTreeView : public QWidget {
    Q_OBJECT

public:
    explicit ItemsTreeView(QWidget* parent = nullptr);
    ~ItemsTreeView() override;

    QTreeView* treeView();

    void setViewModel(std::unique_ptr<ViewModel> viewModel);

    void setViewModelDelegate(std::unique_ptr<ViewModelDelegate> delegate);

    void setSelected(SessionItem* item);

    void setRootSessionItem(SessionItem* item);

    ViewModel* viewModel() const;

signals:
    void itemSelected(ModelView::SessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView{nullptr};
    std::unique_ptr<ViewModel> m_viewModel;
    std::unique_ptr<ViewModelDelegate> m_delegate;
    bool m_block_selection;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ITEMSTREEVIEW_H
