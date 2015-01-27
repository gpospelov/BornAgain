// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/LayerSpecularInfo.h
//! @brief     Defines class LayerSpecularInfo.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERSPECULARINFO_H_
#define LAYERSPECULARINFO_H_

#include "Utils.h"
#include "ICloneable.h"
#include "ILayerRTCoefficients.h"
#include "ISpecularInfoMap.h"

#include <boost/shared_ptr.hpp>


//! @class LayerSpecularInfo
//! @ingroup algorithms_internal
//! @brief Holds the amplitude information of the neutron
//! wavefunction in a specific layer for different incoming (outgoing) angles of
//! the neutron beam in the top layer (these amplitudes correspond to the
//! specular part of the neutron wavefunction)

class BA_CORE_API_ LayerSpecularInfo : public ICloneable
{
public:
    LayerSpecularInfo();
    virtual ~LayerSpecularInfo() {}

    virtual LayerSpecularInfo *clone() const;

    //! Adds the amplitude coefficients for the (time-reversed) outgoing
    //! wavevector with the given angles
    void addOutCoefficients(ISpecularInfoMap *rt_coefficient_map);

    //! Adds the amplitude coefficients for the incoming wavevector
    void addInCoefficients(ILayerRTCoefficients *rt_coefficients) {
        mP_in_coeffs.reset(rt_coefficients);
    }

    //! Retrieves the amplitude coefficients for the (time-reversed) outgoing
    //! wavevector with the given angles
    const ILayerRTCoefficients *getOutCoefficients(
            double alpha_f, double phi_f) const;

    //! Retrieves the amplitude coefficients for the incoming wavevector
    const ILayerRTCoefficients *getInCoefficients() const {
        return mP_in_coeffs.get();
    }
private:
    boost::shared_ptr<ISpecularInfoMap> mP_out_coeff_map;
    boost::shared_ptr<ILayerRTCoefficients> mP_in_coeffs;
};


#endif /* LAYERSPECULARINFO_H_ */