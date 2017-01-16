// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction1DLattice.h
//! @brief     Defines class InterferenceFunction1DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION1DLATTICE_H
#define INTERFERENCEFUNCTION1DLATTICE_H

#include "IInterferenceFunction.h"
#include "Lattice1DParameters.h"

class IFTDecayFunction1D;

//! Interference function of 1D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction1DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction1DLattice(double length, double xi);
    ~InterferenceFunction1DLattice() final;

    InterferenceFunction1DLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void setDecayFunction(const IFTDecayFunction1D& pdf);

    Lattice1DParameters getLatticeParameters() const { return m_lattice_params; }

    const IFTDecayFunction1D* getDecayFunction() const { return mp_pdf; }

    double evaluate(const kvector_t q) const final;

private:
    InterferenceFunction1DLattice(const Lattice1DParameters& lattice_params);
    void init_parameters();

    Lattice1DParameters m_lattice_params;
    IFTDecayFunction1D* mp_pdf;
    int m_na; //!< determines the number of reciprocal lattice points to use

    static const int nmax = 20; //!< maximum value for qx*Lambdax and qy*lambday
};

#endif // INTERFERENCEFUNCTION1DLATTICE_H
