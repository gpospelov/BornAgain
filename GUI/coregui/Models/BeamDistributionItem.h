// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/BeamDistributionItem.h
//! @brief     Declares class BeamDistributionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BEAMDISTRIBUTIONITEM_H
#define BEAMDISTRIBUTIONITEM_H

#include "SessionItem.h"
#include "DistributionItem.h"

#include <memory>

class ParameterDistribution;
class IDistribution1D;

//! The BeamDistributionItem handles wavelength, inclination and azimuthal parameter
//! distribution for BeamItem
class BA_CORE_API_ BeamDistributionItem : public SessionItem
{
public:
    static const QString P_DISTRIBUTION;
    explicit BeamDistributionItem(const QString name = QString());
    virtual ~BeamDistributionItem(){}

    std::unique_ptr<ParameterDistribution> getParameterDistributionForName(
            const std::string &parameter_name);


protected:
    virtual std::unique_ptr<IDistribution1D> createDistribution1D();
};

#endif
