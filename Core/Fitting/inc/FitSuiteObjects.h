// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/FitSuiteObjects.h
//! @brief     Defines class FitSuiteObjects.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FITSUITEOBJECTS_H
#define FITSUITEOBJECTS_H

#include "IParameterized.h"
#include "Simulation.h"
#include "OutputData.h"
#include "FitObject.h"
#include "SafePointerVector.h"

#include <vector>

//! class containing vector FitObject's (simulation and real data) to fit

class FitSuiteObjects : public IParameterized
{
public:
    typedef SafePointerVector<FitObject > FitObjects_t;

    FitSuiteObjects();
    virtual ~FitSuiteObjects(){}

    //! clear all data
    void clear();

    //! return number of fit items
    size_t size() const { return m_fit_objects.size(); }

    //! add to kit pair of (simulation, real data) for consecutive simulation and chi2 module
    void add(const Simulation &simulation, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module, double weight = 1.0);

    //! loop through all defined simulations and run them
    void runSimulations();

    //! get total number of data points
    size_t getSizeOfDataSet() const;

    //! get sum of chi squared values for all fit objects
    double getChiSquaredValue() const { return m_chi_squared_value; }

    //! calculate sum of chi squared values for all fit objects
    double calculateChiSquaredValue();

    //! get residuals for single data element
    //! @pars global_index index accross all OutputData defined
    double getResidualValue(size_t global_index);

    //! get simulation
    const Simulation *getSimulation(size_t i_item = 0) const { return m_fit_objects[check_index(i_item)]->getSimulation(); }
    Simulation *getSimulation(size_t i_item = 0) { return m_fit_objects[check_index(i_item)]->getSimulation(); }

    //! get real data
    const OutputData<double> * getRealData(size_t i_item = 0) const { return m_fit_objects[check_index(i_item)]->getRealData(); }
    //! set real data
    void setRealData(const OutputData<double > &real_data, size_t i_item = 0) { m_fit_objects[check_index(i_item)]->setRealData(real_data);}

    //! get chi2 module
//    const IChiSquaredModule *getChiSquaredModule(size_t i_item = 0) const { return m_fit_objects[check_index(i_item)]->getChiSquaredModule(); }
//    IChiSquaredModule *getChiSquaredModule(size_t i_item = 0) { return m_fit_objects[check_index(i_item)]->getChiSquaredModule(); }

    //! get simulated data
    const OutputData<double> * getSimulationData(size_t i_item = 0) const { return m_fit_objects[check_index(i_item)]->getSimulationData(); }

    //! get fit object
    const FitObject *getObject(size_t i_item = 0) const { return m_fit_objects[check_index(i_item)]; }
    FitObject *getObject(size_t i_item = 0) { return m_fit_objects[check_index(i_item)]; }

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

    //! set simulation normalize flag
    void setSimulationNormalize(bool simulation_normalize) { m_simulation_normalize = simulation_normalize; }

    void setNfreeParameters(int nfree_parameters ) { m_nfree_parameters = nfree_parameters; }

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! calculate maximum intensity in simulated data
    double getSimulationMaxIntensity();

    //! return object and calculate index of data element for given global data element index
    const FitObject *getObjectForGlobalDataIndex(size_t global_index, size_t &local_index);

private:
    //! disabled copy constructor and assignment operator
    FitSuiteObjects &operator=(const FitSuiteObjects &);
    FitSuiteObjects(const FitSuiteObjects &);

    //! check if index inside vector bounds
    inline size_t check_index(size_t index) const { return index < m_fit_objects.size() ? index : throw OutOfBoundsException("FitSuiteKit::check() -> Index outside of range"); }

    FitObjects_t m_fit_objects; //!  set of simulations and corresponding real data
    double m_total_weight; //! sum of weights of fit sets
    bool m_simulation_normalize;
    int m_nfree_parameters; //! number of freefit parameters for normalization
    double m_chi_squared_value;
};

#endif // FITSUITEKIT_H
