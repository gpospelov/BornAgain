// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorCoherentPart.h
//! @brief     Defines class FormFactorCoherentPart.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCOHERENTPART_H
#define FORMFACTORCOHERENTPART_H

#include "Complex.h"
#include "EigenCore.h"
#include "WinDllMacros.h"
#include <memory>

class IFormFactor;
class SimulationElement;
class ILayerSpecularInfo;

//! Information about single particle form factor and specular info of the embedding layer.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorCoherentPart
{
public:
    FormFactorCoherentPart(IFormFactor* p_ff);
    FormFactorCoherentPart(const FormFactorCoherentPart& other);
    virtual ~FormFactorCoherentPart();

    complex_t evaluate(const SimulationElement& sim_element) const;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const SimulationElement& sim_element) const;
#endif

    void setSpecularInfo(const ILayerSpecularInfo& specular_info);
    double radialExtension() const;
private:
    std::unique_ptr<IFormFactor> mP_ff;
    std::unique_ptr<ILayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA
};

#endif // FORMFACTORCOHERENTPART_H
