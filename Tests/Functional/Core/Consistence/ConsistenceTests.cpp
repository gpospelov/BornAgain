//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Tests/Functional/Core/Consistence/ConsistenceTests.cpp
//! @brief     Implements Core consistence tests through gtest macros.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

// These tests check whether pairs of reference data sets, generated by
// some other tests, coincide within reasonable numeric error margins.

#include "Tests/GTestWrapper/google_test.h"
#include <string>

int compareTwoReferences(const std::string& name0, const std::string& name1, const double limit);

class Consistence : public ::testing::Test {};

TEST_F(Consistence, SpecularWithSlicing) {
    EXPECT_TRUE(compareTwoReferences("SpecularWithSlicing_01", "SpecularWithSlicing_02", 2e-10));
    EXPECT_TRUE(compareTwoReferences("SpecularWithSlicing_01", "SpecularWithSlicing_03", 2e-10));
}

TEST_F(Consistence, InstrumentDefinitionComparison) {
    EXPECT_TRUE(compareTwoReferences("InstrumentDefinitionComparison_0",
                                     "InstrumentDefinitionComparison_Q", 2e-10));
}

TEST_F(Consistence, TOFResolutionComparison) {
    EXPECT_TRUE(
        compareTwoReferences("TOFResolutionComparison_TP", "TOFResolutionComparison_TR", 2e-10));
}

TEST_F(Consistence, PolarizedQAngleReflectivity) {
    EXPECT_TRUE(compareTwoReferences("PolarizedQAngleReflectivityPP_0",
                                     "PolarizedQAngleReflectivityPP_Q", 2e-10));
    EXPECT_TRUE(compareTwoReferences("PolarizedQAngleReflectivityMM_0",
                                     "PolarizedQAngleReflectivityMM_Q", 2e-10));
}
