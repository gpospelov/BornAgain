// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitObject.h
//! @brief     Declares class FitObject.
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

#include "FitElement.h"
#include "IParameterized.h"
#include "OutputData.h"
#include <memory>

class GISASSimulation;
class IIntensityNormalizer;

//! @class FitObject
//! @ingroup fitting_internal
//! @brief Holds simulation description and real data to run the fit.

class BA_CORE_API_ FitObject : public IParameterized
{
public:
    //! FitObject constructor
    //! @param simulation The simulation to eun
    //! @param real_data The real data
    //! @param weight Weight of dataset in chi2 calculations
    //! @param adjust_detector_to_data Detector axes will be adjusted to real data axes, if true
    FitObject(const GISASSimulation &simulation, const OutputData<double> &real_data,
              double weight = 1, bool adjust_detector_to_data = true);

    virtual ~FitObject();

    //! Returns real (experimental) data.
    const OutputData<double> *getRealData() const;

    //! Returns simulated data.
    const OutputData<double> *getSimulationData() const;

    //! Returns simulation
    const GISASSimulation *getSimulation() const;

    //! Returns weight of data set in chi2 calculations.
    double getWeight() const;

    //! Returns the size of the data. It is equal to the number of non-masked detector channels
    //! which will participate in chi2 calculations.
    size_t getSizeOfData() const;

    void prepareFitElements(std::vector<FitElement> &fit_elements, double weight,
                            IIntensityNormalizer *normalizer=0);

    const OutputData<double> *getChiSquaredMap(std::vector<FitElement>::const_iterator first,
                                         std::vector<FitElement>::const_iterator last) const;

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters() {}

private:
    void init_dataset();
    bool same_dimensions_dataset() const;
    bool is_possible_to_adjust_simulation() const;
    std::string get_error_message() const;

    FitObject(const FitObject& );
    FitObject& operator=(const FitObject& );

    std::unique_ptr<GISASSimulation> m_simulation;
    std::unique_ptr<OutputData<double> > m_real_data;
    std::unique_ptr<OutputData<double> > m_simulation_data;
    std::unique_ptr<OutputData<double> > m_chi2_data;
    double m_weight;
    bool m_adjust_detector_to_data;
};

#endif // FITOBJECT_H
