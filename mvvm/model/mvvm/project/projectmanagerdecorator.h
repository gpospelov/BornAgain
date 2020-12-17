//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/project/projectmanagerdecorator.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_PROJECTMANAGERDECORATOR_H
#define BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_PROJECTMANAGERDECORATOR_H

#include "mvvm/interfaces/projectmanagerinterface.h"
#include <memory>

namespace ModelView {

struct ProjectContext;
struct UserInteractionContext;

//! Decorator for ProjectManager to provide interaction with the user on open/save-as requests.
//! It relies on the same interface and adds additional logic related to "unsaved" data.

//! For example, on createNewProject it will check if previous project is saved, and will
//! call external dialog save/discard/cancel via provided callback.

class MVVM_MODEL_EXPORT ProjectManagerDecorator : public ProjectManagerInterface {
public:
    ProjectManagerDecorator(const ProjectContext& project_context,
                            const UserInteractionContext& user_context);

    ~ProjectManagerDecorator() override;
    ProjectManagerDecorator(const ProjectManagerDecorator& other) = delete;
    ProjectManagerDecorator& operator=(const ProjectManagerDecorator& other) = delete;

    bool createNewProject(const std::string& dirname = {}) override;

    bool saveCurrentProject() override;

    bool saveProjectAs(const std::string& dirname = {}) override;

    bool openExistingProject(const std::string& dirname = {}) override;

    std::string currentProjectDir() const override;

    bool isModified() const override;

    bool closeCurrentProject() const override;

private:
    struct ProjectManagerImpl;
    std::unique_ptr<ProjectManagerImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_PROJECTMANAGERDECORATOR_H
