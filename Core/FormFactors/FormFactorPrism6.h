// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPrism6.h
//! @brief     Defines class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM6_H
#define FORMFACTORPRISM6_H
#include "FormFactorPolyhedron.h"

//! @class FormFactorPrism6
//! @ingroup formfactors
//! @brief The formfactor of a prism based on a regular hexagonal.

class BA_CORE_API_ FormFactorPrism6 : public FormFactorPolygonalPrism
{
public:
    //! @brief Prism6 constructor
    //! @param radius of hexagonal base (different from R in IsGisaxs)
    //! @param height of Prism6
    FormFactorPrism6(const double radius, const double height);

    static PolyhedralFace prismatic_face(const double radius);

    virtual FormFactorPrism6 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_radius;
};

inline double FormFactorPrism6::getRadius() const { return m_radius; }

#endif // FORMFACTORPRISM6_H
