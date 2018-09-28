// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOService.h
//! @brief     Implements class OutputDataIOService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "OutputDataIOService.h"
#include "ApplicationModels.h"
#include "DataItem.h"
#include "IntensityDataIOFactory.h"
#include "ProjectUtils.h"
#include "MessageService.h"
#include "JobItem.h"
#include "ModelPath.h"
#include "item_constants.h"

namespace
{
JobItem* parentJobItem(DataItem* dataItem);

//! loads intensity data from project directory
void loadIntensityData(DataItem* intensityItem, const QString& projectDir);

//! Saves intensityData in project directory
void saveIntensityData(DataItem* intensityItem, const QString& projectDir);
} // namespace

OutputDataIOService::OutputDataIOService(QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
}

OutputDataIOService::OutputDataIOService(ApplicationModels* models, QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
    setApplicationModels(models);
}

void OutputDataIOService::setApplicationModels(ApplicationModels* models)
{
    m_applicationModels = models;
}

void OutputDataIOService::save(const QString& projectDir)
{
    if (!m_history.hasHistory(projectDir))
        m_history.setHistory(projectDir, OutputDataDirHistory());

    OutputDataDirHistory newHistory;

    for (auto item : dataItems()) {

        if (m_history.wasModifiedSinceLastSave(projectDir, item))
            saveIntensityData(item, projectDir);

        newHistory.markAsSaved(item);
    }

    // dealing with files
    QStringList oldFiles = m_history.savedFileNames(projectDir);
    QStringList newFiles = newHistory.savedFileNames();
    cleanOldFiles(projectDir, oldFiles, newFiles);

    // if oldHistory contained some deleted IntensityDataItems, that info will be dropped here
    m_history.setHistory(projectDir, newHistory);
}

void OutputDataIOService::load(const QString& projectDir, MessageService* messageService)
{
    OutputDataDirHistory newHistory;

    for (auto item : dataItems()) {
        try {
            loadIntensityData(item, projectDir);
            newHistory.markAsSaved(item);
            // handling crash of GUI during job run and non-existing file
            if (auto jobItem = parentJobItem(item)) {
                if (jobItem->isRunning()) {
                    jobItem->setComments(QString("Possible GUI crash while job was running"));
                    jobItem->setStatus(Constants::STATUS_FAILED);
                }
            }

        } catch (const std::exception& ex) {
            if (auto jobItem = parentJobItem(item)) {
                // Handling corrupted file on disk
                jobItem->setComments(QString("Load of the data from disk failed with '%1'").arg(QString(ex.what())));
                jobItem->setStatus(Constants::STATUS_FAILED);
            }
            if (messageService)
                messageService->send_warning(this, QString(ex.what()));
            else
                throw ex;
        }
    }
    m_history.setHistory(projectDir, newHistory);
}

//! Returns all IntensityDataItems available for save/load.

QVector<DataItem*> OutputDataIOService::dataItems() const
{
    QVector<DataItem*> result;

    if (!m_applicationModels)
        return result;

    for (auto item : m_applicationModels->nonXMLData())
        if (auto data_item = dynamic_cast<DataItem*>(item))
            result.push_back(data_item);

    return result;
}

//! Clean old saved files.
//! All files in oldSaves list, which are not in newSaves list, will be removed.

void OutputDataIOService::cleanOldFiles(const QString& projectDir, const QStringList& oldSaves,
                                        const QStringList& newSaves)
{
    QStringList to_remove = ProjectUtils::substract(oldSaves, newSaves);
    ProjectUtils::removeFiles(projectDir, to_remove);
}

namespace
{
JobItem* parentJobItem(DataItem* dataItem)
{
    auto jobItem =
        dynamic_cast<const JobItem*>(ModelPath::ancestor(dataItem, Constants::JobItemType));
    return const_cast<JobItem*>(jobItem);
}

//! loads intensity data from project directory

void loadIntensityData(DataItem* intensityItem, const QString& projectDir)
{
    QString filename = intensityItem->fileName(projectDir);
    auto data = IntensityDataIOFactory::readOutputData(filename.toStdString());
    if (data)
        intensityItem->setOutputData(data);
}

//! Saves intensityData in project directory

void saveIntensityData(DataItem* intensityItem, const QString& projectDir)
{
    if (!intensityItem)
        return;

    intensityItem->saveData(projectDir);
}
} // namespace
