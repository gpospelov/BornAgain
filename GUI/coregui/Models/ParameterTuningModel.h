// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTuningModel.h
//! @brief     Declares class ParameterTuningModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERTUNINGMODEL_H
#define PARAMETERTUNINGMODEL_H

#include "FilterPropertyProxy.h"

class ParameterItem;

//!
//! \brief The ParameterTuningModel class represents parameters which can be tuned in real time
//! in ParameterTuningWidget. In the fitting activity context handles dragging of ParameterItem's
//! to the FitParametersWidget.
//!

class BA_CORE_API_ ParameterTuningModel : public FilterPropertyProxy
{
    Q_OBJECT

public:
    ParameterTuningModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &proxyIndex) const;
    QMimeData *mimeData(const QModelIndexList &proxyIndexes) const;
    Qt::DropActions supportedDragActions() const;
    Qt::DropActions supportedDropActions() const;

    ParameterItem *getParameterItem(const QModelIndex &proxyIndex) const;

};

inline Qt::DropActions ParameterTuningModel::supportedDragActions() const
{
    return Qt::CopyAction;
}

inline Qt::DropActions ParameterTuningModel::supportedDropActions() const
{
    return Qt::IgnoreAction;
}

#endif // PARAMETERTUNINGMODEL_H
