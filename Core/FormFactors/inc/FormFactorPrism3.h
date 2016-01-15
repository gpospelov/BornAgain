// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPrism3.h
//! @brief     Defines class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM3_H_
#define FORMFACTORPRISM3_H_

#include "IFormFactorBorn.h"

//! @class FormFactorPrism3
//! @ingroup formfactors
//! @brief The formfactor of a prism based on a regular triangle.

class BA_CORE_API_ FormFactorPrism3 : public IFormFactorBorn
{
public:
    //! @brief Prism3 constructor
    //! @param length of a side of Prism3's base
    //! @param height of Prism3
    FormFactorPrism3(double length, double height);

    virtual FormFactorPrism3 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;
    void setHeight(double height);

    double getLength() const;
    void setLength(double length);

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_length;
    double m_height;
    double m_root3; // Cached value of square root of 3
};

inline double FormFactorPrism3::getHeight() const
{
    return m_height;
}

inline void FormFactorPrism3::setHeight(double height)
{
    m_height = height;
}

inline double FormFactorPrism3::getLength() const
{
    return m_length;
}

inline void FormFactorPrism3::setLength(double length)
{
    m_length = length;
}

#endif /* FORMFACTORPRISM3_H_ */
