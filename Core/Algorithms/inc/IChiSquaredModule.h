// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IChiSquaredModule.h
//! @brief     Defines class IChiSquaredModule.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICHISQUAREDMODULE_H_
#define ICHISQUAREDMODULE_H_

#include "IFittingDataSelector.h"
#include "ISquaredFunction.h"
#include "IIntensityNormalizer.h"
#include "IIntensityFunction.h"


//! @class IChiSquaredModule
//! @ingroup algorithms_internal
//! @brief Interface for ChiSquaredModule, ChiSquaredFrequency for chi2 calculations.

class BA_CORE_API_ IChiSquaredModule : public ICloneable
{
public:
    IChiSquaredModule();
    virtual ~IChiSquaredModule();

    //! clone method
    virtual IChiSquaredModule* clone() const = 0;

    //! Returns output data which contains chi^2 values
    virtual OutputData<double>* createChi2DifferenceMap() const=0;

    //! Returns chi squared value.
    virtual double calculateChiSquared() = 0;

    //! Returns real data
    const OutputData<double>* getRealData() const {
        return mp_real_data; }

    //! Returns simulated data
    const OutputData<double>* getSimulationData() const {
        return mp_simulation_data; }

    //! Sets real and simulated data pair
    void setRealAndSimulatedData(
        const OutputData<double >& real_data,
        const OutputData<double >&simulation_data);

    //! Returns squared function
    const ISquaredFunction* getSquaredFunction() const {
        return mp_squared_function; }

    //! Sets squared function
    void setChiSquaredFunction(ISquaredFunction *squared_function);
    void setChiSquaredFunction(const ISquaredFunction& squared_function);

    //! Returns fitting data selector
    virtual const IFittingDataSelector* getFittingDataSelector() const {
        return mp_data_selector; }

    //! Sets fitting data selector.
    virtual void setFittingDataSelector(const IFittingDataSelector& selector);

    //! Returns data normalizer.
    virtual const IIntensityNormalizer* getIntensityNormalizer() const {
        return mp_data_normalizer; }

    //! Returns data normalizer, non-const version needed to set internals.
    virtual IIntensityNormalizer* getIntensityNormalizer() {
        return mp_data_normalizer; }

    //! Sets data normalizer
    virtual void setIntensityNormalizer(
        const IIntensityNormalizer& data_normalizer);

    //! Returns data rescaler.
    virtual const IIntensityFunction* getIntensityFunction() const {
        return mp_intensity_function; }

    //! Sets data rescaler.
    virtual void setIntensityFunction(
        const IIntensityFunction& intensity_function);

    //! Sets number of degree of freedom.
    void setNdegreeOfFreedom(int ndegree_of_freedom) {
        m_ndegree_of_freedom = ndegree_of_freedom; }

    //! Returns residual between data and simulation for single element.
    virtual double getResidualValue(size_t /* index */) const {
        throw NotImplementedException(
            "IChiSquaredModule::getResidualValue() -> "
            "Error! Not implemented."); }

protected:
    IChiSquaredModule(const IChiSquaredModule& other);

    virtual void initWeights();
    OutputData<double>* mp_real_data;
    OutputData<double>* mp_simulation_data;
    OutputData<double>* mp_weights;
    ISquaredFunction* mp_squared_function;
    IFittingDataSelector* mp_data_selector;
    IIntensityNormalizer* mp_data_normalizer;
    IIntensityFunction * mp_intensity_function;
    int m_ndegree_of_freedom;
};

#endif /* ICHISQUAREDMODULE_H_ */
