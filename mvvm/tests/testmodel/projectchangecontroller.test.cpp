//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testmodel/projectchangecontroller.test.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "mvvm/model/propertyitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/project/projectchangecontroller.h"

using namespace ModelView;

//! Tests for ProjectChangeController class.

class ProjectChangeControllerTest : public ::testing::Test {
public:
    ~ProjectChangeControllerTest();
};

ProjectChangeControllerTest::~ProjectChangeControllerTest() = default;

TEST_F(ProjectChangeControllerTest, initialState)
{
    SessionModel sample_model("SampleModel");
    SessionModel material_model("MaterialModel");
    std::vector<SessionModel*> models = {&sample_model, &material_model};

    ProjectChangedController controller(models);
    EXPECT_FALSE(controller.hasChanged());
}

TEST_F(ProjectChangeControllerTest, twoModelsChange)
{
    SessionModel sample_model("SampleModel");
    SessionModel material_model("MaterialModel");
    std::vector<SessionModel*> models = {&sample_model, &material_model};

    ProjectChangedController controller(models);

    sample_model.insertItem<PropertyItem>();
    material_model.insertItem<PropertyItem>();

    EXPECT_TRUE(controller.hasChanged());

    controller.resetChanged();
    EXPECT_FALSE(controller.hasChanged());
}

TEST_F(ProjectChangeControllerTest, callback)
{
    int model_changed_count{0};

    SessionModel sample_model("SampleModel");
    SessionModel material_model("MaterialModel");
    std::vector<SessionModel*> models = {&sample_model, &material_model};

    auto on_model_changed = [&model_changed_count]() { ++model_changed_count; };
    ProjectChangedController controller(models, on_model_changed);

    // changing first model
    sample_model.insertItem<PropertyItem>();
    EXPECT_TRUE(controller.hasChanged());
    EXPECT_EQ(model_changed_count, 1);

    // changing second model
    material_model.insertItem<PropertyItem>();
    EXPECT_TRUE(controller.hasChanged());
    EXPECT_EQ(model_changed_count, 1); // controller reports only once

    controller.resetChanged();
    EXPECT_FALSE(controller.hasChanged());
}
