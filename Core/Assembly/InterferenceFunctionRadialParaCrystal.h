// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Assembly/InterferenceFunctionRadialParaCrystal.h
//! @brief     Declares class InterferenceFunctionRadialParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H
#define INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H

#include "Complex.h"
#include "FTDistributions.h"
#include "IInterferenceFunction.h"
#include <memory>

//! @class InterferenceFunctionRadialParaCrystal
//! @ingroup interference
//! @brief Interference function of radial paracrystal.

class BA_CORE_API_ InterferenceFunctionRadialParaCrystal : public IInterferenceFunction
{
public:
    InterferenceFunctionRadialParaCrystal(double peak_distance, double damping_length=0.0);
    virtual ~InterferenceFunctionRadialParaCrystal() {}
    virtual InterferenceFunctionRadialParaCrystal* clone() const;

    virtual void accept(ISampleVisitor* visitor) const;

    //! @brief Sets size of coherence domain
    //! @param size: size in lattice direction
    void setDomainSize(double size);

    //! @brief Gets size of coherence domain
    //! @return Size in lattice direction
    double getDomainSize() const;

    //! @brief Sets size-spacing coupling parameter
    //! @param kappa: size-spacing coupling parameter
    void setKappa(double kappa);

    //! @brief Gets size-spacing coupling parameter
    //! @return Size-spacing coupling parameter
    virtual double getKappa() const;

    virtual double evaluate(const kvector_t q) const;
    //TODO: replace these with strategy pattern for different algorithms
    complex_t FTPDF(double qpar) const;

    //! Sets the Fourier transformed probability distribution of the nearest particle
    void setProbabilityDistribution(const IFTDistribution1D& pdf);

    //! Gets the Fourier transformed probability distribution of the nearest particle
    const IFTDistribution1D* getProbabilityDistribution() const;

    double getPeakDistance() const;

    double getDampingLength() const;

protected:
    double m_peak_distance; //!< the distance to the first neighbor peak
    double m_damping_length; //!< damping length of paracrystal
    std::unique_ptr<IFTDistribution1D> mP_pdf; //!< pdf of nearest particle
    bool m_use_damping_length;
    double m_kappa;
    double m_domain_size;

private:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();
};

#endif // INTERFERENCEFUNCTIONRADIALPARACRYSTAL_H
