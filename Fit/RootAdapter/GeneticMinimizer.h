// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GeneticMinimizer.h
//! @brief     Declares class GeneticMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GENETICMINIMIZER_H
#define GENETICMINIMIZER_H

#include "RootMinimizerAdapter.h"

namespace BA_ROOT { namespace Math { class GeneticMinimizer; } }

//! @class GeneticMinimizer
//! @ingroup fitting_internal
//! @brief Wrapper for ROOT Genetic minimizer

class BA_CORE_API_ GeneticMinimizer : public RootMinimizerAdapter {
public:
    GeneticMinimizer();
    ~GeneticMinimizer();

    //!< Sets tolerance on the function value at the minimum.
    //!< Minimization will stop when the estimated vertical distance to the minimum (EDM) is less
    //! than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5
    //! for negative log likelihood fit.
    //! Default value is 0.01.
    void setTolerance(double value);
    double tolerance() const;

    //! Sets minimizer internal print level.
    //! Default value is 0 (silent).
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of iterations to try at each step.
    //! Default values is 3.
    void setMaxIterations(int value);
    int maxIterations() const;

    //! Sets population size.
    //! Default value is 300.
    void setPopulationSize(int value);
    int populationSize() const;

    //! Sets random seed.
    //! Default value is 0.
    void setRandomSeed(int value);
    int randomSeed() const;

    void setParameter(size_t index, const FitParameter *par);

    std::string statusToString() const;
    std::map<std::string, std::string> statusMap() const;

protected:
    void propagateOptions();
    const root_minimizer_t* rootMinimizer() const;

private:
    std::unique_ptr<BA_ROOT::Math::GeneticMinimizer> m_genetic_minimizer;
};

#endif // GENETICMINIMIZER_H
