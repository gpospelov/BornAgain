// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NIntensityDataItem.h
//! @brief     Defines class NIntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NINTENSITYDATAITEM_H
#define NINTENSITYDATAITEM_H

#include "ParameterizedItem.h"

class BA_CORE_API_ NIntensityDataItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_XAXIS_MIN;
    static const QString P_XAXIS_MAX;
    static const QString P_YAXIS_MIN;
    static const QString P_YAXIS_MAX;
    static const QString P_ZAXIS_MIN;
    static const QString P_ZAXIS_MAX;
    static const QString P_GRADIENT;
    static const QString P_IS_LOGZ;
    static const QString P_IS_INTERPOLATED;
    static const QString P_XAXIS_TITLE;
    static const QString P_YAXIS_TITLE;
    static const QString P_AXES_UNITS;

    explicit NIntensityDataItem(ParameterizedItem *parent=0);
    ~NIntensityDataItem(){}
};

#endif // NINTENSITYDATAITEM_H

