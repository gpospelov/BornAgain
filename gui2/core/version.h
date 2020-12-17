//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/core/version.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_CORE_VERSION_H
#define BORNAGAIN_GUI2_CORE_VERSION_H

//! @file version.h
//! Automatically generated from darefl_version.h.in

#include <string>

namespace gui2 {

//! Returns major project version.
inline int ProjectVersionMajor() {
    const int project_version_major = 0;
    return project_version_major;
}

//! Returns minor project version.
inline int ProjectVersionMinor() {
    const int project_version_minor = 1;
    return project_version_minor;
}

//! Returns patch project version.
inline int ProjectVersionPatch() {
    const int project_version_path = 0;
    return project_version_path;
}

//! Returns project version string
inline std::string ProjectVersion() {
    const std::string project_version = "0.1.0";
    return project_version;
}

} // namespace gui2

#endif // BORNAGAIN_GUI2_CORE_VERSION_H
