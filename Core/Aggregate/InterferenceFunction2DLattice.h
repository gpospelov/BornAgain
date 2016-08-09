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
#include "Lattice2DParameters.h"

//! @class InterferenceFunction2DLattice
//! @ingroup interference
//! @brief Interference function of 2D lattice

class BA_CORE_API_ InterferenceFunction2DLattice : public IInterferenceFunction
{
public:
    //! @brief contructor
    //! @param length_1 Lattice length 1
    //! @param length_2 Lattice length 2
    //! @param angle angle between lattice vectors
    //! @param xi rotation of lattice with respect to x-axis
    InterferenceFunction2DLattice(double length_1, double length_2, double angle, double xi=0.0);
    virtual ~InterferenceFunction2DLattice();

    virtual InterferenceFunction2DLattice* clone() const;

    virtual void accept(ISampleVisitor* visitor) const;

    static InterferenceFunction2DLattice* createSquare(double lattice_length, double xi = 0.0);
    static InterferenceFunction2DLattice* createHexagonal(double lattice_length, double xi = 0.0);

    void setDecayFunction(const IFTDecayFunction2D& pdf);

    const IFTDecayFunction2D* getDecayFunction() const;

    virtual double evaluate(const kvector_t q) const;

    Lattice2DParameters getLatticeParameters() const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool* external_pool,
                                                    int copy_number = -1) const;

    //! Returns the particle density associated with this 2d lattice
    virtual double getParticleDensity() const;

protected:
    //! Returns interference from a single reciprocal lattice vector
    double interferenceAtOneRecLatticePoint(double qx, double qy) const;

    //! Returns reciprocal coordinates in the principal axis system
    void transformToPrincipalAxes(double qx, double qy, double gamma,
            double delta, double& q_pa_1, double& q_pa_2) const;

    //! Returns qx,qy coordinates of q - qint, where qint is a reciprocal lattice vector
    //! bounding the reciprocal unit cell to which q belongs
    void calculateReciprocalVectorFraction(double qx, double qy,
            double& qx_frac, double& qy_frac) const;

    Lattice2DParameters m_lattice_params;
    IFTDecayFunction2D* mp_pdf;
    static const int nmax = 20; //!< maximum value for qx*Lambdax and qy*lambday

private:
    InterferenceFunction2DLattice(const Lattice2DParameters& lattice_params);

    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    //! Initializes the x,y coordinates of the a*,b* reciprocal bases
    void initialize_rec_vectors();

    //! Initializes factors needed in each calculation
    void initialize_calc_factors(double coherence_length_x,
            double coherence_length_y);

    double m_asx, m_asy; //!< x,y coordinates of a*
    double m_bsx, m_bsy; //!< x,y coordinates of b*
    int m_na, m_nb; //!< determines the number of reciprocal lattice points to use
};

#endif // INTERFERENCEFUNCTION2DLATTICE_H
