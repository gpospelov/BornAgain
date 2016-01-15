// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/LayerRoughnessItems.h
//! @brief     Defines classes LayerRoughnessItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERROUGHNESSITEMS_H
#define LAYERROUGHNESSITEMS_H


#include "ParameterizedItem.h"

class BA_CORE_API_ LayerZeroRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit LayerZeroRoughnessItem(ParameterizedItem *parent=0);
    virtual ~LayerZeroRoughnessItem(){}
};


class BA_CORE_API_ LayerBasicRoughnessItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_SIGMA;
    static const QString P_HURST;
    static const QString P_LATERAL_CORR_LENGTH;
    explicit LayerBasicRoughnessItem(ParameterizedItem *parent=0);
    virtual ~LayerBasicRoughnessItem(){}
};


#endif
