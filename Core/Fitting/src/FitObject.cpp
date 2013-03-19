// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Fitting/FitObject.cpp 
//! @brief     Implements class FitObject.
//
// ************************************************************************** //

#include "FitObject.h"
#include "Exceptions.h"

FitObject::FitObject(const Simulation &simulation, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module, double weight)
    : m_simulation(simulation.clone())
    , m_real_data(real_data.clone())
    , m_chi2_module(chi2_module.clone())
    , m_weight(weight)
{
    setName("FitObject");
    if( !m_real_data->hasSameShape(*m_simulation->getOutputData()) ) {
        std::cout << "FitObject::FitObject() -> Info. Real data and output data in the simulation have different shape. Adjusting simulation's detector." << std::endl;
    } else {
        std::cout << "FitObject::FitObject() -> Info. Real data and output data in the simulation have same shape. Ok." << std::endl;
    }
    m_simulation->setDetectorParameters(*m_real_data);
}

FitObject::~FitObject()
{
    delete m_simulation;
    delete m_real_data;
    delete m_chi2_module;
}

//! set real data
void FitObject::setRealData(const OutputData<double > &real_data)
{
    delete m_real_data;
    m_real_data = real_data.clone();
    if( m_simulation) {
        if( !m_real_data->hasSameShape(*m_simulation->getOutputData()) ) {
            std::cout << "FitObject::setRealData() -> Real data and the detector have different shape. Adjusting detector..." << std::endl;
        } else {
            std::cout << "FitObject::setRealData() -> Real data and the detector have same shape. No need to adjust detector." << std::endl;
        }
        m_simulation->setDetectorParameters(*m_real_data);
    }
}

//! calculate chi squared value
double FitObject::calculateChiSquared()
{
    m_chi2_module->setRealAndSimulatedData(*m_real_data, *m_simulation->getOutputData());
    return m_chi2_module->calculateChiSquared();
}

//! add parameters from local pool to external pool
std::string FitObject::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the simulation
    if(m_simulation) m_simulation->addParametersToExternalPool(new_path, external_pool, -1);

    if(m_chi2_module) {
        const IOutputDataNormalizer *data_normalizer = m_chi2_module->getOutputDataNormalizer();
        if(data_normalizer) {
            data_normalizer->addParametersToExternalPool(new_path, external_pool, -1);
        }
    }

    return new_path;
}

//! ?
void FitObject::init_parameters()
{
}
