// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitObject.h
//! @brief     Defines class FitObject.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITOBJECT_H
#define FITOBJECT_H

#include "IParameterized.h"
#include "Simulation.h"
#include "OutputData.h"
#include "ChiSquaredModule.h"

//! @class FitObject
//! @ingroup fitting_internal
//! @brief Single simulation description, real data and chi2 module (used by FitSuite)

class BA_CORE_API_ FitObject : public IParameterized
{
 public:
    FitObject(const Simulation& simulation,
              const OutputData<double >& real_data,
              const IChiSquaredModule& chi2_module=ChiSquaredModule(),
              double weight = 1);

    ~FitObject();

    //! Returns simulation
    const Simulation *getSimulation() const { return m_simulation; }

    Simulation *getSimulation() { return m_simulation; }

    //! Sets simulation
    void setSimulation(const Simulation& simulation) {
        delete m_simulation; m_simulation = simulation.clone(); }

    //! Returns real data
    const OutputData<double> *getRealData() const { return m_real_data; }
    //! Sets real data
    void setRealData(const OutputData<double >& real_data);

    //! Returns simulated data
//    const OutputData<double> *getSimulationData() const {
//        return m_simulation->getOutputData(); }
    const OutputData<double> *getSimulationData() const {
        return m_chi2_module->getSimulationData(); }


    //! Returns chi2 module
    const IChiSquaredModule *getChiSquaredModule() const {
        return m_chi2_module; }

    IChiSquaredModule *getChiSquaredModule() { return m_chi2_module; }

    //! Sets chi2 module
    void setChiSquaredModule(const IChiSquaredModule& chi2_module) {
        delete m_chi2_module; m_chi2_module = chi2_module.clone(); }

    //! Returns chi squared value
    double calculateChiSquared();

    //! Adds parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(
        std::string path, ParameterPool *external_pool,
        int copy_number=-1) const;

    //! Returns weight of data set in chi2 calculations
    double getWeight() const { return m_weight; }

    //! Returns size of data
    size_t getSizeOfData() const { return m_real_data->getAllocatedSize(); }

 protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters() {}

 private:
    FitObject(const FitObject& );
    FitObject& operator=(const FitObject& );

    Simulation* m_simulation;       //!< external simulation (not owned by this)
    OutputData<double>* m_real_data;  //!< real data
    IChiSquaredModule* m_chi2_module; //!< chi2 module
    double m_weight;                //!< weight of data set in chi2 calculations
};

#endif // FITOBJECT_H


