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
#include <darefl/dataloader/datahandler.h>
#include "mvvm/utils/fileutils.h"

using TestUtils::toStringVector;
using namespace DaRefl;

class DataHandlerTest : public FolderBasedTest {
public:
    DataHandlerTest() : FolderBasedTest("test_DataHandlerTest") {}
    ~DataHandlerTest();
};

DataHandlerTest::~DataHandlerTest() = default;

//! Testing function TrimWhitespace

TEST_F(DataHandlerTest, updateRawData) {
    auto file_name1 = TestUtils::CreateTestFile(testPath(), "a.txt", {"aaa bbb\nccc ddd\n"});

    DataHandler handler;
    handler.updateRawData({file_name1});

    // the data was loaded
    EXPECT_EQ(handler.textData(file_name1), toStringVector("aaa bbb", "ccc ddd"));

    // removing file physically from disk
    ModelView::Utils::remove(file_name1);

    // Updating to the same data will not change anything. Handler knows nothing about
    // the data removed from disk and still keeps the buffer.

    handler.updateRawData({file_name1});
    EXPECT_EQ(handler.textData(file_name1), toStringVector("aaa bbb", "ccc ddd"));

    // adding second file
    auto file_name2 = TestUtils::CreateTestFile(testPath(), "b.txt", {"111 222\n333 444\n"});
    handler.updateRawData({file_name1, file_name2});

    EXPECT_EQ(handler.textData(file_name1), toStringVector("aaa bbb", "ccc ddd"));
    EXPECT_EQ(handler.textData(file_name2), toStringVector("111 222", "333 444"));

    // remove file from list
    handler.updateRawData({});
    EXPECT_TRUE(handler.textData(file_name1).empty());
    EXPECT_TRUE(handler.textData(file_name2).empty());
}
