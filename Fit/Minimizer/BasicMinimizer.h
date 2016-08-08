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

//! @class BasicMinimizer
//! @ingroup fitting_internal
//! @brief The BasicMinimizer class is a base for all minimizers

class BA_CORE_API_ BasicMinimizer : public IMinimizer
{
public:
    explicit BasicMinimizer(const std::string &minimizerName,
                            const std::string &algorithmName = std::string());

    //! Returns name of the minimizer.
    std::string minimizerName() const;

    //! Returns name of the minimization algorithm.
    std::string algorithmName() const;

    //! Sets minimization algorithm.
    void setAlgorithmName(const std::string &algorithmName);

private:
    std::string m_minimizerName;
    std::string m_algorithmName;
};

#endif

