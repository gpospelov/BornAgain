// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/IntensityDataItem.cpp
//! @brief     Implements class IntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataItem.h"
#include "BornAgainNamespace.h"
#include "GUIHelpers.h"

const QString DataItem::P_FILE_NAME = "FileName";

void DataItem::setOutputData(OutputData<double>* data)
{
    Q_ASSERT(data);
    m_data.reset(data);
}

void DataItem::setRawDataVector(const OutputData<double>* data)
{
    if (!m_data->hasSameDimensions(*data)) {
        throw GUIHelpers::Error("DataItem::setRawDataVector() -> Error. "
                                "Different dimensions of data.");
    }
    m_data->setRawDataVector(data->getRawDataVector());
}

QString DataItem::fileName(const QString& projectDir) const
{
    QString filename = getItemValue(DataItem::P_FILE_NAME).toString();
    return projectDir.isEmpty() ? filename : projectDir + QStringLiteral("/") + filename;
}

QDateTime DataItem::lastModified() const
{
    return m_last_modified;
}

void DataItem::setLastModified(const QDateTime& dtime)
{
    m_last_modified = dtime;
}

DataItem::DataItem(const QString& modelType) : SessionItem(modelType)
{
    // name of the file used to serialize given IntensityDataItem
    addProperty(P_FILE_NAME, QStringLiteral("undefined"))->setVisible(false);

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_FILE_NAME)
            setLastModified(QDateTime::currentDateTime());
    });

    mapper()->setOnValueChange([this]() {
        // OutputData was modified
        setLastModified(QDateTime::currentDateTime());
    });
}
