// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorFullSphere.h
//! @brief     Defines class FormFactorFullSphere.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORFULLSPHERE_H_
#define FORMFACTORFULLSPHERE_H_

#include "IFormFactorBorn.h"

//! @ingroup formfactors
//! @class FormFactorFullSphere
//! @brief The formfactor of a sphere.

// // /*! \addtogroup formfactors
// //   *  Sketch of a Full Sphere
//   *  @{
//   */
// //! \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$
// //! @image html sphere3d.png "Sphere"
// //![Caption text](sphere3d.png "Image title")

// /*!
//  * @image html sphere3d.png "Sphere"
// */
// /*!
// *  A function
// */
//void func1()
//{
//}

///*! Another function */
//void func2()
//{
//}

// /*! @} */



class BA_CORE_API_ FormFactorFullSphere : public IFormFactorBorn
{
public:
    //! @brief Full Sphere constructor
    //! @param radius of Sphere
    FormFactorFullSphere(double radius);
    ~FormFactorFullSphere() {}
    virtual FormFactorFullSphere *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 1; }

    //! Returns radius of sphere
    virtual double getRadius() const { return m_radius; }
    virtual void setRadius(double radius) {m_radius = radius; }

    //! Returns diameter of sphere
    virtual double getHeight() const { return 2.0*m_radius; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    double m_radius;
};

#endif /* FORMFACTORFULLSPHERE_H_ */


