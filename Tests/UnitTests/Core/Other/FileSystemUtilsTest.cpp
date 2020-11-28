#include "Base/Utils/FileSystemUtils.h"
#include "Tests/GTestWrapper/google_test.h"

class FileSystemUtilsTest : public ::testing::Test {};

TEST_F(FileSystemUtilsTest, extension) {
    EXPECT_EQ(FileSystemUtils::extension(""), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.hidden"), "");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/.hidden.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt"), ".txt");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt.gz"), ".gz");
    EXPECT_EQ(FileSystemUtils::extension("/home/james/file.txt.GZ"), ".GZ");
}

TEST_F(FileSystemUtilsTest, extensions) {
    EXPECT_EQ(FileSystemUtils::extensions(""), "");
    EXPECT_EQ(FileSystemUtils::extensions("/home/james/"), "");
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
	EXPECT_EQ(FileSystemUtils::filename("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file.txt"), "file.txt");
    EXPECT_EQ(FileSystemUtils::filename("/home/james/file"), "file");
}

TEST_F(FileSystemUtilsTest, stem) {
    EXPECT_EQ(FileSystemUtils::stem(""), "");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden.txt"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/.hidden.txt.gz"), ".hidden.txt");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem("/home/james/filename.txt.gz"), "filename.txt");
}

TEST_F(FileSystemUtilsTest, stem_ext) {
    EXPECT_EQ(FileSystemUtils::stem_ext(""), "");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/"), "");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden.txt"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/.hidden.txt.gz"), ".hidden");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename"), "filename");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt"), "filename");
    EXPECT_EQ(FileSystemUtils::stem_ext("/home/james/filename.txt.gz"), "filename");
}
