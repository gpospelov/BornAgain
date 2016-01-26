// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunction1DLattice.h
//! @brief     Defines class InterferenceFunction1DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION1DLATTICE_H_
#define INTERFERENCEFUNCTION1DLATTICE_H_

#include "IInterferenceFunction.h"
#include "Lattice1DParameters.h"
#include "FTDistributions.h"

//! @class InterferenceFunction1DLattice
//! @ingroup interference
//! @brief Interference function of 1D lattice

class BA_CORE_API_ InterferenceFunction1DLattice : public IInterferenceFunction
{
public:
    //! @brief constructor
    //! @param lattice_params Lattice parameters
    //! @param length Lattice length
    //! @param xi rotation of lattice with respect to x-axis
    InterferenceFunction1DLattice(double length, double xi);
    virtual ~InterferenceFunction1DLattice();

    virtual InterferenceFunction1DLattice *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    void setProbabilityDistribution(const IFTDistribution1D& pdf);

    Lattice1DParameters getLatticeParameters() const;

    const IFTDistribution1D *getProbabilityDistribution() const;

    virtual double evaluate(const kvector_t& q) const;

protected:
    Lattice1DParameters m_lattice_params;
    IFTDistribution1D *mp_pdf;
    static const int nmax = 20; //!< maximum value for qx*Lambdax and qy*lambday

private:
    InterferenceFunction1DLattice(const Lattice1DParameters& lattice_params);
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    double m_prefactor; //!< fixed prefactor for normalization
    int m_na; //!< determines the number of reciprocal lattice points to use
};

inline Lattice1DParameters InterferenceFunction1DLattice::getLatticeParameters() const
{
    return m_lattice_params;
}

inline const IFTDistribution1D *InterferenceFunction1DLattice::getProbabilityDistribution() const
{
    return mp_pdf;
}

#endif /* INTERFERENCEFUNCTION1DLATTICE_H_ */
