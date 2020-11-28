#include "Base/Utils/FileSystemUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <filesystem>
#include "BATesting.h"

class FileSystemUtilsTest : public ::testing::Test {
    public:
        std::string folderName() {
            const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
            return test_info->test_case_name() + std::string("_") + test_info->name();
        }
};

TEST_F(FileSystemUtilsTest, extension) {
    EXPECT_EQ(FileSystemUtils::extension(""), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/."), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.."), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.hidden"), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.hidden.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt.gz"), ".gz");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt.GZ"), ".GZ");
}

TEST_F(FileSystemUtilsTest, extensions) {
    EXPECT_EQ(FileSystemUtils::extensions(""), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/."), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.."), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.hidden"), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.hidden.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/.hidden.txt.gz"), ".txt.gz");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/f"), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/f.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/file.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/file.txt.gz"), ".txt.gz");
}

TEST_F(FileSystemUtilsTest, filename) {
    EXPECT_EQ(FileSystemUtils::filename(""), "");
	EXPECT_EQ(FileSystemUtils::filename("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/."), ".");     // sic! according to C++17
    EXPECT_EQ(FileSystemUtils::filename("/home/james/.."), "..");   // sic! according to C++17
	EXPECT_EQ(FileSystemUtils::filename("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file.txt"), "file.txt");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file"), "file");
}

TEST_F(FileSystemUtilsTest, stem) {
    EXPECT_EQ(FileSystemUtils::stem(""), "");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/."), ".");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.."), "..");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden.txt"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden.txt.gz"), ".hidden.txt");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt.gz"), "filename.txt");
}

TEST_F(FileSystemUtilsTest, stem_ext) {
    EXPECT_EQ(FileSystemUtils::stem_ext(""), "");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/."), ".");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.."), "..");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden.txt"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden.txt.gz"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename"), "filename");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt.gz"), "filename");
}

TEST_F(FileSystemUtilsTest, createDirectory) {
    const auto baseDir = BATesting::TestOutDir_Core();
    FileSystemUtils::createDirectories(baseDir);
    ASSERT_TRUE(std::filesystem::exists(baseDir));

    const auto newPath = FileSystemUtils::jointPath(baseDir, folderName());
    std::filesystem::remove_all(newPath);
    ASSERT_TRUE(std::filesystem::exists(baseDir));
    ASSERT_FALSE(std::filesystem::exists(newPath));

    // with absolute path
    EXPECT_TRUE(FileSystemUtils::createDirectory(newPath));
    EXPECT_FALSE(FileSystemUtils::createDirectory(newPath));

    // with relative path
    std::filesystem::current_path(newPath);
    EXPECT_TRUE(FileSystemUtils::createDirectory("sub"));
    EXPECT_FALSE(FileSystemUtils::createDirectory("sub"));
    EXPECT_TRUE(std::filesystem::exists("sub"));
    EXPECT_TRUE(std::filesystem::exists(FileSystemUtils::jointPath(newPath, "sub")));

    // clean up
    std::filesystem::current_path(baseDir);
    std::filesystem::remove_all(newPath);
}

TEST_F(FileSystemUtilsTest, createDirectories) {
    const auto baseDir = BATesting::TestOutDir_Core();
    FileSystemUtils::createDirectories(baseDir);
    ASSERT_TRUE(std::filesystem::exists(baseDir));

    // with absolute path
    const auto sub0 = FileSystemUtils::jointPath(baseDir, folderName());
    const auto sub1 = FileSystemUtils::jointPath(sub0, "sub1");
    const auto sub2 = FileSystemUtils::jointPath(sub1, "sub2");
    std::filesystem::remove_all(sub0);
    ASSERT_TRUE(std::filesystem::exists(baseDir));
    ASSERT_FALSE(std::filesystem::exists(sub0));

    EXPECT_TRUE(FileSystemUtils::createDirectories(sub2));
    EXPECT_FALSE(FileSystemUtils::createDirectories(sub2));
    EXPECT_TRUE(std::filesystem::exists(sub0));
    EXPECT_TRUE(std::filesystem::exists(sub1));
    EXPECT_TRUE(std::filesystem::exists(sub2));

    // with relative path
    const auto sub4 = "sub3/sub4";
    std::filesystem::current_path(sub2);
    EXPECT_TRUE(FileSystemUtils::createDirectories(sub4));
    EXPECT_FALSE(FileSystemUtils::createDirectories(sub4));
    EXPECT_TRUE(std::filesystem::exists("sub3"));
    EXPECT_TRUE(std::filesystem::exists("sub3/sub4"));
    EXPECT_TRUE(std::filesystem::exists(FileSystemUtils::jointPath(sub2,sub4)));

    // clean up
    std::filesystem::current_path(baseDir);
    std::filesystem::remove_all(sub0);
}
