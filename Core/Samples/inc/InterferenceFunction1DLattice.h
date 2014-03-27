// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunction1DLattice.h
//! @brief     Defines class InterferenceFunction1DLattice.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION1DLATTICE_H_
#define INTERFERENCEFUNCTION1DLATTICE_H_

#include "IInterferenceFunction.h"
#include "Lattice1DIFParameters.h"
#include "FTDistributions.h"

//! @class InterferenceFunction1DLattice
//! @ingroup interference
//! @brief Interference function of 1D lattice

class BA_CORE_API_ InterferenceFunction1DLattice : public IInterferenceFunction
{
public:

    //! @brief constructor
    //! @param lattice_params Lattice parameters
    InterferenceFunction1DLattice(const Lattice1DIFParameters& lattice_params);
    virtual ~InterferenceFunction1DLattice();

    virtual InterferenceFunction1DLattice *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    void setProbabilityDistribution(const IFTDistribution1D& pdf);

    virtual double evaluate(const cvector_t& q) const;
protected:

    Lattice1DIFParameters m_lattice_params;
    IFTDistribution1D *mp_pdf;
    static const int nmax = 20; //!< maximum value for qx*Lambdax and qy*lambday
private:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

//    double m_asx; //!< x coordinates of a*
    double m_prefactor; //!< fixed prefactor for normalization
    int m_na; //!< determines the number of reciprocal lattice points to use
};

#endif /* INTERFERENCEFUNCTION1DLATTICE_H_ */


