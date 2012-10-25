#ifndef INTERFERENCEFUNCTION2DPARACRYSTAL_H_
#define INTERFERENCEFUNCTION2DPARACRYSTAL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   InterferenceFunction2DParaCrystal.h
//! @brief  Definition of InterferenceFunction2DParaCrystal class
//! @author Scientific Computing Group at FRM II
//! @date   Oct 17, 2012

#include "IInterferenceFunction.h"

class InterferenceFunction2DParaCrystal : public IInterferenceFunction
{
public:
    InterferenceFunction2DParaCrystal(double peak_distance, double alpha_lattice, double width, double corr_length=0.0);
    virtual ~InterferenceFunction2DParaCrystal() {}
    virtual InterferenceFunction2DParaCrystal *clone() const {
        InterferenceFunction2DParaCrystal *p_new = new InterferenceFunction2DParaCrystal(m_peak_distance, m_alpha_lattice, m_width, m_corr_length);
        p_new->setDomainSizes(m_domain_size_1, m_domain_size_2);
        return p_new;
    }
    static InterferenceFunction2DParaCrystal *createSquare(double peak_distance, double width, double corr_length=0.0,
            double domain_size_1=0.0, double domain_size_2=0.0) {
        InterferenceFunction2DParaCrystal *p_new = new InterferenceFunction2DParaCrystal(peak_distance, M_PI/2.0, width, corr_length);
        p_new->setDomainSizes(domain_size_1, domain_size_2);
        return p_new;        return new InterferenceFunction2DParaCrystal(peak_distance, M_PI/2.0, width, corr_length);
    }
    static InterferenceFunction2DParaCrystal *createHexagonal(double peak_distance, double width, double corr_length=0.0,
            double domain_size_1=0.0, double domain_size_2=0.0) {
        InterferenceFunction2DParaCrystal *p_new = new InterferenceFunction2DParaCrystal(peak_distance, 2.0*M_PI/3.0, width, corr_length);
        p_new->setDomainSizes(domain_size_1, domain_size_2);
        return p_new;
    }

    void setDomainSizes(double size_1, double size_2) {
        m_domain_size_1 = size_1;
        m_domain_size_2 = size_2;
    }

    virtual double evaluate(const cvector_t &q) const;

protected:
    double m_peak_distance;
    double m_alpha_lattice; //!< Angle between lattice basis vectors
    double m_width;
    double m_corr_length;
    bool m_use_corr_length;
    double m_domain_size_1;
    double m_domain_size_2;
private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    InterferenceFunction2DParaCrystal(const InterferenceFunction2DParaCrystal &);
    InterferenceFunction2DParaCrystal &operator=(const InterferenceFunction2DParaCrystal &);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! Calculate interference function for fixed rotation xi
    double interferenceForXi(double xi) const;

    //! calculate interference function for fixed xi in 1d
    double interference1D(double qpar, double xi, double domain_size) const;

    //TODO: replace these with strategy pattern for different algorithms
    complex_t FTCauchyDistribution(double qpar, double xi) const;

    mutable double m_qpar;
};

double wrapFunctionForGSL(double xi, void* p_unary_function);



#endif /* INTERFERENCEFUNCTION2DPARACRYSTAL_H_ */
