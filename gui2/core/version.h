// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

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
