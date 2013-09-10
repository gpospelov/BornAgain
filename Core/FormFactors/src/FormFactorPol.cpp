// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPol.cpp
//! @brief     Implements class FormFactorPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPol.h"

FormFactorPol::~FormFactorPol()
{
}

complex_t FormFactorPol::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    (void)k_i;
    (void)k_f_bin;
    (void)alpha_i;
    (void)alpha_f;
    throw Exceptions::NotImplementedException("FormFactorPol::evaluate:"
            " scalar evaluate should never be called for matrix ff");
}


