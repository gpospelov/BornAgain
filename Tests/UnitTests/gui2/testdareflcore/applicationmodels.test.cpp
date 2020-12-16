// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "google_test.h"
#include "gui2/model/applicationmodels.h"
#include "mvvm/factories/modeldocumentfactory.h"
#include "mvvm/project/project.h"
#include "mvvm/project/project_types.h"

using namespace ModelView;

//! Tests of ApplicationModels

class ApplicationModelsTest : public FolderBasedTest {
public:
    ApplicationModelsTest() : FolderBasedTest("test_ApplicationModelsTest") {}

    ~ApplicationModelsTest();
};

ApplicationModelsTest::~ApplicationModelsTest() = default;

//! Testing that nothing is crashing on project save and load.

TEST_F(ApplicationModelsTest, saveLoad) {
    auto project_dir = createEmptyDir("Untitled1");

    gui2::ApplicationModels models, loadedModels;

    {
        ProjectContext context1;
        context1.m_models_callback = [&models]() { return models.persistent_models(); };
        Project project1(context1);
        project1.save(project_dir);
    }

    {
        ProjectContext context2;
        context2.m_models_callback = [&loadedModels]() { return loadedModels.persistent_models(); };
        Project project2(context2);
        project2.load(project_dir);
    }
}
