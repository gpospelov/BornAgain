// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitObject.cpp
//! @brief     Implements class FitObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitObject.h"
#include "Exceptions.h"
#include "MessageService.h"
#include <boost/scoped_ptr.hpp>

FitObject::FitObject(
    const GISASSimulation& simulation, const OutputData<double >& real_data,
    const IChiSquaredModule& chi2_module, double weight)
    : m_simulation(simulation.clone())
    , m_real_data(real_data.clone())
    , m_chi2_module(chi2_module.clone())
    , m_weight(weight)
{
    setName("FitObject");
    if( !m_real_data->hasSameShape(*m_simulation->getOutputData()) ) {
        msglog(MSG::INFO) << "FitObject::FitObject() -> Info. "
            "Real data and output data in the simulation have different shape. "
            "Adjusting simulation's detector.";
    } else {
        msglog(MSG::INFO) << "FitObject::FitObject() -> Info. "
            "Real data and output data in the simulation have same shape.";
    }
    m_simulation->setDetectorParameters(*m_real_data);
}

FitObject::~FitObject()
{
    delete m_simulation;
    delete m_real_data;
    delete m_chi2_module;
}

//! Sets real data
//void FitObject::setRealData(const OutputData<double >& real_data)
//{
//    delete m_real_data;
//    m_real_data = real_data.clone();
//    if( m_simulation) {
//        if( !m_real_data->hasSameShape(*m_simulation->getOutputData()) ) {
//            msglog(MSG::INFO) << "FitObject::setRealData() -> "
//                "Real data and the detector have different shape. "
//                "Adjusting detector...";
//        } else {
//            msglog(MSG::INFO) << "FitObject::setRealData() -> "
//                "Real data and the detector have same shape. "
//                "No need to adjust detector.";
//        }
//        m_simulation->setDetectorParameters(*m_real_data);
//    }
//}

//! Updates m_chi2_module; returns chi squared value.

double FitObject::calculateChiSquared()
{
    boost::scoped_ptr<OutputData<double> > P_sim_data(m_simulation->getIntensityData());
    m_chi2_module->setRealAndSimulatedData(*m_real_data, *P_sim_data.get());
    if(m_simulation->getInstrument().getDetector()->hasMasks()) {
        m_chi2_module->setMasks(*m_simulation->getInstrument().getDetector()->getDetectorMask()->getMaskData());
    }

    return m_chi2_module->calculateChiSquared();
}

//! Adds parameters from local pool to external pool
std::string FitObject::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path = IParameterized::addParametersToExternalPool(
        path, external_pool, copy_number);

    // add parameters of the simulation
    if(m_simulation)
        m_simulation->addParametersToExternalPool(new_path, external_pool, -1);

    if(m_chi2_module) {
        const IIntensityNormalizer* data_normalizer =
            m_chi2_module->getIntensityNormalizer();
        if(data_normalizer)
            data_normalizer->addParametersToExternalPool(
                new_path, external_pool, -1);
    }

    return new_path;
}
