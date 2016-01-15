// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorAnisoPyramid.h
//! @brief     Defines class FormFactorAnisoPyramid
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORANISOPYRAMID_H
#define FORMFACTORANISOPYRAMID_H

#include "IFormFactorBorn.h"

//! @class FormFactorAnisoPyramid
//! @ingroup formfactors
//! @brief The formfactor of an anisotropic pyramid.
// //! @image html AnistropicPyramid3d.png

class BA_CORE_API_ FormFactorAnisoPyramid : public IFormFactorBorn
{
public:
    //! @brief Anisotropic Pyramid constructor
    //! @param length of Anisotropic Pyramid's base
    //! @param width of Anisotropic Pyramid's base
    //! @param height of Anisotropic Pyramid
    //! @param alpha angle in radians between base and facet
    FormFactorAnisoPyramid(double length, double width, double height, double alpha);

    ~FormFactorAnisoPyramid() {}
    virtual FormFactorAnisoPyramid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;
    void setHeight(double height);

    double getLength() const;
    void setLength(double length);

    double getWidth() const;
    void setWidth(double width);

    double getAlpha() const;
    void setAlpha(double alpha);

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    complex_t fullAnisoPyramidPrimitive(complex_t a, complex_t b, complex_t c,
                                        double d, double z) const;
    complex_t g(complex_t x, complex_t c, complex_t bd, double z) const;  // helper function
    complex_t h(complex_t x, complex_t bd, double z) const;               // helper function
    complex_t k(complex_t x, double d, double z) const;                   // helper function
    double m_length;
    double m_width;
    double m_height;
    double m_alpha;
};

inline double FormFactorAnisoPyramid::getHeight() const
{
    return m_height;
}

inline void FormFactorAnisoPyramid::setHeight(double height)
{
    m_height = height;
}

inline double FormFactorAnisoPyramid::getLength() const
{
    return m_length;
}

inline void FormFactorAnisoPyramid::setLength(double length)
{
    m_length = length;
}

inline double FormFactorAnisoPyramid::getWidth() const
{
    return m_width;
}

inline void FormFactorAnisoPyramid::setWidth(double width)
{
    m_width = width;
}

inline double FormFactorAnisoPyramid::getAlpha() const
{
    return m_alpha;
}

inline void FormFactorAnisoPyramid::setAlpha(double alpha)
{
    m_alpha = alpha;
}


#endif // FORMFACTORANISOPYRAMID_H
