// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamWavelengthItem.h
//! @brief     Defines class BeamWavelengthItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BEAMWAVELENGTHITEM_H
#define BEAMWAVELENGTHITEM_H

#include "BeamDistributionItem.h"

class BA_CORE_API_ BeamWavelengthItem : public BeamDistributionItem
{
public:
    BeamWavelengthItem();

    double wavelength() const;

private:
    static const bool m_show_mean = true;
};

#endif // BEAMWAVELENGTHITEM_H
