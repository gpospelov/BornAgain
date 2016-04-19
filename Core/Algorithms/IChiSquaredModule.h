// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/IChiSquaredModule.h
//! @brief     Declares class IChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICHISQUAREDMODULE_H_
#define ICHISQUAREDMODULE_H_

#include "ISquaredFunction.h"
#include "IIntensityNormalizer.h"
#include "IIntensityFunction.h"
#include "FitElement.h"


//! @class IChiSquaredModule
//! @ingroup algorithms_internal
//! @brief Interface for ChiSquaredModule for chi2 calculations.
//! Until BornAgain-1.1, there was another child, ChiSquaredFrequency.

class BA_CORE_API_ IChiSquaredModule : public ICloneable
{
public:
    IChiSquaredModule();
    virtual ~IChiSquaredModule();

    //! clone method
    virtual IChiSquaredModule* clone() const = 0;

    //! Returns squared function
    const ISquaredFunction* getSquaredFunction() const {
        return mp_squared_function; }

    //! Sets squared function
    void setChiSquaredFunction(ISquaredFunction *squared_function);
    void setChiSquaredFunction(const ISquaredFunction& squared_function);

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

    virtual void processFitElements(std::vector<FitElement>::iterator,
                                    std::vector<FitElement>::iterator){}

protected:
    IChiSquaredModule(const IChiSquaredModule& other);

    ISquaredFunction* mp_squared_function;
    IIntensityNormalizer* mp_data_normalizer;
    IIntensityFunction * mp_intensity_function;
};

#endif /* ICHISQUAREDMODULE_H_ */
