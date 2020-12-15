// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "test_utils.h"
#include <darefl/dataloader/dataloader_constants.h>
#include <darefl/dataloader/dataloader_utils.h>
#include <darefl/importdataview/graphimportdata.h>
#include <initializer_list>
#include <vector>

using namespace DaRefl;
using TestUtils::toStringVector;

//! Tests of ParseUtils.

class ParseUtilsTest : public FolderBasedTest
{
public:
    ParseUtilsTest() : FolderBasedTest("test_ParseUtilsTest") {}
    ~ParseUtilsTest();

    std::vector<std::pair<int, int>>
    toPairVector(std::initializer_list<std::pair<int, int>> list = {})
    {
        return std::vector<std::pair<int, int>>(list.begin(), list.end());
    }

    std::vector<double> toVector(std::initializer_list<double> args)
    {
        return std::vector<double>(args.begin(), args.end());
    };
};

ParseUtilsTest::~ParseUtilsTest() = default;

TEST_F(ParseUtilsTest, LoadASCIIFile)
{
    std::string content = {"abc abc\n 123 456\n"};
    auto file_name = TestUtils::CreateTestFile(testPath(), "a.txt", content);

    auto raw_data = Utils::LoadASCIIFile(file_name);
    EXPECT_EQ(raw_data.size(), 2u);
    EXPECT_EQ(raw_data[0], std::string("abc abc"));
    EXPECT_EQ(raw_data[1], std::string(" 123 456"));
}

//! Testing local utility function.

TEST_F(ParseUtilsTest, toStringVector)
{
    std::vector<std::string> expected;

    expected = {};
    EXPECT_EQ(toStringVector(), expected);

    expected = {"a"};
    EXPECT_EQ(toStringVector("a"), expected);

    expected = {"a", "b"};
    EXPECT_EQ(toStringVector("a", "b"), expected);

    expected = {"aaa", "bbb", ""};
    EXPECT_EQ(toStringVector("aaa", "bbb", ""), expected);
}

//! Testing local utility function.

TEST_F(ParseUtilsTest, toPairVector)
{
    std::vector<std::pair<int, int>> expected;

    expected = {};
    EXPECT_EQ(toPairVector(), expected);
    expected = {{1, 2}};
    EXPECT_EQ(toPairVector({{1, 2}}), expected);
    expected = {{1, 2}, {3, 4}};
    EXPECT_EQ(toPairVector({{1, 2}, {3, 4}}), expected);
}

//! Checking method to expand line numbers
//! "1, 2-4" -> {0, 0}, {1, 3}

