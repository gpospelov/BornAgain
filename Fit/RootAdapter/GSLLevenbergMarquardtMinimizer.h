// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GSLLevenbergMarquardtMinimizer.h
//! @brief     Declares class GSLLevenbergMarquardtMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GSLLEVENBERGMARQUARDTMINIMIZER_H
#define GSLLEVENBERGMARQUARDTMINIMIZER_H

#include "RootMinimizerAdapter.h"

namespace ROOT { namespace Math { class GSLNLSMinimizer; } }

//! Wrapper for CERN ROOT facade of the GSL Levenberg-Marquardt minimizer.
//! It's a facade to ROOT::Math::GSLNLSMinimizer which adapts ROOT::Math::GSLMultiFit
//! minimizers to some CERN ROOT generic minimizer interface. ROOT::Math::GSLMultiFit,
//! in turn, is a facade to the actual GSL's gsl_multifit_fdfsolver_type
//! (http://www.gnu.org/software/gsl/manual/html_node/Nonlinear-Least_002dSquares-Fitting.html).
//! @ingroup fitting_internal

class BA_CORE_API_ GSLLevenbergMarquardtMinimizer : public RootMinimizerAdapter {
public:
    GSLLevenbergMarquardtMinimizer();
    ~GSLLevenbergMarquardtMinimizer();

    //!< Sets tolerance on the function value at the minimum.
    void setTolerance(double value);
    double tolerance() const;

    //! Sets minimizer internal print level.
    void setPrintLevel(int value);
    int printLevel() const;

    //! Sets maximum number of iterations. This is an internal minimizer setting which has
    //! no direct relation to the number of objective function calls (e.g. numberOfIteraction=5
    //! might correspond to ~100 objective function calls).
    void setMaxIterations(int value);
    int maxIterations() const;

    std::string statusToString() const override;
    std::map<std::string, std::string> statusMap() const override;

protected:
    virtual bool isGradientBasedAgorithm() override;
    void propagateOptions() override;
    const root_minimizer_t* rootMinimizer() const override;

private:
    std::unique_ptr<ROOT::Math::GSLNLSMinimizer> m_gsl_minimizer;
};

#endif // GSLLEVENBERGMARQUARDTMINIMIZER_H
