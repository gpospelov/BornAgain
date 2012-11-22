#ifndef FITOBJECT_H
#define FITOBJECT_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitObject.h
//! @brief  Definition of FitObject class
//! @author Scientific Computing Group at FRM II
//! @date   21.11.2012


#include "Experiment.h"
#include "OutputData.h"
#include "ChiSquaredModule.h"

//- -------------------------------------------------------------------
//! @class FitObject
//! @brief Class to hold experiment description, real data and chi2 module
//! to be used by FitSuite
//- -------------------------------------------------------------------
class FitObject
{
public:
    FitObject(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module=ChiSquaredModule());
    ~FitObject();

    //! get real data
    const OutputData<double > *getRealData() const { return m_real_data; }
    //! set real data
    void setRealData(const OutputData<double > &real_data);

    //! get simulated data
    const OutputData<double > *getSimulatedData() const { return m_experiment->getOutputData(); }

    //! get chi2 module
    const IChiSquaredModule *getChiSquaredModule() const {return m_chi2_module; }
    //! set chi2 module
    void setChiSquaredModule(const IChiSquaredModule &chi2_module) { delete m_chi2_module; m_chi2_module = chi2_module.clone(); }

private:
    FitObject(const FitObject &);
    FitObject &operator=(const FitObject &);

    Experiment *m_experiment; //! external experiment (not owned by this)
    OutputData<double > *m_real_data; //! real data
    IChiSquaredModule *m_chi2_module; //! chi2 module

};

#endif // FITOBJECT_H
