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
#include "Exceptions.h"
#include <string>
#include <map>

//! @class MinimizerOptions
//! @ingroup fitting
//! @brief The %MinimizerOptions class contains options for minimization algorithms
//!
//! It allows to set values only if they have been already registered.

class BA_CORE_API_ MinimizerOptions
{
public:
    MinimizerOptions();
    ~MinimizerOptions(){}

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

    //! set option value
//    void setValue(const std::string &name, double val) { setRealValue(name, val);}
//    void setValue(const std::string &name, int val) { setIntValue(name, val);}
//    void setValue(const std::string &name, const std::string &val) { setNamedValue(name, val);}

    void setValue(const std::string &name, double val) { setExistingValue(name, m_RealOpts, val); }
    void setValue(const std::string &name, int val) { setExistingValue(name, m_IntOpts, val);}
    void setValue(const std::string &name, const std::string &val) { setExistingValue(name, m_NamOpts, val);}

    void addValue(const std::string &name, double val) { addNewValue(name, m_RealOpts, val); }
    void addValue(const std::string &name, int val) { addNewValue(name, m_IntOpts, val);}
    void addValue(const std::string &name, const std::string &val) { addNewValue(name, m_NamOpts, val);}

    int getIntValue(const std::string &name) { return getValue(name, m_IntOpts); }
    double getRealValue(const std::string &name) { return getValue(name, m_RealOpts); }
    std::string getNamedValue(const std::string &name) { return getValue(name, m_NamOpts); }

private:
//    void setRealValue(const std::string &name, double val){ setExistingValue(name, m_RealOpts, val); }
//    void setIntValue(const std::string &name, int val){ setExistingValue(name, m_IntOpts, val); }
//    void setNamedValue(const std::string &name, const std::string &val){ setExistingValue(name, m_NamOpts, val); }

    template<class M>
    static void setExistingValue(const std::string &name, M & opts, const typename M::mapped_type & value) {
       typename M::iterator pos;
       pos = opts.find(name);
       if (pos != opts.end()) {
           pos->second = value;
       } else {
           throw LogicErrorException("MinimizerOptions::setValue() -> Error! Not existing name '"+name+"'");
       }
    }

    template<class M>
    static void addNewValue(const std::string &name, M & opts, const typename M::mapped_type & value) {
       typename M::iterator pos;
       pos = opts.find(name);
       if (pos != opts.end()) {
           throw LogicErrorException("MinimizerOptions::addValue() -> Error! Already existing name '"+name+"'");
       } else {
           opts.insert(typename M::value_type(name, value) );
       }
    }

    template<class M>
    static const typename M::mapped_type getValue(const std::string &  name, const M & opts) {
       typename M::const_iterator pos;
       pos = opts.find(name);
       if (pos == opts.end()) {
           throw LogicErrorException("MinimizerOptions::getValue() -> Error! Not existing name '"+name+"'");
       }
       return  (*pos).second;
    }


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

    std::map<std::string, double> m_RealOpts; //!< additional map of the real options
    std::map<std::string, int> m_IntOpts; //!< map of the integer options
    std::map<std::string, std::string> m_NamOpts; //!< map of the named options
};


#endif // MINIMIZEROPTIONS_H
