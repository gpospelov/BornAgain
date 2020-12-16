// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "gui2/dataloader/dataloader_types.h"
#include "gui2/dataloader/defaultparser.h"
#include "test_utils.h"

using namespace gui2;
using TestUtils::toStringVector;

//! Test DefaultParser.

class DefaultParserTest : public ::testing::Test {
public:
    ~DefaultParserTest();

    int parsedDataRowCount(const DefaultParser& parser) { return parser.parsedData().size(); }
};

DefaultParserTest::~DefaultParserTest() = default;

TEST_F(DefaultParserTest, initialState) {
    DefaultParser parser({});

    EXPECT_EQ(parser.totalLineCount(), 0);
    EXPECT_EQ(parsedDataRowCount(parser), 0);
}

//! Testing line acceptance with standard parser settings.

TEST_F(DefaultParserTest, lineAcceptanceStandardParser) {
    DefaultParser parser({"#", ",", ""}); // prefix, separator, line pattern

    parser.process({"1, 2, 3"});
    EXPECT_EQ(parser.totalLineCount(), 1);
    EXPECT_EQ(parsedDataRowCount(parser), 1);

    parser.process({"1, 2, 3", "4, 5, 6"});
    EXPECT_EQ(parser.totalLineCount(), 2);
    EXPECT_EQ(parsedDataRowCount(parser), 2);

    parser.process({"# 1, 2, 3"});
    EXPECT_EQ(parser.totalLineCount(), 1);
    EXPECT_EQ(parsedDataRowCount(parser), 0);

    parser.process({"#1, 2, 3", "4, 5, 6"});
    EXPECT_EQ(parser.totalLineCount(), 2);
    EXPECT_EQ(parsedDataRowCount(parser), 1);

    parser.process({"#1, 2, 3", "4, 5, 6", ""});
    EXPECT_EQ(parser.totalLineCount(), 3);
    EXPECT_EQ(parsedDataRowCount(parser), 1);
}

//! Testing line acceptance with standard parser settings.

TEST_F(DefaultParserTest, lineAcceptanceNumberPatternParser) {
    DefaultParser parser({"#", ",", "1-2"}); // prefix, separator, line pattern

    parser.process({"1, 2, 3", "4, 5, 6", "7, 8, 9", "#", ""});
    EXPECT_EQ(parser.totalLineCount(), 5);
    EXPECT_EQ(parsedDataRowCount(parser), 1);
}

TEST_F(DefaultParserTest, parseResults) {
    DefaultParser parser({"#", ",", ""}); // prefix, separator, line pattern

    parser.process({"1, 2, 3"});
    EXPECT_EQ(parser.parsedData().size(), 1);
    EXPECT_EQ(parser.parsedData()[0], toStringVector("1", " 2", " 3"));

    parser.process({"1, 2, 3", "4, 5, 6"});
    EXPECT_EQ(parser.parsedData().size(), 2);
    EXPECT_EQ(parser.parsedData()[0], toStringVector("1", " 2", " 3"));
    EXPECT_EQ(parser.parsedData()[1], toStringVector("4", " 5", " 6"));

    parser.process({"#1, 2, 3", "4, 5, 6"});
    EXPECT_EQ(parser.parsedData().size(), 1);
    EXPECT_EQ(parser.parsedData()[0], toStringVector("4", " 5", " 6"));
}
