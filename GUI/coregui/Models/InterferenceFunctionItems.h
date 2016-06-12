// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InterferenceFunctionItems.h
//! @brief     Declares InterferenceFunctionItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARACRYSTALITEMS_H
#define PARACRYSTALITEMS_H

#include "SessionGraphicsItem.h"


class BA_CORE_API_ InterferenceFunctionRadialParaCrystalItem : public SessionGraphicsItem
{

public:
    static const QString P_PEAK_DISTANCE;
    static const QString P_DAMPING_LENGTH;
    static const QString P_DOMAIN_SIZE;
    static const QString P_KAPPA;
    static const QString P_PDF;
    explicit InterferenceFunctionRadialParaCrystalItem();
    virtual ~InterferenceFunctionRadialParaCrystalItem(){}
};


class BA_CORE_API_ InterferenceFunction2DParaCrystalItem : public SessionGraphicsItem
{

public:
    static const QString P_ROTATION_ANGLE;
    static const QString P_DAMPING_LENGTH;
    static const QString P_DOMAIN_SIZE1;
    static const QString P_DOMAIN_SIZE2;
    static const QString P_XI_INTEGRATION;
    static const QString P_PDF1;
    static const QString P_PDF2;
    explicit InterferenceFunction2DParaCrystalItem();
    virtual ~InterferenceFunction2DParaCrystalItem(){}
};


class BA_CORE_API_ InterferenceFunction1DLatticeItem : public SessionGraphicsItem
{

public:
    static const QString P_LENGTH;
    static const QString P_ROTATION_ANGLE;
    static const QString P_DECAY_FUNCTION;
    explicit InterferenceFunction1DLatticeItem();
    virtual ~InterferenceFunction1DLatticeItem(){}
};


class BA_CORE_API_ InterferenceFunction2DLatticeItem : public SessionGraphicsItem
{

public:
    static const QString P_LATTICE_TYPE;
    static const QString P_ROTATION_ANGLE;
    static const QString P_DECAY_FUNCTION;
    explicit InterferenceFunction2DLatticeItem();
    virtual ~InterferenceFunction2DLatticeItem(){}
};

#endif
