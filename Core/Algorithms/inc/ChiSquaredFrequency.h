// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/ChiSquaredFrequency.h 
//! @brief     Defines class ChiSquaredFrequency.
//
// ************************************************************************** //

#ifndef CHISQUAREDFREQUENCY_H_
#define CHISQUAREDFREQUENCY_H_

#include "IChiSquaredModule.h"

class ChiSquaredFrequency : public IChiSquaredModule
{
public:
    ChiSquaredFrequency();
    virtual ~ChiSquaredFrequency();

    virtual double calculateChiSquared();

    void setCutoff(double cutoff) {
        if (cutoff>=0.0 && cutoff<=1.0) m_cutoff = cutoff;
    }
    double getCutoff() const { return m_cutoff; }

    //! return output data which contains chi^2 values
    virtual OutputData<double > *createChi2DifferenceMap() const;
protected:
    virtual void initWeights();
    OutputData<complex_t> *mp_real_ft;
    OutputData<complex_t> *mp_simulation_ft;
    double m_cutoff;
};


#endif /* CHISQUAREDFREQUENCY_H_ */
