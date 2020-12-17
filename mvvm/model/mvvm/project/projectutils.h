//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/project/projectutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_PROJECTUTILS_H
#define BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_PROJECTUTILS_H

#include "mvvm/model_export.h"
#include <memory>
#include <string>
#include <vector>

namespace ModelView {

class SessionModel;
class ProjectInterface;
struct ProjectContext;

//! Collection of utility functions to handle project saving and loading.

namespace ProjectUtils {

MVVM_MODEL_EXPORT std::string SuggestFileName(const SessionModel& model);

MVVM_MODEL_EXPORT bool IsPossibleProjectDir(const std::string& project_dir);

MVVM_MODEL_EXPORT std::unique_ptr<ProjectInterface>
CreateUntitledProject(const ProjectContext& context);

MVVM_MODEL_EXPORT std::string ProjectWindowTitle(const ProjectInterface& project);

MVVM_MODEL_EXPORT std::string ProjectWindowTitle(const std::string& project_dir, bool is_modified);

} // namespace ProjectUtils

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_PROJECTUTILS_H
