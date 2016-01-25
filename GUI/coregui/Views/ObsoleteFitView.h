// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitView.h
//! @brief     Defines class FitView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEFITVIEW_H
#define OBSOLETEFITVIEW_H

#include "ObsoleteFitModel.h"
#include "GUIHelpers.h"

#include <QTreeView>
#include <QHBoxLayout>

#include <QDebug>
#include <iostream>

class QModelIndex;
class SampleModel;
class SessionModel;
class InstrumentModel;
class JobModel;
class JobItem;
class InstrumentItem;
class ParameterizedItem;

class ObsoleteFitView : public QWidget
{
    Q_OBJECT

public:
    ObsoleteFitView(SampleModel* sModel, InstrumentModel* iModel, QWidget *parent = 0);

public slots:
    void sampleSelectionChanged(const QItemSelection &newSelection,
                                    const QItemSelection &oldSelection);
    void fitParameterSelectionChanged(const QItemSelection &newSelection,
                                          const QItemSelection &oldSelection);

private:
    SampleModel* m_sampleModel;
    InstrumentModel* m_instrumentModel;

    ObsoleteFitModel *m_fitParameterModel, *m_sampleParameterModel;

    QTreeView *sampleTreeView;
    QTreeView *instrumentTreeView;

    QTreeView *fitTreeView;

    QItemSelectionModel *sampleSelectionModel;
    QItemSelectionModel *FitParameterSelectionModel;

    QHBoxLayout* wholeWindow;

    ParameterizedItem *extractSampleModel(const QModelIndex &parentIndex = QModelIndex(),
                                          ParameterizedItem *parentItem = 0);

    ParameterizedItem *extractInstrumentModel();
    ParameterizedItem *iterateInstrumentItem(InstrumentItem *instrument);

    // TODO consider implementing as wrapper to ParametrizedItem interface
    // probably a good idea since the data structure can change....
    void insertRowIntoItem(ParameterizedItem *parentItem, ParameterizedItem *childItem);
    void addPropertyToItem(ParameterizedItem *parentItem, const QString &name,
                           const QString &property_name, QVariant &value);
};

#endif // FITVIEW_H
