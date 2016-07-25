// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregates/InterferenceFunctionRadialParaCrystal.h
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

#include "IInterferenceFunction.h" // inheriting from
#include "Complex.h"
#include "FTDistributions.h"
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

    //! Returns textual representation of *this and its descendants.
    virtual std::string to_str(int indent=0) const;

    //! Sets size of coherence domain
    void setDomainSize(double size) { m_domain_size = size; }

    //! Returns size of coherence domain
    double getDomainSize() const { return m_domain_size; }

    //! Sets size-spacing coupling parameter
    void setKappa(double kappa) { m_kappa = kappa; }

    //! Gets size-spacing coupling parameter
    virtual double getKappa() const { return m_kappa; }

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
