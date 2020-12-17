//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/factories/projectmanagerfactory.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/factories/projectmanagerfactory.h"
#include "mvvm/project/project_types.h"
#include "mvvm/project/projectmanagerdecorator.h"

namespace ModelView {
std::unique_ptr<ProjectManagerInterface>
CreateProjectManager(const ProjectContext& project_context,
                     const UserInteractionContext& user_context) {
    return std::make_unique<ProjectManagerDecorator>(project_context, user_context);
}

} // namespace ModelView
