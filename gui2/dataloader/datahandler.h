// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_DATAHANDLER_H
#define DAREFL_DATALOADER_DATAHANDLER_H

#include "darefl_export.h"
#include <map>
#include <string>
#include <vector>

namespace gui2 {

//! Handles raw data during the life time of DataHandlerDialog.
//! Loads the data from multiple ASCII files and stores in a buffer of strings.

class DAREFLCORE_EXPORT DataHandler {
public:
    DataHandler() = default;

    void updateRawData(const std::vector<std::string>& file_names);

    std::vector<std::string> textData(const std::string& file_name);

private:
    void loadFile(const std::string& file_name);

    //!< correspondence of file name to the raw data in the file (i.e. all strings)
    std::map<std::string, std::vector<std::string>> m_raw_data;
};

} // namespace gui2

#endif // DAREFL_DATALOADER_DATAHANDLER_H
