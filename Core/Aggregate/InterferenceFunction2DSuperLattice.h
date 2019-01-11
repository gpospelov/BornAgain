// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DSuperLattice.h
//! @brief     Defines class InterferenceFunction2DSuperLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DSUPERLATTICE_H
#define INTERFERENCEFUNCTION2DSUPERLATTICE_H

#include "IInterferenceFunction.h"
#include "Lattice2D.h"

template <class T> class IntegratorReal;

//! Interference function of 2D superlattice with a configurable interference function for
//! each lattice site.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DSuperLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DSuperLattice(const Lattice2D& lattice, unsigned size_1, unsigned size_2);
    InterferenceFunction2DSuperLattice(double length_1, double length_2, double alpha,
                                        double xi, unsigned size_1, unsigned size_2);
    ~InterferenceFunction2DSuperLattice() final;

    InterferenceFunction2DSuperLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void setSubstructureIFF(const IInterferenceFunction& sub_iff);
    const IInterferenceFunction& substructureIFF() const;

    static InterferenceFunction2DSuperLattice* createSquare(
            double lattice_length, double xi, unsigned size_1, unsigned size_2);
    static InterferenceFunction2DSuperLattice* createHexagonal(
            double lattice_length, double xi, unsigned size_1, unsigned size_2);

    double evaluate(const kvector_t q) const final;

    unsigned domainSize1() const { return m_size_1; }
    unsigned domainSize2() const { return m_size_2; }

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }

    const Lattice2D& lattice() const;

    std::vector<const INode*> getChildren() const override;

private:
    InterferenceFunction2DSuperLattice(const InterferenceFunction2DSuperLattice& other);
    void setLattice(const Lattice2D& lattice);

    void init_parameters();
    double interferenceForXi(double xi) const;

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<Lattice2D> mP_lattice;
    std::unique_ptr<IInterferenceFunction> mP_substructure;  //!< IFF of substructure
    unsigned m_size_1, m_size_2;  //!< Size of the finite lattice in lattice units
    mutable double m_qx;
    mutable double m_qy;
#ifndef SWIG
    std::unique_ptr<IntegratorReal<InterferenceFunction2DSuperLattice>> mP_integrator;
#endif
};

#endif // INTERFERENCEFUNCTION2DSUPERLATTICE_H
