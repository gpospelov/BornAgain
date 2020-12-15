// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_PARSEUTILS_H
#define DAREFL_DATALOADER_PARSEUTILS_H

#include <darefl/dataloader/dataloader_types.h>

namespace DaRefl
{

struct GraphImportData;

namespace Utils
{

//! Loads ASCII file, returns it in the form of vector of strings.
DAREFLCORE_EXPORT std::vector<std::string> LoadASCIIFile(const std::string& file_name);

//! Expands string representing line number pattern to inclusive pairs of line numbers.
//! "1" will be expanded to { {1, 1} }, "1, 3-5" will be expanded to { {1, 1}, {3, 5} }
DAREFLCORE_EXPORT std::vector<std::pair<int, int>>
ExpandLineNumberPattern(const std::string& pattern);

//! Creates a callback to define if given line number satisfies line number pattern.
//! "1, 4-6" will accept numbers {1, 4, 5, 6} and will refuse all others.
DAREFLCORE_EXPORT accept_int_t CreateLineNumberPatternValidator(const std::string& pattern);

//! Creates a callback to define if given line has a valid content for further parsing.
//! Empty lines and lines starting from a given prefix will be excluded.
DAREFLCORE_EXPORT accept_string_t CreateLinePrefixValidator(const std::string& prefix_to_exclude);

//! Creates line splitter based on separator.
DAREFLCORE_EXPORT line_splitter_t CreateSeparatorBasedSplitter(const std::string& separator);

//! Returns string representing original 'line' wrapped in 'div' tag.
DAREFLCORE_EXPORT std::string AddHtmlDivTag(const std::string& line);

//! Returns string representing original 'line' wrapped in html color tag.
DAREFLCORE_EXPORT std::string AddHtmlColorTag(const std::string& line, const std::string& color);

//! Returns string representing original 'line' wrapped in 'div' tag.
DAREFLCORE_EXPORT std::string AddHtmlBackgroundTag(const std::string& line,
                                                   const std::string& color);

//! Returns string representing original 'line', where 'parts' are surrounded with color tag.
DAREFLCORE_EXPORT std::string AddHtmlColorTagToParts(const std::string& line,
                                                     const std::vector<std::string>& parts,
                                                     const std::string& color_parts,
                                                     const std::string& color_rest);

//! Extracts double values from two columns of a string array.
//! The row must be valid: string value must represent single double for both target columns,
//! rows should have enough columns. If a row is invalid, it will be skipped, so resulting arrays
//! have always the same length.

DAREFLCORE_EXPORT std::pair<std::vector<double>, std::vector<double>>
ExtractTwoColumns(const std::vector<std::vector<std::string>>& text_data, size_t col1, size_t col2);

//! Pack ColumnInfo into pairs representing {AxisType, IntensityType}.
//! For the moment we expect that only one column with AxisType exists. Number of intensity columns
//! can be arbitrary.

DAREFLCORE_EXPORT std::vector<std::pair<ColumnInfo, ColumnInfo>>
CreateGraphInfoPairs(const std::vector<ColumnInfo>& column_info);

//! Creates structure from text data.

DAREFLCORE_EXPORT GraphImportData CreateData(const std::vector<std::vector<std::string>>& text_data,
                                             const ColumnInfo& axis, const ColumnInfo& intensity);

} // namespace Utils

} // namespace DaRefl

#endif // DAREFL_DATALOADER_PARSEUTILS_H
