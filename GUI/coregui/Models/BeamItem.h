// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamItem.h
//! @brief     Defines class BeamItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAMITEM_H
#define BEAMITEM_H


#include "ParameterizedItem.h"

class BA_CORE_API_ BeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    static const QString P_INCLINATION_ANGLE;
    static const QString P_AZIMUTHAL_ANGLE;
    explicit BeamItem(ParameterizedItem *parent=0);
    ~BeamItem(){}

    void onPropertyChange(const QString &name);

};


class BA_CORE_API_ BeamWavelengthItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DISTRIBUTION;
    static const QString P_VALUE;
    explicit BeamWavelengthItem(ParameterizedItem *parent=0);
    ~BeamWavelengthItem(){}
    void onPropertyChange(const QString &name);
};


class BA_CORE_API_ TestBeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    explicit TestBeamItem(ParameterizedItem *parent=0);
    ~TestBeamItem(){}
};

class BA_CORE_API_ BeamDistributionItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DISTRIBUTION;
    static const QString P_VALUE;
    static const QString P_COMBO;
    static const QString P_VECTOR;
    explicit BeamDistributionItem(ParameterizedItem *parent=0);
    ~BeamDistributionItem(){}
//    virtual void onPropertyChange(const QString &name);
private:
    void initProperties();
};





#endif

