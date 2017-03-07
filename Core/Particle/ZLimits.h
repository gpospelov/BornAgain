// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/ZLimits.h
//! @brief     Defines class ZLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ZLIMITS_H
#define ZLIMITS_H

//! Class that contains upper and lower limits of the z-coordinate for the slicing of
//! form factors.
//!
//! @ingroup intern

class ZLimits
{
public:
    enum Type { FINITE, INFINITE, POS_INFINITE, NEG_INFINITE };
    ZLimits(Type type=INFINITE, double ref=0.0);
    ZLimits(double min, double max);

    Type type() const { return m_type; }
    double zmin() const { return m_min; }
    double zmax() const { return m_max; }
private:
    Type m_type;
    double m_min;
    double m_max;
};

#endif // ZLIMITS_H
