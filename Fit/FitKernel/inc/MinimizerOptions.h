// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/MinimizerOptions.h
//! @brief     Defines class MinimizerOptions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZEROPTIONS_H
#define MINIMIZEROPTIONS_H
#include "WinDllMacros.h"

//! The MinimizerOptions class contains options for minimization algorithms

class BA_CORE_API_ MinimizerOptions
{
public:
    MinimizerOptions();
    virtual ~MinimizerOptions(){}

    //! return minimizer tolerance
    double getTolerance() const { return m_tolerance; }
    //! set minimizer tolerance
    void setTolerance(double tolerance) { m_tolerance = tolerance; }

    //! return minimizer precision
    double getPrecision() const { return m_precision; }
    //! set minimizer precision
    void setPrecision(double precision) { m_precision = precision; }

    //! return maximum number of allowed iterations
    int getMaxIterations() const { return m_max_iterations; }
    //! set maximum number of allowed iterations
    void setMaxIterations(int max_iterations) { m_max_iterations = max_iterations; }

    //! return maximum number of allowed function calls
    int getMaxFunctionCalls() const { return m_max_function_calls; }
    //! set maximum number of allowed function calls
    void setMaxFunctionCalls(int max_function_calls) { m_max_function_calls = max_function_calls; }

private:
    double m_tolerance; //!< Tolerance on the function value at the minimum.
    //!< the default tolerance value is 0.01 and the minimization will stop
    //!< when the estimated vertical distance to the minimum (EDM) is less
    //! than 0.001*m_tolerance*up. Here up=1 for chi squared fit and up=0.5
    //! for negative log likelihood fit

    double m_precision; //!< Relative floating point arithmetic precision.
    //!< Should be adjusted when the user knows that FCN function value is not
    //!< calculated to the nominal machine accuracy. Typical values are
    //!< between 10^-5 and 10^-14. If the value is equal to -1 then minimizer
    //!< specific will be used

    int m_max_iterations; //!< Max number of iterations.

    int m_max_function_calls; //!< Max number of function calls.

};


#endif // MINIMIZEROPTIONS_H
