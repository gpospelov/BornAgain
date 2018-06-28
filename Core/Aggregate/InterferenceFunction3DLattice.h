// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction3DLattice.h
//! @brief     Defines class InterferenceFunction3DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION3DLATTICE_H
#define INTERFERENCEFUNCTION3DLATTICE_H

#include "IInterferenceFunction.h"
#include "Lattice.h"

//! Interference function of 3D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction3DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction3DLattice(const Lattice& lattice);
    ~InterferenceFunction3DLattice() final;

    InterferenceFunction3DLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double evaluate(const kvector_t q) const final;

    const Lattice& lattice() const;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const final;

    std::vector<const INode*> getChildren() const override;

    void onChange() override final;
private:
    Lattice m_lattice;
};

#endif // INTERFERENCEFUNCTION3DLATTICE_H
