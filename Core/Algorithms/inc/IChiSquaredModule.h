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

//! Interface for ChiSquaredModule, ChiSquaredFrequency.

class IChiSquaredModule : public ICloneable
{
 public:
    IChiSquaredModule();

    virtual ~IChiSquaredModule();

    //! clone method
    virtual IChiSquaredModule* clone() const = 0;

    //! Returns output data which contains chi^2 values
    virtual OutputData<double>* createChi2DifferenceMap() const=0;

    //! Returns chi squared value
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

    //! Sets squared function
    void setChiSquaredFunction(const ISquaredFunction& squared_function);

    //! Returns squared function
    const ISquaredFunction* getSquaredFunction() const {
        return mp_squared_function; }

    //! Sets fitting data selector
    virtual void setFittingDataSelector(const IFittingDataSelector& selector);

    //! Returns fitting data selector
    virtual const IFittingDataSelector* getFittingDataSelector() const {
        return mp_data_selector; }

    //! Sets data normalizer
    virtual void setOutputDataNormalizer(
        const IOutputDataNormalizer& data_normalizer);

    //! Returns data normalizer
    virtual const IOutputDataNormalizer* getOutputDataNormalizer() const {
        return mp_data_normalizer; }

    //! Returns data normalizer, non-const version, needed to set internals.
    virtual IOutputDataNormalizer* getOutputDataNormalizer() {
        return mp_data_normalizer; }

    //! Sets whether intensity be squared
    virtual void setIntensitySqrt( bool val ) { m_intensity_sqrt = val; }

    //! Sets whether intensity be reduced to logarithm
    virtual void setIntensityLog ( bool val ) { m_intensity_log  = val; }

    //! Returns true if intensity is to be squared
    virtual bool getIntensitySqrt() const { return m_intensity_sqrt; }

    //! Returns true intensity is to be reduced to logarithm
    virtual bool getIntensityLog () const { return m_intensity_log; }

    //! Returns last calculated chi squared value.
    virtual double getValue() const { return m_chi2_value; }

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
    IOutputDataNormalizer* mp_data_normalizer;
    int m_ndegree_of_freedom;
    bool m_intensity_sqrt;
    bool m_intensity_log;

    double m_chi2_value;
};

#endif /* ICHISQUAREDMODULE_H_ */
