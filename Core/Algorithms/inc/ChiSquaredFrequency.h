#ifndef CHISQUAREDFREQUENCY_H_
#define CHISQUAREDFREQUENCY_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ChiSquaredFrequency.h
//! @brief  Definition of ChiSquaredFrequency class
//! @author Scientific Computing Group at FRM II
//! @date   Nov 5, 2012

#include "IChiSquaredModule.h"

class ChiSquaredFrequency : public IChiSquaredModule
{
public:
    ChiSquaredFrequency(const OutputData<double> &real_data);
    virtual ~ChiSquaredFrequency();

    virtual double calculateChiSquared(const OutputData<double> *p_simulation_data=0);

    void setCutoff(double cutoff) {
        if (cutoff>=0.0 && cutoff<=1.0) m_cutoff = cutoff;
    }
    double getCutoff() { return m_cutoff; }

    //! return output data which contains chi^2 values
    virtual OutputData<double > *createChi2DifferenceMap() const;
protected:
    virtual void initWeights();
    OutputData<complex_t> *mp_real_ft;
    OutputData<complex_t> *mp_simulation_ft;
    double m_cutoff;
};


#endif /* CHISQUAREDFREQUENCY_H_ */
