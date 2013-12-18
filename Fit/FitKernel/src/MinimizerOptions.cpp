// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/MinimizerOptions.cpp
//! @brief     Implement class MinimizerOptions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerOptions.h"


MinimizerOptions::MinimizerOptions()
    : m_tolerance(0.01)
    , m_precision(-1)
    , m_max_iterations(0)
    , m_max_function_calls(0)
{

}
