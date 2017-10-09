// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DParaCrystal.h
//! @brief     Defines class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTION2DPARACRYSTAL_H
#define INTERFERENCEFUNCTION2DPARACRYSTAL_H

#include "IInterferenceFunction.h"
#include "Complex.h"
#include "FTDistributions2D.h"
#include "Lattice2D.h"
#include <memory>

template <class T> class IntegratorReal;
class IFTDistribution2D;

//! Interference function of 2D paracrystal.
//! @ingroup interference

class BA_CORE_API_ InterferenceFunction2DParaCrystal : public IInterferenceFunction
{
public:
    InterferenceFunction2DParaCrystal(const Lattice2D& lattice, double damping_length = 0.0,
                                      double domain_size_1 = 0.0,
                                      double domain_size_2 = 0.0);

    InterferenceFunction2DParaCrystal(double length_1, double length_2, double alpha,
                                      double xi = 0.0, double damping_length = 0.0);

    ~InterferenceFunction2DParaCrystal() final;

    InterferenceFunction2DParaCrystal* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    static InterferenceFunction2DParaCrystal* createSquare(double lattice_length,
                                                           double damping_length = 0.0,
                                                           double domain_size_1 = 0.0,
                                                           double domain_size_2 = 0.0);
    static InterferenceFunction2DParaCrystal* createHexagonal(double lattice_length,
                                                              double damping_length = 0.0,
                                                              double domain_size_1 = 0.0,
                                                              double domain_size_2 = 0.0);

    void setDomainSizes(double size_1, double size_2);

    void setProbabilityDistributions(const IFTDistribution2D& pdf_1,
                                     const IFTDistribution2D& pdf_2);

    void setDampingLength(double damping_length);

    double evaluate(const kvector_t q) const final;

    std::vector<double> domainSizes() const;

    void setIntegrationOverXi(bool integrate_xi);
    bool integrationOverXi() const { return m_integrate_xi; }
    double dampingLength() const { return m_damping_length; }

    const Lattice2D& lattice() const;

    double getParticleDensity() const final;

    std::vector<const INode*> getChildren() const;

private:
    InterferenceFunction2DParaCrystal(const InterferenceFunction2DParaCrystal& other);
    void setLattice(const Lattice2D& lattice);

    void init_parameters();
    double interferenceForXi(double xi) const;
    double interference1D(double qx, double qy, double xi, size_t index) const;
    complex_t FTPDF(double qx, double qy, double xi, size_t index) const;
    void transformToPrincipalAxes(double qx, double qy, double gamma, double delta, double& q_pa_1,
                                  double& q_pa_2) const;

    bool m_integrate_xi; //!< Integrate over the orientation xi
    std::unique_ptr<IFTDistribution2D> m_pdf1, m_pdf2;
    std::unique_ptr<Lattice2D> m_lattice;
    double m_damping_length; //!< Damping length for removing delta function singularity at q=0.
    double m_domain_sizes[2]; //!< Coherence domain sizes
    mutable double m_qx;
    mutable double m_qy;
#ifndef SWIG
    std::unique_ptr<IntegratorReal<InterferenceFunction2DParaCrystal>> mP_integrator;
#endif
};

#endif // INTERFERENCEFUNCTION2DPARACRYSTAL_H
