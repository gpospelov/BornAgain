//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testmodel/numericutils.test.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "mvvm/utils/numericutils.h"
#include <cmath>

using namespace ModelView;

class NumericUtilsTest : public ::testing::Test {
public:
    ~NumericUtilsTest();
};

NumericUtilsTest::~NumericUtilsTest() = default;

TEST_F(NumericUtilsTest, areAlmostEqual)
{
    EXPECT_TRUE(Utils::AreAlmostEqual(0.0, 0.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(1.0, 1.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(10.0 / 100.0, 100.0 / 1000.0));
    EXPECT_TRUE(Utils::AreAlmostEqual(std::sin(0.0), 0.0));
    EXPECT_FALSE(Utils::AreAlmostEqual(std::cos(0.0), 0.0));
}
