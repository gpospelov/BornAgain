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

#include "IParameterized.h"
#include "Experiment.h"
#include "OutputData.h"
#include "ChiSquaredModule.h"


//- -------------------------------------------------------------------
//! @class FitObject
//! @brief Class to hold single experiment description, real data and chi2 module
//! Used by FitSuite
//- -------------------------------------------------------------------
class FitObject : public IParameterized
{
public:
    FitObject(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module=ChiSquaredModule());
    ~FitObject();

    //! get experiment
    const Experiment *getExperiment() const { return m_experiment; }
    Experiment *getExperiment() { return m_experiment; }
    //! set experiment
    void setExperiment(const Experiment &experiment) { delete m_experiment; m_experiment = experiment.clone(); }

    //! get real data
    const OutputData<double > *getRealData() const { return m_real_data; }
    //! set real data
    void setRealData(const OutputData<double > &real_data);

    //! get simulated data
    const OutputData<double > *getSimulationData() const { return m_experiment->getOutputData(); }

    //! get chi2 module
    const IChiSquaredModule *getChiSquaredModule() const {return m_chi2_module; }
    IChiSquaredModule *getChiSquaredModule() {return m_chi2_module; }
    //! set chi2 module
    void setChiSquaredModule(const IChiSquaredModule &chi2_module) { delete m_chi2_module; m_chi2_module = chi2_module.clone(); }

    //! calculate chi squared value
    double calculateChiSquared();

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    FitObject(const FitObject &);
    FitObject &operator=(const FitObject &);

    Experiment *m_experiment; //! external experiment (not owned by this)
    OutputData<double > *m_real_data; //! real data
    IChiSquaredModule *m_chi2_module; //! chi2 module

};

#endif // FITOBJECT_H
