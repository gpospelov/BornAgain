// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterItem.h
//! @brief     Defines class FitParameterItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETERITEM_H
#define FITPARAMETERITEM_H

#include "ParameterizedItem.h"


class BA_CORE_API_ FitParameterItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_MIN;
    static const QString P_MAX;
    static const QString P_VALUE;
    static const QString P_USE;
    explicit FitParameterItem(ParameterizedItem *parent=0);
    virtual ~FitParameterItem(){}

    void setParNames(QStringList par_names);
    QStringList getParNames();
private:
    QStringList m_par_names;
};


// bool fixed, start_value, min, max, step

#endif

