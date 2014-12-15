// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/MultiLayerRTCoefficients.h
//! @brief     Defines class MultiLayerRTCoefficients.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERRTCOEFFICIENTS_H
#define MULTILAYERRTCOEFFICIENTS_H

#include "ILayerRTCoefficients.h"

//! @class MultiLayerRTCoefficients
//! @ingroup algorithms_internal
//! @brief Container to hold matrix or scalar RT coefficients for a multilayer.

class BA_CORE_API_ MultiLayerRTCoefficients
{
public:
    ~MultiLayerRTCoefficients();
    ILayerRTCoefficients* operator[](size_t i) { return m_data[i]; }
    const ILayerRTCoefficients* operator[](size_t i) const { return m_data[i]; }
    size_t size() const { return m_data.size(); }
    void clear() { m_data.clear(); }
    void resize(size_t size) { m_data.resize(size); }
private:
    std::vector<ILayerRTCoefficients *> m_data;
};

#endif
