// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorCoherentSum.h
//! @brief     Defines class FormFactorCoherentSum.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCOHERENTSUM_H
#define FORMFACTORCOHERENTSUM_H

#include "ICloneable.h"
#include "Complex.h"
#include "EigenCore.h"
#include "FormFactorCoherentPart.h"
#include <vector>

class IFresnelMap;
class IFormFactor;
class SimulationElement;

//! Information about particle form factor and abundance.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorCoherentSum : public ICloneable
{
public:
    FormFactorCoherentSum(IFormFactor* ff, double abundance);
    virtual ~FormFactorCoherentSum();
    virtual FormFactorCoherentSum* clone() const;

    complex_t evaluate(const SimulationElement& sim_element) const;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const SimulationElement& sim_element) const;
#endif

    void setSpecularInfo(const IFresnelMap* p_fresnel_map, size_t layer_index);

    double relativeAbundance() const { return m_abundance; }
    void scaleRelativeAbundance(double total_abundance);
    double radialExtension() const;
private:
    FormFactorCoherentSum(const std::vector<FormFactorCoherentPart>& parts,
                          double abundance);
    std::vector<FormFactorCoherentPart> m_parts;
    double m_abundance;
};

#endif // FORMFACTORCOHERENTSUM_H
