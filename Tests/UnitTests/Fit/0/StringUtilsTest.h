#include "StringUtils.h"


class StringUtilsTest : public ::testing::Test
{
protected:
    StringUtilsTest(){}
    virtual ~StringUtilsTest(){}
};


TEST_F(StringUtilsTest, removeSubstring)
{
    std::string target("one two threeone five one");
    std::string result = StringUtils::removeSubstring(target, "one");
    EXPECT_EQ(result, " two three five ");
}
