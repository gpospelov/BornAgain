// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunction2DParaCrystal.h
//! @brief     Defines class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DPARACRYSTAL_H_
#define INTERFERENCEFUNCTION2DPARACRYSTAL_H_

#include "IInterferenceFunction.h"
#include "FTDistributions.h"
#include <iostream>

//! @class InterferenceFunction2DParaCrystal
//! @ingroup interference
//! @brief Interference function of 2D paracrystal.

class BA_CORE_API_ InterferenceFunction2DParaCrystal : public IInterferenceFunction
{
public:

    //! @brief constructor of 2D paracrystal interference function
    //! @param length_1 Lattice length 1.
    //! @param length_2 Lattice length 2.
    //! @param alpha_lattice Angle between lattice basis vectors.
    //! @param xi Angle between first basis vector and the x-axis of incoming beam.
    //! @param m_corr_length correlation length of paracrystal
    InterferenceFunction2DParaCrystal(double length_1, double length_2,
            double alpha_lattice, double xi=0.0, double damping_length=0.0);
    virtual ~InterferenceFunction2DParaCrystal();

    virtual InterferenceFunction2DParaCrystal *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    static InterferenceFunction2DParaCrystal *createSquare(
            double peak_distance, double corr_length=0.0,
            double domain_size_1=0.0, double domain_size_2=0.0);
    static InterferenceFunction2DParaCrystal *createHexagonal(
            double peak_distance, double corr_length=0.0,
            double domain_size_1=0.0, double domain_size_2=0.0);

    //! @brief Sets sizes of coherence domain
    //! @param size_1: size in first lattice direction
    //! @param size_2: size in second lattice direction
    void setDomainSizes(double size_1, double size_2) {
        m_domain_sizes[0] = size_1;
        m_domain_sizes[1] = size_2;
    }

    void setProbabilityDistributions(const IFTDistribution2D& pdf_1,
            const IFTDistribution2D& pdf_2);

    void setIntegrationOverXi(bool integrate_xi)
    { m_integrate_xi = integrate_xi; }

    virtual double evaluate(const cvector_t& q) const;

    //! Adds parameters from local pool to external pool and call recursion
    //! over direct children
    virtual std::string addParametersToExternalPool(std::string path,
            ParameterPool *external_pool, int copy_number=-1) const;

    std::vector<double> getLatticeLengths() const;
    double getAlphaLattice() const { return m_alpha_lattice; }
    double getLatticeOrientation() const { return m_xi; }
    std::vector<double> getDomainSizes() const;
    std::vector<const IFTDistribution2D *> getPropabilityDistributions() const;
    bool getIntegrationOverXi() const { return m_integrate_xi; }
    double getDampingLength() const { return m_damping_length;}

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    void transformToPrincipalAxes(double qx, double qy, double gamma,
            double delta, double& q_pa_1, double& q_pa_2) const;
    double m_lattice_lengths[2]; //!< the size of unit cell
    double m_alpha_lattice; //!< Angle between lattice basis vectors
    double m_xi; //!< Orientation of the lattice wrt beam axis x
    bool m_integrate_xi; //!< Integrate over the orientation xi
    IFTDistribution2D *m_pdfs[2];
    double m_damping_length;
    bool m_use_damping_length;
    double m_domain_sizes[2]; //!< Coherence domain sizes
private:

    //! Returns interference function for fixed rotation xi
    double interferenceForXi(double xi, void *params) const;

    //! Returns interference function for fixed xi in 1d
    double interference1D(double qx, double qy, double xi, size_t index) const;

    complex_t FTPDF(double qx, double qy, double xi, size_t index) const;

    mutable double m_qx;
    mutable double m_qy;

};

#endif /* INTERFERENCEFUNCTION2DPARACRYSTAL_H_ */


