// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction1DLattice.h
//! @brief     Defines class InterferenceFunction1DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION1DLATTICE_H
#define INTERFERENCEFUNCTION1DLATTICE_H

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Lattice/Lattice1DParameters.h"

class IFTDecayFunction1D;

//! Interference function of a 1D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction1DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction1DLattice(double length, double xi);
    ~InterferenceFunction1DLattice() final;

    InterferenceFunction1DLattice* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setDecayFunction(const IFTDecayFunction1D& decay);

    Lattice1DParameters getLatticeParameters() const { return m_lattice_params; }

    std::vector<const INode*> getChildren() const override final;

private:
    double iff_without_dw(const kvector_t q) const override final;
    InterferenceFunction1DLattice(const InterferenceFunction1DLattice& other);
    void init_parameters();

    Lattice1DParameters m_lattice_params;
    std::unique_ptr<IFTDecayFunction1D> mP_decay;
    int m_na; //!< determines the number of reciprocal lattice points to use
};

#endif // INTERFERENCEFUNCTION1DLATTICE_H
