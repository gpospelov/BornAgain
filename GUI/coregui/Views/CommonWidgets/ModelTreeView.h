// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ModelTreeView.h
//! @brief     Defines class ModelTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MODELTREEVIEW_H
#define MODELTREEVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class QTreeView;
class SessionModel;
class SessionDecorationModel;
class QAbstractItemDelegate;

//! Equivalent of QTreeView for SessionModel allowing to add visual decorations to the tree.
//! Additionaly provides expand/collapse utility methods.

class BA_CORE_API_ ModelTreeView : public QWidget
{
    Q_OBJECT
public:
    ModelTreeView(QWidget* parent, SessionModel* model);

    void setItemDelegate(QAbstractItemDelegate* delegate);

public slots:
    void toggleExpanded();
    void setExpanded(bool expanded);
    bool isExpanded() const { return m_is_expanded; }

private:
    QTreeView* m_tree;
    SessionDecorationModel* m_decorationProxy;
    bool m_is_expanded;
};


#endif  // MODELTREEVIEW_H
