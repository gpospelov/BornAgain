// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Samples/ISelectionRule.h 
//! @brief     Defines class ISelectionRule.
//
// ************************************************************************** //

#ifndef ISELECTIONRULE_H_
#define ISELECTIONRULE_H_

#include "Coordinate3D.h"

class ISelectionRule
{
public:
    virtual ~ISelectionRule() {}

    virtual ISelectionRule *clone() const=0;

    virtual bool coordinateSelected(const Coordinate3D<int> &coordinate) const=0;
};

class SimpleSelectionRule : public ISelectionRule
{
public:
    SimpleSelectionRule(int a, int b, int c, int modulus);
    virtual ~SimpleSelectionRule() {}

    virtual SimpleSelectionRule *clone() const;

    virtual bool coordinateSelected(const Coordinate3D<int> &coordinate) const;
private:
    int m_a, m_b, m_c;
    int m_mod;
};

inline SimpleSelectionRule::SimpleSelectionRule(int a, int b, int c,
        int modulus)
: m_a(a), m_b(b), m_c(c)
, m_mod(modulus)
{
}

inline SimpleSelectionRule* SimpleSelectionRule::clone() const
{
    return new SimpleSelectionRule(m_a, m_b, m_c, m_mod);
}

inline bool SimpleSelectionRule::coordinateSelected(
        const Coordinate3D<int> &coordinate) const
{
    return (m_a*coordinate[0]+m_b*coordinate[1]+m_c*coordinate[2])%m_mod == 0;
}

#endif /* ISELECTIONRULE_H_ */
