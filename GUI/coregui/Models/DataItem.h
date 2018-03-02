// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DataItem.h
//! @brief     Declares class DataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATAITEM_H
#define DATAITEM_H

#include "SessionItem.h"
#include "OutputData.h"
#include <QDateTime>

class BasicAxisItem;
class MaskContainerItem;
class ProjectionContainerItem;

//! Provides common functionality for IntensityDataItem and SpecularDataItem

class BA_CORE_API_ DataItem : public SessionItem
{
public:
    static const QString P_FILE_NAME;

    OutputData<double>* getOutputData() { return m_data.get(); }
    const OutputData<double>* getOutputData() const { return m_data.get(); }
    virtual void setOutputData(OutputData<double>* data) = 0;
    virtual void setRawDataVector(const OutputData<double>* data) = 0;

    QString fileName(const QString& projectDir = QString()) const;

    QDateTime lastModified() const;
    void setLastModified(const QDateTime& dtime);

protected:
    DataItem(const QString& modelType);

    std::unique_ptr<OutputData<double>> m_data; //!< simulation results
    QDateTime m_last_modified;
};

#endif // DATAITEM_H
