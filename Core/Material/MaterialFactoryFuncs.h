// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialFactoryFuncs.h
//! @brief     Factory functions used to create material instances.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALFACTORYFUNCS_H_
#define MATERIALFACTORYFUNCS_H_

#include "Material.h"

struct HomogeneousRegion;

//! @ingroup materials

BA_CORE_API_ Material HomogeneousMaterial();

//! @ingroup materials

BA_CORE_API_ Material HomogeneousMaterial(const std::string& name, double delta, double beta,
                                              kvector_t magnetization = kvector_t());

//! @ingroup materials

//! Constructs a material with _name_, _refractive_index_ and _magnetization_ (in A/m). Alternatively,
//! \f$\delta\f$ and \f$\beta\f$ for refractive index \f$n = 1 - \delta + i \beta\f$ can be passed directly.
//! With no parameters given, constructs default (vacuum) material with \f$n = 1\f$ and zero magnetization.
BA_CORE_API_ Material HomogeneousMaterial(const std::string& name, complex_t refractive_index,
                                              kvector_t magnetization = kvector_t());

//! @ingroup materials

BA_CORE_API_ Material MaterialBySLD();

//! @ingroup materials

//! Constructs a wavelength-independent material with given sld and absorptive term
//! Absorptive term is wavelength-independent (normalized to a wavelength)
//! and can be considered as inverse of imaginary part of complex scattering length density:
//! \f$ SLD = (N b_{coh}, N \sigma_{abs}(\lambda_0) / \lambda_0) \f$
//! Here \f$ N \f$ - material number density,
//! \f$ b_{coh} \f$ - bound coherent scattering length
//! \f$ \sigma_{abs}(\lambda_0) \f$ - absorption cross-section at \f$ \lambda_0 \f$ wavelength.
//! With no parameters given, constructs default (vacuum) material with zero sld and zero magnetization.
//! @param name: material name
//! @param sld: scattering length density, \f$ nm^{-2} \f$
//! @param abs_term: wavelength-independent absorptive term, \f$ nm^{-2} \f$
//! @param magnetization: magnetization (in A/m)
BA_CORE_API_ Material MaterialBySLD(const std::string& name, double sld, double abs_term,
                                    kvector_t magnetization = kvector_t());

//! @ingroup materials

//! Creates averaged material. Square refractive index of returned material is arithmetic mean over
//! _regions_ and _layer_mat_. Magnetization (if present) is averaged linearly.
BA_CORE_API_ Material createAveragedMaterial(const Material& layer_mat, const std::vector<HomogeneousRegion>& regions);

#endif /* MATERIALFACTORYFUNCS_H_ */
