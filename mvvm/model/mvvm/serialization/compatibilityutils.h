//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/compatibilityutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_COMPATIBILITYUTILS_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_COMPATIBILITYUTILS_H

//! @file compatibilityutils.h
//! @brief Place for utils to fix back compatibility of serialized projects.

#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class SessionItemData;
class SessionItemContainer;
class TagInfo;

namespace Compatibility {

//! Returns `true` if given TagInfo is compatible with given container.
//! See explanations in the code.

MVVM_MODEL_EXPORT
bool IsCompatibleUniversalTag(const SessionItemContainer& container, const TagInfo& taginfo);

//! Returns `true` if given TagInfo is a single property tag which is compatible with given
//! container. See more explanations in the code.

MVVM_MODEL_EXPORT
bool IsCompatibleSinglePropertyTag(const SessionItemContainer& container, const TagInfo& taginfo);

//! Returns `true` if given TagInfo is a tag from GroupItem which is compatible with given
//! container. See more explanations in the code.

MVVM_MODEL_EXPORT bool IsCompatibleGroupTag(const SessionItemContainer& container,
                                            const TagInfo& taginfo);

} // namespace Compatibility

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_COMPATIBILITYUTILS_H
