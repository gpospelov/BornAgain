// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_PARSERINTERFACE_H
#define DAREFL_DATALOADER_PARSERINTERFACE_H

#include <darefl/darefl_export.h>
#include <string>
#include <vector>

namespace DaRefl
{

//! Interface for all classes capable of parsing ASCII data into multicolumn presentation.

class DAREFLCORE_EXPORT ParserInterface
{
public:
    virtual ~ParserInterface() = default;

    //! Parse data representing content of ASCII file.
    virtual void process(const std::vector<std::string>& raw_data) = 0;

    //! Returns total number of lines in raw data.
    virtual size_t totalLineCount() const = 0;

    //! Returns original line.
    virtual std::string getLine(size_t index) const = 0;

    //! Returns parsed text for given line index. If line was skipped during parsing, returns empty
    //! vector.
    virtual std::vector<std::string> parseResults(size_t index) const = 0;

    //! Returns 2D vector representing parsed text. Skipped lines are not present.
    virtual std::vector<std::vector<std::string>> parsedData() const = 0;
};

} // namespace DaRefl

#endif // DAREFL_DATALOADER_PARSERINTERFACE_H
