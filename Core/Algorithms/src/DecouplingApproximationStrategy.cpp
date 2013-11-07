// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DecouplingApproximationStrategy.cpp
//! @brief     Implements class DecouplingApproximationStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecouplingApproximationStrategy.h"
#include "Exceptions.h"
#include "MathFunctions.h"

#include <cassert>
#include <iostream>

void DecouplingApproximationStrategy::init(
        const SafePointerVector<FormFactorInfo>& form_factor_infos,
        const SafePointerVector<IInterferenceFunction>& ifs)
{
    IInterferenceFunctionStrategy::init(form_factor_infos, ifs);
    if (!checkVectorSizes()) {
        throw ClassInitializationException(
            "Wrong number of formfactors or interference functions "
            "for Decoupling Approximation.");
    }
}

double DecouplingApproximationStrategy::evaluateForList(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const std::vector<complex_t> &ff_list) const
{
    double intensity = 0.0;
    complex_t amplitude = complex_t(0.0, 0.0);
    for (size_t i=0; i<m_ff_infos.size(); ++i) {
        complex_t ff = ff_list[i];

        if (MathFunctions::isnan(ff.real())) {
            std::cout << "Amplitude is NaN: i = " << i << std::endl;
        }
        double fraction = m_ff_infos[i]->m_abundance;
        amplitude += fraction*ff;
        intensity += fraction*(std::norm(ff));

        assert(!MathFunctions::isnan(amplitude.real()));
        assert(!MathFunctions::isnan(amplitude.imag()));
        assert(!MathFunctions::isinf(amplitude.real()));
        assert(!MathFunctions::isinf(amplitude.imag()));
    }
    double amplitude_norm = std::norm(amplitude);
    double itf_function = m_ifs[0]->evaluate(k_i-k_f_bin.getMidPoint());
    return intensity + amplitude_norm*(itf_function-1.0);
}

bool DecouplingApproximationStrategy::checkVectorSizes() const
{
    size_t n_ffs = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    return (n_ffs>0 && n_ifs==1);
}


