// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DLattice.h
//! @brief     Defines class InterferenceFunction2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DLATTICE_H
#define INTERFERENCEFUNCTION2DLATTICE_H

#include "IInterferenceFunction.h"
#include "FTDecayFunctions.h"
#include "Lattice2D.h"

//! Interference function of 2D lattice.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DLattice(double length_1, double length_2, double angle, double xi=0.0);
    ~InterferenceFunction2DLattice() final;

    InterferenceFunction2DLattice* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    static InterferenceFunction2DLattice* createSquare(double lattice_length, double xi = 0.0);
    static InterferenceFunction2DLattice* createHexagonal(double lattice_length, double xi = 0.0);

    void setDecayFunction(const IFTDecayFunction2D& pdf);

    const IFTDecayFunction2D* getDecayFunction() const { return mp_pdf.get(); }

    double evaluate(const kvector_t q) const final;

    const Lattice2D& lattice() const;

    //! Returns the particle density associated with this 2d lattice
    double getParticleDensity() const final;

    std::vector<const INode*> getChildren() const override;

    void onChange() override final;

private:
    InterferenceFunction2DLattice(const Lattice2D& lattice);
    InterferenceFunction2DLattice(const InterferenceFunction2DLattice& other);

    void setLattice(const Lattice2D& lattice);

    //! Returns interference from a single reciprocal lattice vector
    double interferenceAtOneRecLatticePoint(double qx, double qy) const;

    //! Returns reciprocal coordinates in the principal axis system
    void transformToPrincipalAxes(double qx, double qy, double gamma,
                                  double delta, double& q_pa_1, double& q_pa_2) const;

    //! Returns qx,qy coordinates of q - qint, where qint is a reciprocal lattice vector
    //! bounding the reciprocal unit cell to which q belongs
    void calculateReciprocalVectorFraction(double qx, double qy,
                                           double& qx_frac, double& qy_frac) const;

    //! Initializes the x,y coordinates of the a*,b* reciprocal bases
    void initialize_rec_vectors();

    //! Initializes factors needed in each calculation
    void initialize_calc_factors();

    std::unique_ptr<IFTDecayFunction2D> mp_pdf;
    std::unique_ptr<Lattice2D> m_lattice;
    Lattice2D::ReciprocalBases m_sbase;
    static const int nmax = 20; //!< maximum value for qx*Lambdax and qy*lambday
    int m_na, m_nb; //!< determines the number of reciprocal lattice points to use
};

#endif // INTERFERENCEFUNCTION2DLATTICE_H
