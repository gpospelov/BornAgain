// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactor2DLattice.h
//! @brief     Defines class FormFactor2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTOR2DLATTICE_H
#define FORMFACTOR2DLATTICE_H

#include "IFormFactorBorn.h"
#include "Lattice2D.h"
#include <memory>

//! The formfactor of a finite 2d lattice of other shapes.
//! @ingroup formfactors

class BA_CORE_API_ FormFactor2DLattice : public IFormFactor
{
public:
    FormFactor2DLattice(const IFormFactor& form_factor, const Lattice2D& lattice,
                        unsigned size_1, unsigned size_2);
    FormFactor2DLattice(const IFormFactor& form_factor, double length_1, double length_2,
                        double alpha, double xi, unsigned size_1, unsigned size_2);
    ~FormFactor2DLattice() override final;

    FormFactor2DLattice* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setAmbientMaterial(Material material) override final;

    double volume() const override final;
    double radialExtension() const override final;

    double bottomZ(const IRotation& rotation) const override;

    double topZ(const IRotation& rotation) const override final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

private:
    void setFormFactor(const IFormFactor& ff);
    void setLattice(const Lattice2D& lattice);
    complex_t getLatticeFactor(const WavevectorInfo& wavevectors) const;
    std::unique_ptr<IFormFactor> mP_form_factor;
    std::unique_ptr<Lattice2D> mP_lattice;
    unsigned m_size_1, m_size_2;  //!< Size of the finite lattice in lattice units
};

inline void FormFactor2DLattice::setAmbientMaterial(Material material)
{
    mP_form_factor->setAmbientMaterial(material);
}

inline double FormFactor2DLattice::volume() const
{
    return m_size_1 * m_size_2 * mP_form_factor->volume();
}

inline double FormFactor2DLattice::radialExtension() const
{
    return (m_size_1 + m_size_2) * mP_form_factor->radialExtension() / 2.0;
}

inline double FormFactor2DLattice::bottomZ(const IRotation& rotation) const
{
    return  mP_form_factor->bottomZ(rotation);
}

inline double FormFactor2DLattice::topZ(const IRotation& rotation) const
{
    return mP_form_factor->topZ(rotation);
}

#endif // FORMFACTOR2DLATTICE_H
