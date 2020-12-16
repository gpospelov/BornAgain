// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_FOLDERBASEDTEST_H
#define BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_FOLDERBASEDTEST_H

#include <gtest/gtest.h>
#include <string>

//! Convenience class which creates a directory on disk for test content.

class FolderBasedTest : public ::testing::Test {
public:
    FolderBasedTest(const std::string& test_dir);
    ~FolderBasedTest();

    std::string testDir() const;

    std::string testPath() const;

    std::string createEmptyDir(const std::string& subdir) const;

protected:
    std::string m_test_dir; //! main directory of given test
};

#endif // BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_FOLDERBASEDTEST_H
