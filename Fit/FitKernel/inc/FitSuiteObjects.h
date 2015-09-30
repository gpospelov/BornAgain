// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitSuiteObjects.h
//! @brief     Defines class FitSuiteObjects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEOBJECTS_H
#define FITSUITEOBJECTS_H

#include "IParameterized.h"
#include "GISASSimulation.h"
#include "OutputData.h"
#include "FitObject.h"
#include "SafePointerVector.h"
#include "FitElement.h"

#include <vector>

//! @class FitSuiteObjects
//! @ingroup fitting_internal
//! @brief class containing vector FitObject's (simulation and real data) to fit

class BA_CORE_API_  FitSuiteObjects : public IParameterized
{
 public:
    typedef SafePointerVector<FitObject > FitObjects_t;

    FitSuiteObjects();
    virtual ~FitSuiteObjects(){}

    //! clear all data
    void clear();

    //! Returns number of fit items
    size_t size() const { return m_fit_objects.size(); }

    //! Adds to kit pair of (simulation, real data) for consecutive simulation and chi2 module
    void add(const GISASSimulation& simulation,
             const OutputData<double>& real_data,
             const IChiSquaredModule& chi2_module, double weight = 1.0);

    //! loop through all defined simulations and run them
    void runSimulations();

    //! Returns total number of data points
    size_t getSizeOfDataSet() const;

    //! Returns sum of chi squared values for all fit objects
    double getChiSquaredValue() const { return m_chi_squared_value; }

    //! Returns sum of chi squared values for all fit objects
    double calculateChiSquaredValue();

    double calculateChiSquaredValueNew();

    //! Returns residuals for single data element
    //! @pars global_index index accross all OutputData defined
    double getResidualValue(size_t global_index);

    //! Returns simulation for read access.
//    const GISASSimulation *getSimulation(size_t i_item = 0) const {
//        return m_fit_objects[check_index(i_item)]->getSimulation(); }

    //! Returns simulation for write access.
//    GISASSimulation *getSimulation(size_t i_item = 0) {
//        return m_fit_objects[check_index(i_item)]->getSimulation(); }

    //! Returns real data
    const OutputData<double> * getRealData(size_t i_item = 0) const {
        return m_fit_objects[check_index(i_item)]->getRealData(); }

    //! Sets real data
//    void setRealData(const OutputData<double >& real_data, size_t i_item = 0) {
//        m_fit_objects[check_index(i_item)]->setRealData(real_data);}

    //! Returns simulated data
    const OutputData<double> * getSimulationData(size_t i_item = 0) const { return m_fit_objects[check_index(i_item)]->getSimulationData(); }

    //! Returns fit object
    const FitObject *getObject(size_t i_item = 0) const {
        return m_fit_objects[check_index(i_item)]; }

    FitObject *getObject(size_t i_item = 0) {
        return m_fit_objects[check_index(i_item)]; }

    //! Adds parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(
        std::string path, ParameterPool *external_pool,
        int copy_number=-1) const;

    //! Sets simulation normalize flag
//    void setSimulationNormalize(bool simulation_normalize) {
//        m_simulation_normalize = simulation_normalize; }

    void setNfreeParameters(int nfree_parameters ) {
        m_nfree_parameters = nfree_parameters; }

    //! Returns chi-squared map
    OutputData<double> * getChiSquaredMap(size_t i_item = 0);


 protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters() {}

    //! Returns maximum intensity in simulated data
    double getSimulationMaxIntensity();

    //! Returns object and calculate index of data element for given global data element index
    const FitObject *getObjectForGlobalDataIndex(
        size_t global_index, size_t& local_index);

 private:
    //! disabled copy constructor and assignment operator
    FitSuiteObjects& operator=(const FitSuiteObjects& );
    FitSuiteObjects(const FitSuiteObjects& );

    //! Checks if index inside vector bounds
    inline size_t check_index(size_t index) const {
        return index < m_fit_objects.size() ?
            index :
            throw OutOfBoundsException("FitSuiteKit::check() -> "
                                       "Index outside of range"); }

    //! Set of simulations and corresponding real data.
    FitObjects_t m_fit_objects;

    //! Sum of weights of fit sets.
    double m_total_weight;

//    bool m_simulation_normalize;

    //! number of free fit parameters for normalization
    int m_nfree_parameters;

    double m_chi_squared_value;

    std::vector<FitElement> m_fit_elements;
};

#endif // FITSUITEKIT_H


