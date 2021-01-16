//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/core/version.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_CORE_VERSION_H
#define BORNAGAIN_MVVM_MODEL_MVVM_CORE_VERSION_H

//! @file mvvm/model/mvvm/core/version.h
//! Automatically generated from mvvm_version.h.in

#include <string>

namespace ModelView {

//! Returns major project version.
inline int ProjectVersionMajor()
{
    const int project_version_major = 0;
    return project_version_major;
}

//! Returns minor project version.
inline int ProjectVersionMinor()
{
    const int project_version_minor = 2;
    return project_version_minor;
}

//! Returns patch project version.
inline int ProjectVersionPatch()
{
    const int project_version_path = 0;
    return project_version_path;
}

//! Returns project version string
inline std::string ProjectVersion()
{
    const std::string project_version = "0.2.0";
    return project_version;
}

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_CORE_VERSION_H
