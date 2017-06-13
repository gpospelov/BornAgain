#include "PythonFormatting.h"
#include "BornAgainNamespace.h"
#include "Units.h"
#include "RealLimits.h"

class PythonFormattingTest : public ::testing::Test
{
public:
};

TEST_F(PythonFormattingTest, ValueTimesUnits)
{
    EXPECT_EQ("2.0*nm", PythonFormatting::printValue(2.0, BornAgain::UnitsNm));
    EXPECT_EQ("2.0*deg", PythonFormatting::printValue(2.0*Units::deg, BornAgain::UnitsRad));
    EXPECT_EQ("2.0", PythonFormatting::printValue(2.0, BornAgain::UnitsNone));
}


TEST_F(PythonFormattingTest, RealLimits)
{
    EXPECT_EQ("RealLimits.positive()",
              PythonFormatting::printRealLimits(RealLimits::positive()));

    EXPECT_EQ("RealLimits.nonnegative()",
              PythonFormatting::printRealLimits(RealLimits::nonnegative()));

    EXPECT_EQ("RealLimits.lowerLimited(1.0)", PythonFormatting::printRealLimits(RealLimits::lowerLimited(1.0)));
    EXPECT_EQ("RealLimits.lowerLimited(1.0*nm)", PythonFormatting::printRealLimits(RealLimits::lowerLimited(1.0), BornAgain::UnitsNm));
    EXPECT_EQ("RealLimits.lowerLimited(1.0*deg)", PythonFormatting::printRealLimits(RealLimits::lowerLimited(1.0*Units::deg), BornAgain::UnitsRad));

    EXPECT_EQ("RealLimits.upperLimited(1.0)", PythonFormatting::printRealLimits(RealLimits::upperLimited(1.0)));
    EXPECT_EQ("RealLimits.upperLimited(1.0*nm)", PythonFormatting::printRealLimits(RealLimits::upperLimited(1.0), BornAgain::UnitsNm));
    EXPECT_EQ("RealLimits.upperLimited(1.0*deg)", PythonFormatting::printRealLimits(RealLimits::upperLimited(1.0*Units::deg), BornAgain::UnitsRad));

    EXPECT_EQ("RealLimits.limited(1.0, 2.0)", PythonFormatting::printRealLimits(RealLimits::limited(1.0, 2.0)));
    EXPECT_EQ("RealLimits.limited(1.0*nm, 2.0*nm)", PythonFormatting::printRealLimits(RealLimits::limited(1.0, 2.0), BornAgain::UnitsNm));
    EXPECT_EQ("RealLimits.limited(1.0*deg, 2.0*deg)", PythonFormatting::printRealLimits(RealLimits::limited(1.0*Units::deg, 2.0*Units::deg), BornAgain::UnitsRad));

    // testing printing of real limits in the context of ParameterDistribution and similar
    EXPECT_EQ(", ba.RealLimits.limited(1.0*deg, 2.0*deg)", PythonFormatting::printRealLimitsArg(RealLimits::limited(1.0*Units::deg, 2.0*Units::deg), BornAgain::UnitsRad));

}
