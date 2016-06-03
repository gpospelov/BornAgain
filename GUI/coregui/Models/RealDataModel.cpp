// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RealDataModel.cpp
//! @brief     Implements class RealDataModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataModel.h"
#include "JobResultsPresenter.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "IntensityDataIOFactory.h"

RealDataModel::RealDataModel(QObject *parent)
    : SessionModel(SessionXML::RealDataModelTag, parent)
{
    setObjectName(SessionXML::RealDataModelTag);
}

//Qt::ItemFlags RealDataModel::flags(const QModelIndex &index) const
//{
//    Qt::ItemFlags result_flags =  SessionModel::flags(index);
//    result_flags |= Qt::ItemIsEditable;
//    return result_flags;
//}


//! Loads OutputData from the projectDir to JobItem

void RealDataModel::loadNonXMLData(const QString &projectDir)
{
//    for (int i = 0; i < rowCount(QModelIndex()); ++i) {
//        JobItem *jobItem = getJobItemForIndex(index(i, 0, QModelIndex()));
//        JobResultsPresenter::loadIntensityData(jobItem, projectDir);
//    }

}

//! Saves JobItem's OutputData to the projectDir

void RealDataModel::saveNonXMLData(const QString &projectDir)
{
    for (int i = 0; i < rowCount(QModelIndex()); ++i) {
        SessionItem *realDataItem = itemForIndex(index(i, 0, QModelIndex()));
        Q_ASSERT(realDataItem);
        if(IntensityDataItem *intensityItem = dynamic_cast<IntensityDataItem *>(
                    realDataItem->getItem(RealDataItem::T_INTENSITY_DATA))) {
            QString filename = projectDir + QStringLiteral("/")
                    + intensityItem->getItemValue(IntensityDataItem::P_FILE_NAME).toString();
            IntensityDataIOFactory::writeOutputData(
                        *intensityItem->getOutputData(), filename.toStdString());
        }
    }
}
