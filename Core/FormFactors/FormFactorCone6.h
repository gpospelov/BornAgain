// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorCone6.h
//! @brief     Defines class FormFactorCone6
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCONE6_H
#define FORMFACTORCONE6_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorCone6
//! @ingroup formfactors
//! @brief The formfactor of a cone6.
class BA_CORE_API_ FormFactorCone6 : public FormFactorPolyhedron
{
public:
    //! @brief Cone6 constructor
    //! @param radius of hexagonal base (different from R in IsGisaxs)
    //! @param height of Cone6
    //! @param angle in radians between base and facet
    FormFactorCone6(double radius, double height,  double alpha);

    static std::vector<PolyhedralFace> polyhedral_faces(
        double radius, double height,  double alpha);

    virtual FormFactorCone6* clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;
    virtual double getRadius() const final;
    double getAlpha() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_radius;
    double m_height;
    double m_alpha;
};

inline double FormFactorCone6::getHeight() const { return m_height; }
inline double FormFactorCone6::getRadius() const { return m_radius; }
inline double FormFactorCone6::getAlpha() const { return m_alpha; }

#endif // FORMFACTORCONE6_H
