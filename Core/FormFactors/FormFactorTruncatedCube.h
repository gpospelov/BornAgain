// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorTruncatedCube.h
//! @brief     Declares class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRUNCATEDCUBE_H
#define FORMFACTORTRUNCATEDCUBE_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorTruncatedCube
//! @ingroup formfactors
//! @brief The formfactor of a truncated cube.

class BA_CORE_API_ FormFactorTruncatedCube : public FormFactorPolyhedron
{
public:
    FormFactorTruncatedCube(double length, double removed_length);

    virtual FormFactorTruncatedCube *clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    double getLength() const { return m_length; }
    double getRemovedLength() const { return m_removed_length; }

private:
    virtual void onChange() final;
    double m_length;
    double m_removed_length;
};

#endif // FORMFACTORTRUNCATEDCUBE_H
