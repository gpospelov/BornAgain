// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPyramid.h
//! @brief     Defines class FormFactorPyramid
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPYRAMID_H
#define FORMFACTORPYRAMID_H

#include "IFormFactorBorn.h"

//! @class FormFactorPyramid
//! @ingroup formfactors
//! @brief The form factor of pyramid.

class BA_CORE_API_ FormFactorPyramid : public IFormFactorBorn
{
public:
    //! @brief Pyramid constructor
    //! @param length of one side of Pyramid's square base
    //! @param height of Pyramid
    //! @param angle in radians between base and facet
    FormFactorPyramid(double length, double height, double alpha);

    ~FormFactorPyramid() {}
    virtual FormFactorPyramid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;
    void setHeight(double height);

    double getLength() const;
    void setLength(double length);

    double getAlpha() const;
    void setAlpha(double alpha);

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t fullPyramidPrimitive(complex_t a, complex_t b, complex_t c, double z) const;
    complex_t g(complex_t x, complex_t c, double z) const;  // helper function
    complex_t h(complex_t x, double z) const;  // helper function
    double m_length;
    double m_height;
    double m_alpha;
};

inline double FormFactorPyramid::getHeight() const
{
    return m_height;
}

inline void FormFactorPyramid::setHeight(double height)
{
    m_height = height;
}

inline double FormFactorPyramid::getLength() const
{
    return m_length;
}

inline void FormFactorPyramid::setLength(double length)
{
    m_length = length;
}

inline double FormFactorPyramid::getAlpha() const
{
    return m_alpha;
}

inline void FormFactorPyramid::setAlpha(double alpha)
{
    m_alpha = alpha;
}

#endif // FORMFACTORPYRAMID_H
