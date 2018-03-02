// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOHistory.h
//! @brief     Defines OutputDataIOHistory classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef OUTPUTDATAIOHISTORY_H
#define OUTPUTDATAIOHISTORY_H

#include "WinDllMacros.h"
#include "DataItem.h"
#include <QVector>
#include <QDateTime>

class IntensityDataItem;

//! Holds information about last save for IntensityDataItem.

class BA_CORE_API_ OutputDataSaveInfo
{
public:
    OutputDataSaveInfo() : m_dataItem(nullptr) {}

    static OutputDataSaveInfo createSaved(const DataItem* item);

    const DataItem* dataItem() const { return m_dataItem; }

    QString fileName() const { return m_file_name; }

    bool wasModifiedSinceLastSave() const;

private:
    bool wasSavedBefore(const QDateTime& dtime) const;

    QDateTime m_last_saved;
    QString m_file_name;
    const DataItem* m_dataItem;
};

//! Save history information for collection of IntensityDataItems.

class BA_CORE_API_ OutputDataDirHistory {
public:
    OutputDataDirHistory() {}

    void markAsSaved(const DataItem* item);

    bool wasModifiedSinceLastSave(const DataItem* item);

    bool contains(const DataItem* item);

    QStringList savedFileNames() const;

private:
    OutputDataSaveInfo itemInfo(const DataItem* item) const;

    QVector<OutputDataSaveInfo> m_history;
};

//! Save history information for set of directories.

class BA_CORE_API_ OutputDataIOHistory {
public:
    bool hasHistory(const QString& dirname) const;

    bool wasModifiedSinceLastSave(const QString& dirname, const DataItem* item);

    void setHistory(const QString& dirname, const OutputDataDirHistory& history);

    QStringList savedFileNames(const QString& dirname) const;

private:

    //!< Correspondance of directory name to save history.
    QMap<QString, OutputDataDirHistory> m_dir_history;
};

#endif // OUTPUTDATAIOHISTORY_H
