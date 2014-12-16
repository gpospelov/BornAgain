// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SpecularSimulation.h
//! @brief     Defines class SpecularSimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARSIMULATION_H
#define SPECULARSIMULATION_H

#include "Simulation.h"
//#include "MultiLayerRTCoefficients.h"
#include "OutputData.h"

#ifndef GCCXML_SKIP_THIS
#include "SpecularMatrix.h"
#endif
#include <vector>


//! @class SpecularSimulation
//! @ingroup simulation
//! @brief Main class to run a specular simulation.

class BA_CORE_API_ SpecularSimulation : public ICloneable, public IParameterized
{
public:
    typedef boost::shared_ptr<const ILayerRTCoefficients> LayerRTCoefficients;
    typedef std::vector<LayerRTCoefficients> MultiLayerRTCoefficients;

    SpecularSimulation();
    SpecularSimulation(const ISample& sample);
    SpecularSimulation(SampleBuilder_t sample_builder);
    ~SpecularSimulation();

    SpecularSimulation *clone() const;

    //! Put into a clean state for running a simulation
    void prepareSimulation();

    //! Run a simulation with the current parameter settings
    void runSimulation();

    //! Sets the sample to be tested
    void setSample(const ISample& sample);

    //! Returns the sample
    ISample *getSample() const;

    //! Sets the sample builder
    void setSampleBuilder(SampleBuilder_t sample_builder);

    //! return sample builder
    SampleBuilder_t getSampleBuilder() const;

    //! Sets beam parameters with alpha_i of the beam defined in the range
    void setBeamParameters(double lambda, const IAxis &alpha_axis);
    void setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max);

    //! returns alpha_i axis
    const IAxis *getAlphaAxis() const;

    //! returns vector containing reflection coefficients for all alpha_i angles for given layer index
    std::vector<complex_t > getScalarR(int i_layer = 0) const;

    //! returns vector containing transmission coefficients for all alpha_i angles for given layer index
    std::vector<complex_t > getScalarT(int i_layer = 0) const;

    //! returns vector containing Kz coefficients for all alpha_i angles for given layer index
    std::vector<complex_t > getScalarKz(int i_layer = 0) const;

//    const ILayerRTCoefficients *getLayerRTCoefficients(int i_alpha, int i_layer) const;

protected:
    SpecularSimulation(const SpecularSimulation& other);

    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    //! calculates RT coefficients for multilayer without magnetic materials
    void collectRTCoefficientsScalar(const MultiLayer *multilayer);

    //! calculates RT coefficients for multilayer with magnetic materials
    void collectRTCoefficientsMatrix(const MultiLayer *multilayer);

    ISample *m_sample;
    SampleBuilder_t m_sample_builder;
    IAxis *m_alpha_i_axis;
    double m_lambda;

#ifndef GCCXML_SKIP_THIS
    OutputData<SpecularMatrix::MultiLayerCoeff_t> *m_scalar_data;

//    OutputData<MultiLayerRTCoefficients> m_data;
#endif
};


#endif
