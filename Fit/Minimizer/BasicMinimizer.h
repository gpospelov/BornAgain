// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/BasicMinimizer.h
//! @brief     Declares class BasicMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BASICMINIMIZER_H
#define BASICMINIMIZER_H

#include "IMinimizer.h"
#include <string>
#include <memory>

class ROOTMinimizerChiSquaredFunction;
class ROOTMinimizerGradientFunction;
namespace BA_ROOT {
namespace Math {
class Minimizer;
}
}

//! @class BasicMinimizer
//! @ingroup fitting_internal
//! @brief The BasicMinimizer class is a base for all minimizers

class BA_CORE_API_ BasicMinimizer : public IMinimizer
{
public:
    typedef BA_ROOT::Math::Minimizer root_minimizer_t;

    explicit BasicMinimizer(const std::string &minimizerName,
                            const std::string &algorithmName = std::string());
    virtual ~BasicMinimizer();

    virtual void minimize();


    //! Returns name of the minimizer.
    std::string minimizerName() const;

    //! Returns name of the minimization algorithm.
    std::string algorithmName() const;

    //! Sets minimization algorithm.
    void setAlgorithmName(const std::string &algorithmName);


    virtual void setParameter(size_t index, const FitParameter *par);

    virtual void setParameters(const FitSuiteParameters& parameters);


    //! Sets chi squared function to minimize
    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters);

    //! Sets gradient function to minimize
    virtual void setGradientFunction(
        function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize);


    virtual bool isGradientBasedAgorithm() { return false;}


    virtual std::vector<double> getValueOfVariablesAtMinimum() const;
    virtual std::vector<double> getErrorOfVariables() const;

    void printResults() const;

    std::string toResultString() const;


protected:
    int fitParameterCount() const;
    virtual void propagateOptions(){}
    virtual const root_minimizer_t* rootMinimizer() const = 0;
    root_minimizer_t* rootMinimizer();

private:
    std::string m_minimizerName;
    std::string m_algorithmName;

    std::unique_ptr<ROOTMinimizerChiSquaredFunction> m_chi2_func;
    std::unique_ptr<ROOTMinimizerGradientFunction> m_gradient_func;
};

#endif // BASICMINIMIZER_H

