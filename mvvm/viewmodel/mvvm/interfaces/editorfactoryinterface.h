//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/interfaces/editorfactoryinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_EDITORFACTORYINTERFACE_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_EDITORFACTORYINTERFACE_H

#include "mvvm/viewmodel_export.h"
#include <memory>
#include <string>

class QModelIndex;
class QWidget;

namespace ModelView {

class CustomEditor;

//! Interface for custom editor factory.
//! Intended for editor construction in cells of tables and trees in the context of delegate.

class MVVM_VIEWMODEL_EXPORT EditorFactoryInterface {
public:
    virtual ~EditorFactoryInterface() = default;

    virtual std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_EDITORFACTORYINTERFACE_H
