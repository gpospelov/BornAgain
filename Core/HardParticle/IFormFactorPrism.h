// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IFormFactorPrism.h
//! @brief     Defines class IFormFactorPrism.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_IFORMFACTORPRISM_H
#define BORNAGAIN_CORE_HARDPARTICLE_IFORMFACTORPRISM_H

#include "Core/HardParticle/PolyhedralComponents.h"
#include "Core/HardParticle/PolyhedralTopology.h"
#include "Core/Scattering/IFormFactorBorn.h"
#include <memory>

class BA_CORE_API_ Prism
{
public:
    Prism() = delete;
    Prism(const Prism&) = delete;
    Prism(bool symmetry_Ci, double height, const std::vector<kvector_t>& vertices);
    double area() const;
    const std::vector<kvector_t>& vertices(); //! needed for topZ, bottomZ computation
    complex_t evaluate_for_q(const cvector_t& q) const;
    // complex_t evaluate_centered(const cvector_t& q) const;
private:
    std::unique_ptr<PolyhedralFace> m_base;
    double m_height;
    std::vector<kvector_t> m_vertices; //! for topZ, bottomZ computation only
};

//! A prism with a polygonal base, for form factor computation.

class BA_CORE_API_ IFormFactorPrism : public IFormFactorBorn
{
public:
    IFormFactorPrism() = default;
    IFormFactorPrism(const NodeMeta& meta, const std::vector<double>& PValues);

    double bottomZ(const IRotation& rotation) const override final;
    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate_for_q(cvector_t q) const override;
    double volume() const override;
    double radialExtension() const override;
    double getHeight() const;

protected:
    void setPrism(bool symmetry_Ci, const std::vector<kvector_t>& vertices);
    virtual double height() const = 0; // TODO mv parameter m_height back from children to this

private:
    std::unique_ptr<Prism> pimpl;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_IFORMFACTORPRISM_H
