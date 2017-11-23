// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeView.h
//! @brief     Defines class ComponentTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTTREEVIEW_H
#define COMPONENTTREEVIEW_H

#include "ComponentView.h"

class QTreeView;
class SessionModel;
class SessionModelDelegate;
class ComponentProxyModel;
class QModelIndex;
class SessionItem;
class QStandardItemModel;

//! Component property tree for SessionItems.
//! Shows only PropertyItems and current items of GroupProperties.

class BA_CORE_API_ ComponentTreeView : public ComponentView
{
    Q_OBJECT
public:
    ComponentTreeView(QWidget* parent = nullptr);

    void setItem(SessionItem* item);
    void setItemIntern(SessionItem* item, bool show_root_item = true);
    void clearEditor();

    void setModel(SessionModel* model);
    void setRootIndex(const QModelIndex& index, bool show_root_item = true);

    QTreeView* treeView();

    void setHeaderHidden(bool hide);
    void setShowRootItem(bool show);

private:
    QTreeView* m_tree;
    SessionModelDelegate* m_delegate;
    ComponentProxyModel* m_proxyModel;
    QStandardItemModel* m_placeHolderModel;
    bool m_show_root_item;
};

#endif  //  COMPONENTTREEVIEW_H
