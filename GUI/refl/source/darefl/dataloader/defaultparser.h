// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_DEFAULTPARSER_H
#define DAREFL_DATALOADER_DEFAULTPARSER_H

#include <darefl/darefl_export.h>
#include <darefl/dataloader/dataloader_types.h>
#include <darefl/dataloader/parserinterface.h>
#include <map>

namespace DaRefl {

//! Provides basic algorirthm for parsing multi-string data representing content
//! of multi-column ASCII file.
//! + Skips empty lines or lines matching the prefix.
//! + Skips lines matching given line number pattern.
//! + Parse data in columns of basing on given separator value.

class DAREFLCORE_EXPORT DefaultParser : public ParserInterface {
public:
    DefaultParser(const ParserOptions& options);

    void process(const std::vector<std::string>& raw_data) override;

    size_t totalLineCount() const override;

    std::string getLine(size_t index) const override;

    std::vector<std::string> parseResults(size_t index) const override;

    std::vector<std::vector<std::string>> parsedData() const override;

private:
    accept_int_t m_isSkipLineNumber;
    accept_string_t m_isValidLineContent;
    line_splitter_t m_line_splitter;
    std::vector<std::string> m_rawData;
    //!< correspondance of parsed data to original line index
    std::map<size_t, std::vector<std::string>> m_parsedData;
};

} // namespace DaRefl

#endif // DAREFL_DATALOADER_DEFAULTPARSER_H
