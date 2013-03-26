//* ************************************************************************ *//
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IChiSquaredModule.h
//! @brief     Defines class IChiSquaredModule.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//* ************************************************************************ *//

#ifndef ICHISQUAREDMODULE_H_
#define ICHISQUAREDMODULE_H_

#include "IFittingDataSelector.h"
#include "ISquaredFunction.h"
#include "IOutputDataNormalizer.h"
#include "IIntensityFunction.h"

//! Interface for ChiSquaredModule, ChiSquaredFrequency.

class IChiSquaredModule : public ICloneable
{
 public:
    IChiSquaredModule();
    virtual ~IChiSquaredModule();

    //! clone method
    virtual IChiSquaredModule* clone() const = 0;

    //! return output data which contains chi^2 values
    virtual OutputData<double>* createChi2DifferenceMap() const=0;

    //! calculate chi dquared value
    virtual double calculateChiSquared() = 0;

    //! get real data
    const OutputData<double>* getRealData() const {
        return mp_real_data; }

    //! get simulated data
    const OutputData<double>* getSimulationData() const {
        return mp_simulation_data; }

    //! set real and simulated data pair
    void setRealAndSimulatedData(
        const OutputData<double >& real_data,
        const OutputData<double >&simulation_data);

    //! get squared function
    const ISquaredFunction* getSquaredFunction() const {
        return mp_squared_function; }

    //! set squared function
    void setChiSquaredFunction(const ISquaredFunction& squared_function);

    //! get fitting data selector
    virtual const IFittingDataSelector* getFittingDataSelector() const {
        return mp_data_selector; }

    //! set fitting data selector
    virtual void setFittingDataSelector(const IFittingDataSelector& selector);

    //! get data normalizer
    virtual const IOutputDataNormalizer* getOutputDataNormalizer() const {
        return mp_data_normalizer; }

    virtual IOutputDataNormalizer* getOutputDataNormalizer() {
        return mp_data_normalizer; }

    //! set data normalizer
    virtual void setOutputDataNormalizer(
        const IOutputDataNormalizer& data_normalizer);

    //! get data normalizer
    virtual const IIntensityFunction* getIntensityFunction() const {
        return mp_intensity_function; }

    //! set data normalizer
    virtual void setIntensityFunction(
        const IIntensityFunction& intensity_function);

    //! return last calculated chi squared value
    virtual double getValue() const { return m_chi2_value; }

    //! set number of degree of freedom
    void setNdegreeOfFreedom(int ndegree_of_freedom) {
        m_ndegree_of_freedom = ndegree_of_freedom; }

    //! return residual between data and simulation for single element
    virtual double getResidualValue(size_t /* index */) const {
        throw NotImplementedException(
            "IChiSquaredModule::getResidualValue() -> Error! Not implemented."); }

 protected:
    IChiSquaredModule(const IChiSquaredModule& other);

    virtual void initWeights();
    OutputData<double>* mp_real_data;
    OutputData<double>* mp_simulation_data;
    OutputData<double>* mp_weights;
    ISquaredFunction* mp_squared_function;
    IFittingDataSelector* mp_data_selector;
    IOutputDataNormalizer* mp_data_normalizer;
    IIntensityFunction * mp_intensity_function;
    int m_ndegree_of_freedom;

    double m_chi2_value;
};

#endif /* ICHISQUAREDMODULE_H_ */
