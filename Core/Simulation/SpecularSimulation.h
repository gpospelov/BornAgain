// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularSimulation.h
//! @brief     Defines class SpecularSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARSIMULATION_H
#define SPECULARSIMULATION_H

#include "Simulation.h"
#include "ILayerRTCoefficients.h"
#include "OutputData.h"
#include <memory>

class IAxis;
class ISample;
class IMultiLayerBuilder;
class MultiLayer;
class Histogram1D;

//! Main class to run a specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulation : public Simulation
{
public:
    SpecularSimulation();
    SpecularSimulation(const MultiLayer& sample);
    SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder);
    virtual ~SpecularSimulation() override = default;

    virtual SpecularSimulation* clone() const override;

    //! Put into a clean state for running a simulation.
    virtual void prepareSimulation() override;

    //! Run a simulation, possibly averaged over parameter distributions.
    virtual void runSimulation() override;

    virtual void accept(INodeVisitor* visitor) const override final {visitor->visit(this);}

    virtual size_t numberOfSimulationElements() const override;

    //! Sets beam parameters with alpha_i of the beam defined in the range.
    void setBeamParameters(double lambda, const IAxis& alpha_axis, double phi_i = 0.0);
    void setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max,
                           double phi_i = 0.0);

    //! Returns a pointer to incident angle axis.
    const IAxis* getAlphaAxis() const;

    //! Returns reflectivity values \f$Reflectivity = \|R\|^2\f$ from the upper layer in the form of
    //! OutputData<double>.
    virtual OutputData<double>* getDetectorIntensity(IDetector2D::EAxesUnits units_type
                                                     = IDetector2D::DEFAULT) const override;

    //! Returns reflectivity values \f$Reflectivity = |R|^2\f$ in the form of 1D Histogram
    //! for the upper sample layer.
    Histogram1D* reflectivity() const;

    //! Returns transmissivity values \f$Transmissivity = |T|^2\f$ in the form of 1D Histogram
    //! for the sample bottom layer.
    Histogram1D* transmissivity() const;

    //! Returns vector of reflection coefficients (\f$R\f$) for all alpha_i angles for given layer index.
    std::vector<complex_t> getScalarR(size_t i_layer) const;

    //! Returns vector of transmission coefficients for all alpha_i angles for given layer index.
    std::vector<complex_t> getScalarT(size_t i_layer) const;

    //! Returns vector of Kz coefficients for all alpha_i angles for given layer index.
    std::vector<complex_t> getScalarKz(size_t i_layer) const;

private:
    typedef std::shared_ptr<const ILayerRTCoefficients> LayerRTCoefficients_t;
    typedef std::vector<LayerRTCoefficients_t> MultiLayerRTCoefficients_t;
    typedef complex_t (ILayerRTCoefficients::*DataGetter)() const;

    SpecularSimulation(const SpecularSimulation& other);

    std::unique_ptr<OutputData<double>> getData(size_t i_layer, DataGetter fn_ptr) const;

    // unused methods
    virtual void initSimulationElementVector() override {}
    virtual void transferResultsToIntensityMap() override {}
    virtual void updateIntensityMap() override {}

    //! calculates RT coefficients for multilayer without magnetic materials
    void collectRTCoefficientsScalar(const MultiLayer* multilayer);

    //! calculates RT coefficients for multilayer with magnetic materials
    void collectRTCoefficientsMatrix(const MultiLayer* multilayer);

    //! check if simulation was run already and has valid coefficients
    void checkCoefficients(size_t i_layer) const;

    //! Initializes simulation
    void initialize();

    OutputData<MultiLayerRTCoefficients_t> m_RT_coefficients;
    std::unique_ptr<IAxis> m_alpha_i_axis;
};

#endif // SPECULARSIMULATION_H
