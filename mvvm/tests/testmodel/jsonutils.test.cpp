//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testmodel/jsonutils.test.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "mvvm/serialization/jsonutils.h"
#include "mvvm/utils/reallimits.h"
#include <limits>

using namespace ModelView;

class JsonUtilsTest : public ::testing::Test {
protected:
    ~JsonUtilsTest();
};

JsonUtilsTest::~JsonUtilsTest() = default;

TEST_F(JsonUtilsTest, toString)
{
    EXPECT_EQ(JsonUtils::ToString(RealLimits::limitless()), "limitless");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::positive()), "positive");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::nonnegative()), "nonnegative");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::lowerLimited(1.0)), "lowerlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::lowerLimited(1.042)), "lowerlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::lowerLimited(-0.99)), "lowerlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::upperLimited(1.0)), "upperlimited");
    EXPECT_EQ(JsonUtils::ToString(RealLimits::limited(-1.0, 2.0)), "limited");
}

TEST_F(JsonUtilsTest, CreateLimits)
{
    EXPECT_EQ(JsonUtils::CreateLimits("limitless"), RealLimits::limitless());
    EXPECT_EQ(JsonUtils::CreateLimits("positive"), RealLimits::positive());
    EXPECT_EQ(JsonUtils::CreateLimits("nonnegative"), RealLimits::nonnegative());
    EXPECT_EQ(JsonUtils::CreateLimits("lowerlimited", 1.0, 0.0), RealLimits::lowerLimited(1.0));
    EXPECT_EQ(JsonUtils::CreateLimits("upperlimited", 0.0, 42.0), RealLimits::upperLimited(42.0));
    EXPECT_EQ(JsonUtils::CreateLimits("limited", -1.0, 2.0), RealLimits::limited(-1.0, 2.0));
}
