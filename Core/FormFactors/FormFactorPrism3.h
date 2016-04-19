// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorPrism3.h
//! @brief     Defines class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM3_H
#define FORMFACTORPRISM3_H
#include "FormFactorPolyhedron.h"

//! @class FormFactorPrism3
//! @ingroup formfactors
//! @brief The formfactor of a prism based on an equilateral triangle.

class BA_CORE_API_ FormFactorPrism3 : public FormFactorPolygonalPrism
{
public:
    //! @brief Prism3 constructor
    //! @param length of hexagonal base (different from R in IsGisaxs)
    //! @param height of Prism3
    FormFactorPrism3(const double length, const double height);

    static PolyhedralFace prismatic_face(const double length);

    virtual FormFactorPrism3 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;
    double getLength() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_length;
};

inline double FormFactorPrism3::getLength() const { return m_length; }

#endif // FORMFACTORPRISM3_H
