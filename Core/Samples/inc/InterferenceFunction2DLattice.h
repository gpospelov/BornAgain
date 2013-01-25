#ifndef INTERFERENCEFUNCTION2DLATTICE_H_
#define INTERFERENCEFUNCTION2DLATTICE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   InterferenceFunction2DLattice.h
//! @brief  Definition of InterferenceFunction2DLattice class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 22, 2013

#include "IInterferenceFunction.h"
#include "Lattice2DIFParameters.h"
#include "FTDistributions.h"

class InterferenceFunction2DLattice : public IInterferenceFunction
{
public:
    InterferenceFunction2DLattice(const Lattice2DIFParameters &lattice_params);
    virtual ~InterferenceFunction2DLattice() {}

    virtual InterferenceFunction2DLattice *clone() const {
        InterferenceFunction2DLattice *p_clone = new InterferenceFunction2DLattice(m_lattice_params);
        p_clone->setProbabilityDistribution(*mp_pdf);
        return p_clone;
    }

    void setProbabilityDistribution(const IFTDistribution2D &pdf);

    virtual double evaluate(const cvector_t &q) const;
protected:
    double interferenceAtOneRecLatticePoint(double qx, double qy) const;
    void transformToPrincipalAxes(double qx, double qy, double gamma, double delta, double &q_pa_1, double &q_pa_2) const;
    void calculateReciprocalVectorFraction(double qx, double qy, double &qx_frac, double &qy_frac) const;
    Lattice2DIFParameters m_lattice_params;
    IFTDistribution2D *mp_pdf;
private:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();
    void initialize_rec_vectors();
    double m_asx, m_asy;
    double m_bsx, m_bsy;
};

#endif /* INTERFERENCEFUNCTION2DLATTICE_H_ */
