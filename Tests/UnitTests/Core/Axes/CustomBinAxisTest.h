#include "google_test.h"
#include "CustomBinAxis.h"
#include "DataFormatUtils.h"
#include "MathConstants.h"
#include <vector>

class CusomBinAxisTest : public ::testing::Test
{
protected:
    CusomBinAxisTest() : m_axis("name", 100, -1.0, 1.0) {}
    ~CusomBinAxisTest();
    CustomBinAxis m_axis;
};

CusomBinAxisTest::~CusomBinAxisTest() = default;

TEST_F(CusomBinAxisTest, CheckClone)
{
    CustomBinAxis* clone = m_axis.clone();
    EXPECT_TRUE(m_axis == *clone);
    delete clone;
}

TEST_F(CusomBinAxisTest, IOStream)
{

    std::ostringstream oss;
    oss << m_axis;

    CustomBinAxis* result
        = dynamic_cast<CustomBinAxis*>(DataFormatUtils::createFixedBinAxis(oss.str()));
    EXPECT_TRUE(m_axis == *result);
    delete result;
}
