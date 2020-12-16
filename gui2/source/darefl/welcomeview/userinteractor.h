// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_USERINTERACTOR_H
#define DAREFL_WELCOMEVIEW_USERINTERACTOR_H

#include <darefl/darefl_export.h>
#include <string>

class QWidget;

namespace ModelView {
enum class SaveChangesAnswer;
}

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_WELCOMEVIEW_USERINTERACTOR_H
