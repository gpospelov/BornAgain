// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/dataloader/datahandler.h"
#include "gui2/dataloader/dataloader_utils.h"
#include "mvvm/utils/containerutils.h"
#include <iostream>

namespace gui2 {

//! Load raw data from the list of files, if it was not loaded yet.
//! Remove data which is not present.

void DataHandler::updateRawData(const std::vector<std::string>& file_names) {
    for (const auto& file_name : file_names)
        if (auto it = m_raw_data.find(file_name); it == m_raw_data.end())
            loadFile(file_name);

    for (auto it = m_raw_data.begin(); it != m_raw_data.end(); /* no increment */) {
        if (ModelView::Utils::Contains(file_names, it->first))
            it++;
        else
            m_raw_data.erase(it++);
    }
}

//! Returns raw text data representing content of the file with given name.

std::vector<std::string> DataHandler::textData(const std::string& file_name) {
    auto it = m_raw_data.find(file_name);
    return it != m_raw_data.end() ? it->second : std::vector<std::string>();
}

//! Load file with given name. File is assumed to be ASCII.

void DataHandler::loadFile(const std::string& file_name) {
    m_raw_data[file_name] = Utils::LoadASCIIFile(file_name);
}

} // namespace gui2
