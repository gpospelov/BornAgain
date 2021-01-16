// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_TEST_UTILS_H
#define BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_TEST_UTILS_H

#include "mvvm/model/customvariants.h"
#include <QString>
#include <memory>

//! @file Tests/UnitTests/gui2/libtestmachinery/test_utils.h
//! @brief Collection of utility functions for various unit tests.

class QJsonObject;
class QJsonArray;

namespace ModelView {
class SessionModel;
}

//! Various common utils for unit tests.

namespace TestUtils {

//! Returns full path to the main test folder, as defined by CMake at compile time.
//! Should point to CMAKE_BINARY_DIR/test_output
std::string TestOutputDir();

//! Creates test directory in main test folder and returns full path.
//! If directory exists, will do nothing.
std::string CreateTestDirectory(const std::string& test_sub_dir);

//! Returns full path to the main test folder in CMAKE_BINARY_DIR.
std::string TestDirectoryPath(const std::string& test_sub_dir);

//! Returns full path to the file in test directory.
std::string TestFileName(const std::string& test_sub_dir, const std::string& file_name);

//! Helper function to create test file in a given directory (directory should exist).
//! Returns full path of the file.
std::string CreateTestFile(const std::string& dirname, const std::string& fileName,
                           const std::string& content = {});

//! Helper function to create empty file in a given directory (directory should exist).
//! Returns full path of the file.
std::string CreateEmptyFile(const std::string& dirname, const std::string& fileName);

template <typename T = std::string, typename... Args> std::vector<T> toStringVector(Args&&... args)
{
    std::vector<T> v;
    (v.push_back(std::string(args)), ...);
    return v;
}

} // namespace TestUtils

#endif // BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_TEST_UTILS_H
