// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObject.h
//! @brief     Defines class FitObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECT_H
#define FITOBJECT_H

#include "INode.h"
#include "OutputData.h"
#include "SimulationResult.h"
#include <memory>

class FitElement;
class Simulation;
class IIntensityNormalizer;
class IHistogram;

//! Holds simulation description and real data to run the fit.
//! @ingroup fitting_internal

class BA_CORE_API_ FitObject : public INode
{
public:
    //! FitObject constructor
    //! @param simulation The simulation to run
    //! @param real_data The real data
    //! @param weight Weight of dataset in chi2 calculations
    //! @param adjust_detector_to_data Detector axes will be adjusted to real data axes, if true
    FitObject(const Simulation& simulation, const OutputData<double>& real_data,
              double weight = 1);

    virtual ~FitObject();

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    //! Returns weight of data set in chi2 calculations.
    double weight() const { return m_weight; }

    //! Returns the size of the data. It is equal to the number of non-masked detector channels
    //! which will participate in chi2 calculations.
    size_t numberOfFitElements() const;

    void prepareFitElements(std::vector<FitElement>& fit_elements, double weight,
                            IIntensityNormalizer* =0);

    std::vector<const INode*> getChildren() const;

    //! Returns simulation result.
    SimulationResult simulationResult() const;

    //! Returns experimental data.
    SimulationResult experimentalData() const;

    //! Returns relative difference between simulation and experimental data.
    SimulationResult relativeDifference() const;

    void runSimulation();

    //! Returns one dimensional array representing experimental data.
    //! Masked areas and the area outside of region of interest are not included.
    std::vector<double> experimental_array() const;

    //! Returns one dimensional array representing simulated intensities data.
    //! Masked areas and the area outside of region of interest are not included.
    std::vector<double> simulation_array() const;

private:
    void init_dataset(const OutputData<double>& real_data);

    std::unique_ptr<Simulation> m_simulation;
    SimulationResult m_simulation_result;
    SimulationResult m_experimental_data;
    double m_weight;
    size_t m_fit_elements_count;
};

#endif // FITOBJECT_H
