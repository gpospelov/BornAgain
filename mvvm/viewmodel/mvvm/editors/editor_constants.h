//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/editor_constants.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_EDITOR_CONSTANTS_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_EDITOR_CONSTANTS_H

//! @file editor_constants.h
//! Collection of constants specific for cell editing.

#include <string>

namespace ModelView {

namespace Constants {

const std::string BoolEditorType = "BoolEditor";
const std::string ColorEditorType = "ColorEditor";
const std::string ComboPropertyEditorType = "ComboPropertyEditor";
const std::string DoubleEditorType = "DoubleEditor";
const std::string ExternalPropertyEditorType = "ExternalPropertyEditor";
const std::string IntegerEditorType = "IntegerEditor";
const std::string ScientficDoubleEditorType = "ScientficDoubleEditor";
const std::string ScientficSpinBoxEditorType = "ScientficSpinBoxEditor";
const std::string SelectableComboPropertyEditorType = "SelectableComboPropertyEditor";

const int default_double_decimals = 4; //! number of digits after decimal points

} // namespace Constants

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_EDITOR_CONSTANTS_H
