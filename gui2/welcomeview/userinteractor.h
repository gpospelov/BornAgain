//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/welcomeview/userinteractor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_WELCOMEVIEW_USERINTERACTOR_H
#define BORNAGAIN_GUI2_WELCOMEVIEW_USERINTERACTOR_H

#include "darefl_export.h"
#include <string>

class QWidget;

namespace ModelView {
enum class SaveChangesAnswer;
}

namespace gui2 {

class RecentProjectSettings;

//! Provide save/discard/cancel and similar dialogs on user request.
//! Intended to work in pair with ProjectManagerDecorator.

class DAREFLCORE_EXPORT UserInteractor {
public:
    UserInteractor(RecentProjectSettings* settings, QWidget* parent);

    std::string onSelectDirRequest();

    std::string onCreateDirRequest();

    ModelView::SaveChangesAnswer onSaveChangesRequest();

private:
    std::string selectDir() const;

    RecentProjectSettings* m_settings{nullptr};
    QWidget* m_parent{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_WELCOMEVIEW_USERINTERACTOR_H
