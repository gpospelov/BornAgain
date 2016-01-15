// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitObject.h
//! @brief     Defines class FitObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITOBJECT_H
#define FITOBJECT_H

#include "IParameterized.h"
#include "FitElement.h"
#include "OutputData.h"
#include <boost/scoped_ptr.hpp>

class GISASSimulation;
class IIntensityNormalizer;

//! @class FitObject
//! @ingroup fitting_internal
//! @brief Holds simulation description and real data to run the fit.

class BA_CORE_API_ FitObject : public IParameterized
{
public:
    //! FitObject constructor
    //! @param simulaiton The simulation to eun
    //! @param real_data The real data
    //! @param weight Weight of dataset in chi2 calculations
    FitObject(const GISASSimulation &simulation, const OutputData<double> &real_data,
              double weight = 1);

    virtual ~FitObject();

    //! Returns real (experimental) data.
    const OutputData<double> *getRealData() const;

    //! Returns simulated data.
    const OutputData<double> *getSimulationData() const;

    //! Returns weight of data set in chi2 calculations.
    double getWeight() const;

    //! Returns the size of the data. It is equal to the number of non-masked detector channels
    //! which will participate in chi2 calculations.
    size_t getSizeOfData() const;

    void prepareFitElements(std::vector<FitElement> &fit_elements, double weight,
                            IIntensityNormalizer *normalizer=0);

    OutputData<double> *getChiSquaredMap(std::vector<FitElement>::const_iterator first,
                                         std::vector<FitElement>::const_iterator last) const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters() {}

private:
    FitObject(const FitObject& );
    FitObject& operator=(const FitObject& );

    boost::scoped_ptr<GISASSimulation> m_simulation;
    boost::scoped_ptr<OutputData<double> > m_real_data;
    boost::scoped_ptr<OutputData<double> > m_simulation_data;
    double m_weight;
};

#endif // FITOBJECT_H


