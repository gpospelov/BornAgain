// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/dataloader/defaultparser.h"
#include "gui2/dataloader/dataloader_utils.h"
#include <stdexcept>

namespace gui2 {

DefaultParser::DefaultParser(const ParserOptions& options) {
    m_isSkipLineNumber = Utils::CreateLineNumberPatternValidator(options.m_skip_index_pattern);
    m_isValidLineContent = Utils::CreateLinePrefixValidator(options.m_header_prefix);
    m_line_splitter = Utils::CreateSeparatorBasedSplitter(options.m_separator);
}

//! Parse data representing content of ASCII file.

void DefaultParser::process(const std::vector<std::string>& raw_data) {
    m_rawData = raw_data;
    m_parsedData.clear();

    int index{0};
    for (const auto& line : m_rawData) {
        bool isValidLine = m_isValidLineContent(line) && !m_isSkipLineNumber(index + 1);

        if (isValidLine)
            m_parsedData.emplace(index, m_line_splitter(line));

        ++index;
    }
}

//! Returns total number of lines in raw data.

size_t DefaultParser::totalLineCount() const {
    return m_rawData.size();
}

//! Returns a pair representing raw line and flag describing parsing results.

std::string DefaultParser::getLine(size_t index) const {
    if (index >= m_rawData.size())
        throw std::runtime_error("Error in DefaultParser: out of bounds.");

    return m_rawData[index];
}

std::vector<std::string> DefaultParser::parseResults(size_t index) const {
    auto it = m_parsedData.find(index);
    return it == m_parsedData.end() ? std::vector<std::string>() : it->second;
}

std::vector<std::vector<std::string>> DefaultParser::parsedData() const {
    std::vector<std::vector<std::string>> result;
    for (size_t index = 0; index < totalLineCount(); ++index) {
        if (auto it = m_parsedData.find(index); it != m_parsedData.end())
            result.push_back(it->second);
    }

    return result;
}

} // namespace gui2
