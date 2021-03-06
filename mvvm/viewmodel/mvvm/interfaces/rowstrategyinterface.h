//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/interfaces/rowstrategyinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H

#include "mvvm/viewmodel_export.h"
#include <QStringList>
#include <memory>
#include <vector>

namespace ModelView {

class SessionItem;
class ViewItem;

//! Base class to construct row of ViewItem's from given SessionItem.
//! Used in context of AbstractViewModel while exposing SessionModel to Qt.

class MVVM_VIEWMODEL_EXPORT RowStrategyInterface {
public:
    virtual ~RowStrategyInterface() = default;

    virtual QStringList horizontalHeaderLabels() const = 0;

    virtual std::vector<std::unique_ptr<ViewItem>> constructRow(SessionItem*) = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
