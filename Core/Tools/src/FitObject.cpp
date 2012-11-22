#include "FitObject.h"
#include "Exceptions.h"


/* ************************************************************************* */
// FitObject c-tors
/* ************************************************************************* */
FitObject::FitObject(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module)
    : m_experiment(experiment.clone())
    , m_real_data(real_data.clone())
    , m_chi2_module(chi2_module.clone())
{
    if( !m_real_data->hasSameShape(*m_experiment->getOutputData()) ) {
        std::cout << "FitObject::FitObject() -> Info. Real data and output data in the experiment have different shape. Adjusting experiment's detector." << std::endl;
    } else {
        std::cout << "FitObject::FitObject() -> Info. Real data and output data in the experiment have same shape. Ok." << std::endl;
    }
    m_experiment->setDetectorParameters(*m_real_data);
}

FitObject::~FitObject()
{
}


/* ************************************************************************* */
// set real data
/* ************************************************************************* */
void FitObject::setRealData(const OutputData<double > &real_data)
{
    delete m_real_data;
    m_real_data = real_data.clone();
    if( m_experiment) {
        if( !m_real_data->hasSameShape(*m_experiment->getOutputData()) ) {
            std::cout << "FitSuiteKit::KitItem::setRealData() -> Real data and the detector have different shape. Adjusting detector..." << std::endl;
        } else {
            std::cout << "FitSuiteKit::KitItem::setRealData() -> Real data and the detector have same shape. No nedd to adjust detector." << std::endl;
        }
        m_experiment->setDetectorParameters(*m_real_data);
    }
}

