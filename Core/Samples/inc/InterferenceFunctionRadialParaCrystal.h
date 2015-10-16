// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunctionRadialParaCrystal.h
//! @brief     Defines class InterferenceFunctionRadialParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H_
#define INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H_

#include "IInterferenceFunction.h"
#include "FTDistributions.h"

#include <boost/scoped_ptr.hpp>

//! @class InterferenceFunctionRadialParaCrystal
//! @ingroup interference
//! @brief Interference function of radial paracrystal.

class BA_CORE_API_ InterferenceFunctionRadialParaCrystal
        : public IInterferenceFunction
{
public:

    //! @brief constructor of radial paracrystal interference function
    //! @param peak_distance  The distance to the first neighbor peak.
    //! @param width Width parameter in the pair correlation function.
    //! @param m_corr_length Correlation length of paracrystal.
    InterferenceFunctionRadialParaCrystal(
        double peak_distance, double damping_length=0.0);

    virtual ~InterferenceFunctionRadialParaCrystal() {}
    virtual InterferenceFunctionRadialParaCrystal *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! @brief Sets size of coherence domain
    //! @param size: size in lattice direction
    void setDomainSize(double size) {
        m_domain_size = size;
    }

    //! @brief Gets size of coherence domain
    //! @param size: size in lattice direction
    double getDomainSize() const {
        return m_domain_size;
    }

    //! @brief Sets size-spacing coupling parameter
    //! @param kappa: size-spacing coupling parameter
    void setKappa(double kappa) { m_kappa = kappa; }

    //! @brief Gets size-spacing coupling parameter
    //! @param kappa: size-spacing coupling parameter
    virtual double getKappa() const { return m_kappa; }

    virtual double evaluate(const kvector_t& q) const;
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
    boost::scoped_ptr<IFTDistribution1D> mP_pdf; //!< pdf of nearest particle
    bool m_use_damping_length;
    double m_kappa;
    double m_domain_size;

private:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();
};

#endif /* INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H_ */