TEST_F(ParseUtilsTest, ExpandLineNumberPattern)
{
    using Utils::ExpandLineNumberPattern;
    EXPECT_EQ(ExpandLineNumberPattern(""), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern(" "), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern("aaa"), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern("1"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1 "), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("42"), toPairVector({{42, 42}}));

    EXPECT_EQ(ExpandLineNumberPattern("1,1"), toPairVector({{1, 1}, {1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("1,2"), toPairVector({{1, 1}, {2, 2}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1 , 2 "), toPairVector({{1, 1}, {2, 2}}));

    EXPECT_EQ(ExpandLineNumberPattern("1-1"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("1-5"), toPairVector({{1, 5}}));

    EXPECT_EQ(ExpandLineNumberPattern("1,2-3"), toPairVector({{1, 1}, {2, 3}}));
    EXPECT_EQ(ExpandLineNumberPattern("1, 2-3, 42"), toPairVector({{1, 1}, {2, 3}, {42, 42}}));
    EXPECT_EQ(ExpandLineNumberPattern("42, 2-3, 1"), toPairVector({{42, 42}, {2, 3}, {1, 1}}));

    // more wrong patterns
    EXPECT_EQ(ExpandLineNumberPattern("1,b"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("a,1,b"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("a-2"), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern("6-5"), toPairVector()); // wrong order
}

TEST_F(ParseUtilsTest, CreateLineNumberPatternValidator)
{
    using Utils::CreateLineNumberPatternValidator;

    auto is_accepted = CreateLineNumberPatternValidator("1");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_TRUE(is_accepted(1));
    EXPECT_FALSE(is_accepted(2));

    is_accepted = CreateLineNumberPatternValidator("");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_FALSE(is_accepted(1));
    EXPECT_FALSE(is_accepted(2));

    is_accepted = CreateLineNumberPatternValidator("1, 2");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_TRUE(is_accepted(1));
    EXPECT_TRUE(is_accepted(2));
    EXPECT_FALSE(is_accepted(3));

    is_accepted = CreateLineNumberPatternValidator("42, 44-46");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_TRUE(is_accepted(42));
    EXPECT_FALSE(is_accepted(43));
    EXPECT_TRUE(is_accepted(44));
    EXPECT_TRUE(is_accepted(45));
    EXPECT_TRUE(is_accepted(46));
    EXPECT_FALSE(is_accepted(47));
}

TEST_F(ParseUtilsTest, CreateLinePrefixValidator)
{
    using Utils::CreateLinePrefixValidator;

    auto is_accepted = CreateLinePrefixValidator("");
    EXPECT_FALSE(is_accepted(""));
    EXPECT_FALSE(is_accepted(" "));
    EXPECT_FALSE(is_accepted("                                       "));
    EXPECT_TRUE(is_accepted("abc"));
    EXPECT_TRUE(is_accepted(" abc  "));

    is_accepted = CreateLinePrefixValidator("#");
    EXPECT_FALSE(is_accepted(""));
    EXPECT_FALSE(is_accepted(" "));
    EXPECT_FALSE(is_accepted("# abc"));
    EXPECT_TRUE(is_accepted("42  "));
}

TEST_F(ParseUtilsTest, CreateSeparatorSplitter)
{
    using Utils::CreateSeparatorBasedSplitter;

    auto parse = CreateSeparatorBasedSplitter(",");
    EXPECT_EQ(parse("a"), toStringVector("a"));
    EXPECT_EQ(parse("a,b"), toStringVector("a", "b"));
    EXPECT_EQ(parse("a, b"), toStringVector("a", " b")); // shouldn't we trim white spaces?
    EXPECT_EQ(parse(" a, b "), toStringVector("a", " b"));

    EXPECT_EQ(parse("1.0,2.0,3.0"), toStringVector("1.0", "2.0", "3.0"));
    EXPECT_EQ(parse("1.0, 2.0, 3.0"), toStringVector("1.0", " 2.0", " 3.0"));
    EXPECT_EQ(parse("1.0, 2.0, 3.0,"), toStringVector("1.0", " 2.0", " 3.0", ""));

    parse = CreateSeparatorBasedSplitter(" ");
    EXPECT_EQ(parse("a"), toStringVector("a"));
    EXPECT_EQ(parse("a b"), toStringVector("a", "b"));
    EXPECT_EQ(parse(" a b "), toStringVector("a", "b"));
    EXPECT_EQ(parse(" a    b "), toStringVector("a", "b"));
}

TEST_F(ParseUtilsTest, AddHtmlColorTag)
{
    EXPECT_EQ(Utils::AddHtmlColorTag("abc", "x"), "<font color=\"x\">abc</font>");
}

TEST_F(ParseUtilsTest, AddHtmlDivTag)
{
    EXPECT_EQ(Utils::AddHtmlDivTag("abc"), "<div>abc</div>");
}

TEST_F(ParseUtilsTest, AddHtmlColorTagToParts)
{
    auto parse = Utils::CreateSeparatorBasedSplitter(",");
    std::string line("a,b");
    EXPECT_EQ(Utils::AddHtmlColorTagToParts(line, parse(line), "A", "B"),
              "<div><font color=\"A\">a</font><span style=\"background-color:B\">,</span><font "
              "color=\"A\">b</font></div>");

    parse = Utils::CreateSeparatorBasedSplitter(" | ");
    line = "abc | efg";
    EXPECT_EQ(Utils::AddHtmlColorTagToParts(line, parse(line), "A", "B"),
              "<div><font color=\"A\">abc</font><span style=\"background-color:B\"> | </span><font "
              "color=\"A\">efg</font></div>");
}

TEST_F(ParseUtilsTest, ExtractTwoColumns)
{
    using Utils::ExtractTwoColumns;

    auto result = ExtractTwoColumns({{}}, 0, 0);
    EXPECT_EQ(result.first.size(), 0);
    EXPECT_EQ(result.second.size(), 0);

    // normal parsing
    result = ExtractTwoColumns({{"1.0", "2.0"}, {"3.0", "4.0"}}, 0, 1);
    EXPECT_EQ(result.first, toVector({1.0, 3.0}));
    EXPECT_EQ(result.second, toVector({2.0, 4.0}));

    result = ExtractTwoColumns({{" 1.0 ", " 2.0 "}, {" 3.0 ", " 4.0 "}}, 0, 1);
    EXPECT_EQ(result.first, toVector({1.0, 3.0}));
    EXPECT_EQ(result.second, toVector({2.0, 4.0}));

    // partial parsing (nan in input)
    result = ExtractTwoColumns({{"---", "2.0"}, {"3.0", "4.0"}}, 0, 1);
    EXPECT_EQ(result.first, toVector({3.0}));
    EXPECT_EQ(result.second, toVector({4.0}));

    // partial parsing (different length of columns)
    result = ExtractTwoColumns({{"1.0", "2.0", "3.0"}, {"4.0", "5.0", "6.0", "7.0"}}, 0, 3);
    EXPECT_EQ(result.first, toVector({4.0}));
    EXPECT_EQ(result.second, toVector({7.0}));
}

//! Checks method CreateGraphInfoPairs.

TEST_F(ParseUtilsTest, CreateGraphInfoPairs)
{
    ColumnInfo col0{0, Constants::AxisType, "", 0};
    ColumnInfo col1{1, Constants::IntensityType, "", 0};
    ColumnInfo col2{2, Constants::IgnoreType, "", 0};
    ColumnInfo col3{3, Constants::IntensityType, "", 0};

    std::vector<ColumnInfo> infos = {col0, col1, col2, col3};

    auto info_pairs = Utils::CreateGraphInfoPairs(infos);

    // if we have one Axis and two Intesity columns, we have to get
    // two pairs of info

    ASSERT_EQ(info_pairs.size(), 2);
    EXPECT_EQ(info_pairs[0].first.column, 0);
    EXPECT_EQ(info_pairs[0].second.column, 1);
    EXPECT_EQ(info_pairs[1].first.column, 0);
    EXPECT_EQ(info_pairs[1].second.column, 3);
}

TEST_F(ParseUtilsTest, CreateData)
{
    ColumnInfo col0{0, Constants::AxisType, "units0", 1.0};
    ColumnInfo col2{2, Constants::IntensityType, "units2", 2.0};

    std::vector<std::vector<std::string>> text_data = {{"1.0", "2.0", "3.0"},
                                                       {"4.0", "5.0", "6.0"},
                                                       {"7.0", "8.0", "9.0"},
                                                       {"10.0", "11.0", "12.0"}};

    auto data = Utils::CreateData(text_data, col0, col2);

    EXPECT_EQ(data.graph_description, "");
    EXPECT_EQ(data.bin_centers, toVector({1.0, 4.0, 7.0, 10.0}));
    EXPECT_EQ(data.axis_units, "units0");
    EXPECT_EQ(data.bin_values, toVector({6.0, 12.0, 18.0, 24.0}));
    EXPECT_EQ(data.signal_units, "units2");
}
