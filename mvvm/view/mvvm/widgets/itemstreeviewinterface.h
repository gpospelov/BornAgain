//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/itemstreeviewinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H

#include "mvvm/view_export.h"
#include <QWidget>

class QTreeView;

namespace ModelView {

class SessionModel;

//! Saves and restores list of SessionModel's to/from disk using json format.

class MVVM_VIEW_EXPORT ItemsTreeViewInterface : public QWidget {
    Q_OBJECT

public:
    virtual void setSessionModel(SessionModel* model) = 0;

    virtual QTreeView* treeView() const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H
