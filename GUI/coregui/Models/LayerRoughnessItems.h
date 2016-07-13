// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerRoughnessItems.h
//! @brief     Declares classes LayerRoughnessItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef LAYERROUGHNESSITEMS_H
#define LAYERROUGHNESSITEMS_H


#include "SessionItem.h"

class BA_CORE_API_ LayerZeroRoughnessItem : public SessionItem
{

public:
    explicit LayerZeroRoughnessItem();
    virtual ~LayerZeroRoughnessItem(){}
};


class BA_CORE_API_ LayerBasicRoughnessItem : public SessionItem
{

public:
    static const QString P_SIGMA;
    static const QString P_HURST;
    static const QString P_LATERAL_CORR_LENGTH;
    explicit LayerBasicRoughnessItem();
    virtual ~LayerBasicRoughnessItem(){}
};


#endif // LAYERROUGHNESSITEMS_H
