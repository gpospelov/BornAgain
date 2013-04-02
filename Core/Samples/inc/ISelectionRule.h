// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISelectionRule.h
//! @brief     Defines classes ISelectionRule, SimpleSelectionRule
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISELECTIONRULE_H_
#define ISELECTIONRULE_H_

#include "BasicVector3D.h"

typedef Geometry::BasicVector3D<int> IndexVector3D;

//! Pure virtual base class for selection rules.

class ISelectionRule
{
 public:
    virtual ~ISelectionRule() {}

    virtual ISelectionRule *clone() const=0;

    virtual bool coordinateSelected(const IndexVector3D& coordinate) const=0;
};

//! Selection rule (v*q)%modulus!=0, defined by vector v(a,b,c) and modulus.

class SimpleSelectionRule : public ISelectionRule
{
 public:
    SimpleSelectionRule(int a, int b, int c, int modulus);
    virtual ~SimpleSelectionRule() {}

    virtual SimpleSelectionRule *clone() const;

    virtual bool coordinateSelected(const IndexVector3D& coordinate) const;
 private:
    int m_a, m_b, m_c;
    int m_mod;
};

inline SimpleSelectionRule::SimpleSelectionRule(
    int a, int b, int c, int modulus)
    : m_a(a), m_b(b), m_c(c), m_mod(modulus) {}

inline SimpleSelectionRule* SimpleSelectionRule::clone() const
{
    return new SimpleSelectionRule(m_a, m_b, m_c, m_mod);
}

inline bool SimpleSelectionRule::coordinateSelected(
        const IndexVector3D& coordinate) const
{
    return (m_a*coordinate[0]+m_b*coordinate[1]+m_c*coordinate[2])%m_mod == 0;
}

#endif /* ISELECTIONRULE_H_ */


