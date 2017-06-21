// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOHistory.cpp
//! @brief     Defines OutputDataIOHistory classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataIOHistory.h"
#include "GUIHelpers.h"

//! Static method to create info for just saved IntensityDataItem.

OutputDataSaveInfo OutputDataSaveInfo::createSaved(const IntensityDataItem *item)
{
    Q_ASSERT(item);

    OutputDataSaveInfo result;
    result.m_dataItem = item;
    result.m_file_name = item->fileName();
    result.m_last_saved = QDateTime::currentDateTime();
    return result;
}

bool OutputDataSaveInfo::wasModifiedSinceLastSave() const
{
    return wasSavedBefore(m_dataItem->lastModified());
}

//! Returns true if IntensityDataItem was saved before given time.

bool OutputDataSaveInfo::wasSavedBefore(const QDateTime& dtime) const
{
    // positive number means that m_last_saved is older than dtime
    return m_last_saved.msecsTo(dtime) > 0;
}

//-----------------------------------------------------------------------------

void OutputDataDirHistory::markAsSaved(const IntensityDataItem *item)
{
    if (contains(item))
        throw GUIHelpers::Error("OutputDataDirHistory::markAsSaved() -> Error. "
                                "Already existing item.");

    m_history.push_back(OutputDataSaveInfo::createSaved(item));
}

bool OutputDataDirHistory::wasModifiedSinceLastSave(const IntensityDataItem *item)
{
    // non existing item is treated as modified since last save
    return contains(item) ? itemInfo(item).wasModifiedSinceLastSave() : true;
}

bool OutputDataDirHistory::contains(const IntensityDataItem *item) {
    for(auto& info : m_history)
        if(info.dataItem() == item)
            return true;

    return false;
}

OutputDataSaveInfo OutputDataDirHistory::itemInfo(const IntensityDataItem* item) const
{
    for(auto& info : m_history) {
        if (info.dataItem() == item)
            return info;
    }

    throw GUIHelpers::Error("OutputDataDirHistory::itemInfo() -> Error. No info exists.");
}

//-----------------------------------------------------------------------------

bool OutputDataIOHistory::hasHistory(const QString& dirname) const
{
    return m_dir_history.find(dirname) == m_dir_history.end() ? false : true;
}

bool OutputDataIOHistory::wasModifiedSinceLastSave(const QString& dirname,
                                                   const IntensityDataItem* item)
{
    auto it = m_dir_history.find(dirname);
    if (it == m_dir_history.end())
        throw GUIHelpers::Error("OutputDataIOHistory::wasModifiedSinceLastSave() -> Error. "
                                "No info for directory '"+dirname+"'.");
    return it.value().wasModifiedSinceLastSave(item);
}

//! Sets history for given directory. Previous history will be rewritten.

void OutputDataIOHistory::setHistory(const QString& dirname, const OutputDataDirHistory& history)
{
    Q_ASSERT(dirname.isEmpty() == false);

    m_dir_history[dirname] = history;
}

