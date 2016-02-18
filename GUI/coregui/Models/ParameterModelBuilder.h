// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterModelBuilder.h
//! @brief     Defines class ParameterModelBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERMODELBUILDER_H
#define PARAMETERMODELBUILDER_H

#include <QVariant>
#include <QString>
#include <QModelIndex>

class QModelIndex;
class SampleModel;
class SessionModel;
class InstrumentModel;
class JobModel;
class JobItem;
class InstrumentItem;
class QStandardItem;
class QStandardItemModel;
class ParameterizedItem;

//! The ParameterModelBuilder generates QStandardItemModel representing
//! tunable parameters of instrument and sample models.
//! Used by ModelTuningWidget.
class ParameterModelBuilder
{
public:

    static QStandardItemModel *createParameterModel(JobModel *jobModel, JobItem *jobItem);
    static QStandardItem *iterateSessionModel(SessionModel *sampleModel, const QModelIndex &parentIndex = QModelIndex(), QStandardItem *parentItem = 0);

private:

    static QStandardItem *iterateInstrumentModel(InstrumentModel *instrumentModel);
    static QStandardItem *iterateInstrumentItem(InstrumentItem *instrument);

    static void InsertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem = 0);
    static void addPropertyToParameterModel(QStandardItem *parentItem, const QString &title, const QString &property_name, QVariant value, ParameterizedItem *parameterizedItem);
    static void addDisabledProperty(QStandardItem *parentItem, const QString &title);
};


#endif

