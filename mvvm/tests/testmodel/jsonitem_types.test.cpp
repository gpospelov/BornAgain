//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testmodel/jsonitem_types.test.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "mvvm/serialization/jsonitem_types.h"

using namespace ModelView;

//! Testing json related flags.

class JsonItemTypesTest : public ::testing::Test {
public:
    ~JsonItemTypesTest();
};

JsonItemTypesTest::~JsonItemTypesTest() = default;

TEST_F(JsonItemTypesTest, isRegenerateIdWhenBackFromJson) {
    EXPECT_FALSE(isRegenerateIdWhenBackFromJson(ConverterMode::none));
    EXPECT_FALSE(isRegenerateIdWhenBackFromJson(ConverterMode::clone));
    EXPECT_TRUE(isRegenerateIdWhenBackFromJson(ConverterMode::copy));
    EXPECT_FALSE(isRegenerateIdWhenBackFromJson(ConverterMode::project));
}

TEST_F(JsonItemTypesTest, isRebuildItemDataAndTagFromJson) {
    EXPECT_TRUE(isRebuildItemDataAndTagFromJson(ConverterMode::none));
    EXPECT_TRUE(isRebuildItemDataAndTagFromJson(ConverterMode::clone));
    EXPECT_TRUE(isRebuildItemDataAndTagFromJson(ConverterMode::copy));
    EXPECT_FALSE(isRebuildItemDataAndTagFromJson(ConverterMode::project));
}
