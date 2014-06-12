// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunction1DParaCrystal.h
//! @brief     Defines class InterferenceFunction1DParaCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION1DPARACRYSTAL_H_
#define INTERFERENCEFUNCTION1DPARACRYSTAL_H_

#include "IInterferenceFunction.h"
#include "FTDistributions.h"

//! @class InterferenceFunction1DParaCrystal
//! @ingroup interference
//! @brief Interference function of 1D paracrystal.

class BA_CORE_API_ InterferenceFunction1DParaCrystal : public IInterferenceFunction
{
public:

    //! @brief constructor of 1D paracrystal interference function
    //! @param peak_distance  The distance to the first neighbor peak.
    //! @param width Width parameter in the pair correlation function.
    //! @param m_corr_length Correlation length of paracrystal.
    InterferenceFunction1DParaCrystal(
        double peak_distance, double damping_length=0.0);

    virtual ~InterferenceFunction1DParaCrystal() {}
    virtual InterferenceFunction1DParaCrystal *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! @brief Sets size of coherence domain
    //! @param size: size in lattice direction
    void setDomainSize(double size) {
        m_domain_size = size;
    }

    //! Gets the domain size
    double getDomainSize() const {
        return m_domain_size;
    }


    void setKappa(double kappa) { m_kappa = kappa; }
    virtual double getKappa() const { return m_kappa; }
    virtual double evaluate(const cvector_t& q) const;
    //TODO: replace these with strategy pattern for different algorithms
    complex_t FTPDF(double qpar) const;

    //! Sets the Fourier transformed probability distribution of the
    //! nearest particle
    void setProbabilityDistribution(const IFTDistribution1D& pdf);

    //! Gets the Fourier transformed probability distribution of the
    //! nearest particle
    const IFTDistribution1D *getPropabilityDistribution() const;

    double getPeakDistance() const { return m_peak_distance; }

    double getDampingLength() const { return m_damping_length; }

protected:
    double m_peak_distance; //!< the distance to the first neighbor peak
    double m_damping_length; //!< damping length of paracrystal
    IFTDistribution1D *mp_pdf; //!< pdf of nearest particle
    bool m_use_damping_length;
    double m_kappa;
    double m_domain_size;

private:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();
};

#endif /* INTERFERENCEFUNCTION1DPARACRYSTAL_H_ */


