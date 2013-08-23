// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/DoubleToComplexInterpolatingFunction.h
//! @brief     Defines class DoubleToComplexInterpolatingFunction.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_
#define DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_

#include "IDoubleToComplexFunction.h"
#include <map>
#include "Macros.h"
GCC_DIAG_OFF(unused-local-typedefs);
#include <boost/unordered_map.hpp>
GCC_DIAG_ON(unused-local-typedefs);


class DoubleToComplexInterpolatingFunction : public IDoubleToComplexFunction
{
public:
    typedef std::map<double, complex_t> container_t;
    enum InterpolatingMode { Nearest, Linear, Polar };

    virtual ~DoubleToComplexInterpolatingFunction();
    DoubleToComplexInterpolatingFunction(
        const std::map<double, complex_t>& value_map,
        InterpolatingMode imode=Nearest);
    virtual DoubleToComplexInterpolatingFunction *clone() const;

    virtual complex_t evaluate(double value);

protected:
    container_t m_value_map;
    double m_lower_limit;
    double m_upper_limit;
    double m_low_step;
    double m_high_step;

    InterpolatingMode m_interpolating_mode;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    DoubleToComplexInterpolatingFunction(
        const DoubleToComplexInterpolatingFunction& );
    DoubleToComplexInterpolatingFunction& operator=(
        const DoubleToComplexInterpolatingFunction& );
};

#endif /* DOUBLETOCOMPLEXINTERPOLATINGFUNCTION_H_ */


