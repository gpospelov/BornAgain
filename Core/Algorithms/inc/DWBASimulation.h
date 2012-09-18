#ifndef DWBASIMULATION_H_
#define DWBASIMULATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DWBASimulation.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jun 26, 2012

#include "ISimulation.h"
#include "OutputData.h"
#include "Types.h"

//- -------------------------------------------------------------------
//! @class DWBASimulation
//! @brief Calculates scattering cross sections in DWBA
//- -------------------------------------------------------------------
class DWBASimulation : public ISimulation
{
public:
    DWBASimulation();
    virtual ~DWBASimulation();

    //! Initialize the simulation with the parameters from experiment
    virtual void init(const Experiment &experiment);

    //! return output data containing calculated intensity
    const OutputData<double> &getDWBAIntensity() const;

    //! add intensity to current dwba intensity
    void addDWBAIntensity(const OutputData<double > &data_to_add);

    //! clone DWBA simulation
    virtual DWBASimulation *clone();

protected:

    virtual void resetIndex();
    virtual bool hasNext() const;
    virtual const double &next() const;
    virtual double &next();

    OutputData<double> m_dwba_intensity;
    OutputData<double> m_output_data_mask;
    cvector_t m_ki;
    double m_alpha_i;
    double getWaveLength() const;

private:
    //! copy constructor and assignment operator are hidden
    DWBASimulation(const DWBASimulation &);
    DWBASimulation &operator=(const DWBASimulation &);

};

inline const OutputData<double> &DWBASimulation::getDWBAIntensity() const {
    return m_dwba_intensity;
}

inline void DWBASimulation::addDWBAIntensity(const OutputData<double> &data_to_add) {
    m_dwba_intensity += data_to_add;
}


#endif /* DWBASIMULATION_H_ */
