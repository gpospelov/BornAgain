//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/welcomeview/userinteractor.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/welcomeview/userinteractor.h"
#include "gui2/welcomeview/recentprojectsettings.h"
#include "mvvm/project/project_types.h"
#include "mvvm/project/projectutils.h"
#include "mvvm/utils/fileutils.h"
#include <QFileDialog>
#include <QMessageBox>
#include <map>

using namespace ModelView;

namespace {
//! Map of standard Qt answers to what ProjectManager expects.
std::map<QMessageBox::StandardButton, SaveChangesAnswer> answer_map()
{
    std::map<QMessageBox::StandardButton, SaveChangesAnswer> result = {
        {QMessageBox::Save, SaveChangesAnswer::SAVE},
        {QMessageBox::Discard, SaveChangesAnswer::DISCARD},
        {QMessageBox::Cancel, SaveChangesAnswer::CANCEL}};
    return result;
}
} // namespace

namespace gui2 {

UserInteractor::UserInteractor(RecentProjectSettings* settings, QWidget* parent)
    : m_settings(settings), m_parent(parent)
{
}

//! Returns directory on disk selected by the user via QFileDialog.
//! Checks if selected directory can be the project directory.

std::string UserInteractor::onSelectDirRequest()
{
    auto dirname = selectDir();

    if (dirname.empty()) // no valid selection
        return {};

    if (!ModelView::ProjectUtils::IsPossibleProjectDir(dirname)) {
        QMessageBox msgBox;
        msgBox.setText(
            "Selected directory doesn't look like a project directory, choose another one");
        msgBox.exec();
        return {};
    }

    return dirname;
}

//! Returns new directory on disk created by the user via QFileDialog.

std::string UserInteractor::onCreateDirRequest()

{
    auto dirname = selectDir();

    if (dirname.empty()) // no valid selection
        return {};

    if (!ModelView::Utils::is_empty(dirname)) {
        QMessageBox msgBox;
        msgBox.setText("The selected directory is not empty, choose another one.");
        msgBox.exec();
        return {};
    }

    return dirname;
}

//! Returns save/cancel/discard changes choice provided by the user.

SaveChangesAnswer UserInteractor::onSaveChangesRequest()
{
    static auto translate = answer_map();

    QMessageBox msgBox;
    msgBox.setText("The project has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    auto ret = static_cast<QMessageBox::StandardButton>(msgBox.exec());
    return translate[ret];
}

//! Summon dialog to select directory on disk. If selection is not empty,
//! save parent directory for later re-use.

std::string UserInteractor::selectDir() const
{
    QString dirname = QFileDialog::getExistingDirectory(
        m_parent, "Select directory", m_settings->currentWorkdir(),
        QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    if (!dirname.isEmpty())
        m_settings->updateWorkdirFromSelection(dirname);

    return dirname.toStdString();
}

} // namespace gui2
