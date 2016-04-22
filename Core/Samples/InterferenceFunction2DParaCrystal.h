// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/InterferenceFunction2DParaCrystal.h
//! @brief     Declares class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DPARACRYSTAL_H_
#define INTERFERENCEFUNCTION2DPARACRYSTAL_H_

#include "IInterferenceFunction.h"
#include "Lattice2DParameters.h"
#include "FTDistributions.h"

#include <iostream>
#include <memory>

// Forward declaration to prevent IntegratorReal.h to be parsed for Python API:
template <class T> class IntegratorReal;

//! @class InterferenceFunction2DParaCrystal
//! @ingroup interference
//! @brief Interference function of 2D paracrystal.
class BA_CORE_API_ InterferenceFunction2DParaCrystal : public IInterferenceFunction
{
public:

    //! @brief constructor of 2D paracrystal interference function
    //! @param length_1 Length of first lattice basis vector.
    //! @param length_2 Length of second lattice basis vector.
    //! @param alpha_lattice Angle between the lattice basis vectors.
    //! @param xi Angle between first basis vector and the x-axis of incoming beam.
    //! @param damping_length Damping length for removing delta function singularity at q=0.
    InterferenceFunction2DParaCrystal(double length_1, double length_2, double alpha_lattice,
                                      double xi = 0.0, double damping_length = 0.0);

    virtual ~InterferenceFunction2DParaCrystal();

    virtual InterferenceFunction2DParaCrystal *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    static InterferenceFunction2DParaCrystal *createSquare(double peak_distance,
                                                           double damping_length = 0.0,
                                                           double domain_size_1 = 0.0,
                                                           double domain_size_2 = 0.0);
    static InterferenceFunction2DParaCrystal *createHexagonal(double peak_distance,
                                                              double damping_length = 0.0,
                                                              double domain_size_1 = 0.0,
                                                              double domain_size_2 = 0.0);

    //! @brief Sets the sizes of coherence domains
    //! @param size_1: size in first lattice direction
    //! @param size_2: size in second lattice direction
    void setDomainSizes(double size_1, double size_2);

    //! @brief Sets the probability distributions (Fourier transformed) for the two
    //! lattice directions.
    //! @param pdf_1: probability distribution in first lattice direction
    //! @param pdf_2: probability distribution in second lattice direction
    void setProbabilityDistributions(const IFTDistribution2D &pdf_1,
                                     const IFTDistribution2D &pdf_2);

    void setIntegrationOverXi(bool integrate_xi);

    virtual double evaluate(const kvector_t q) const;

    std::vector<double> getDomainSizes() const;
    std::vector<const IFTDistribution2D *> getProbabilityDistributions() const;
    bool getIntegrationOverXi() const;
    double getDampingLength() const;

    Lattice2DParameters getLatticeParameters() const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

    //! Returns the particle density associated with this 2d paracrystal lattice
    virtual double getParticleDensity() const;

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    void transformToPrincipalAxes(double qx, double qy, double gamma, double delta, double &q_pa_1,
                                  double &q_pa_2) const;

    Lattice2DParameters m_lattice_params; //!< Lattice parameters
    bool m_integrate_xi; //!< Integrate over the orientation xi
    IFTDistribution2D *m_pdfs[2];
    double m_damping_length; //!< Damping length for removing delta function singularity at q=0.
    bool m_use_damping_length; //!< Flag that determines if the damping length should be used.
    double m_domain_sizes[2]; //!< Coherence domain sizes

private:
    //! Returns interference function for fixed angle xi.
    double interferenceForXi(double xi) const;

    //! Returns interference function for fixed xi in the dimension determined by the given index.
    double interference1D(double qx, double qy, double xi, size_t index) const;

    complex_t FTPDF(double qx, double qy, double xi, size_t index) const;

#ifndef SWIG
    std::unique_ptr<IntegratorReal<InterferenceFunction2DParaCrystal>> mP_integrator;
#endif
    mutable double m_qx;
    mutable double m_qy;
};

inline void InterferenceFunction2DParaCrystal::setIntegrationOverXi(bool integrate_xi)
{
    m_integrate_xi = integrate_xi;
}

inline bool InterferenceFunction2DParaCrystal::getIntegrationOverXi() const
{
    return m_integrate_xi;
}

inline double InterferenceFunction2DParaCrystal::getDampingLength() const
{
    return m_damping_length;
}

#endif /* INTERFERENCEFUNCTION2DPARACRYSTAL_H_ */
