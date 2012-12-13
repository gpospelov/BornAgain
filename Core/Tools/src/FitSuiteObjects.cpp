#include "FitSuiteObjects.h"



FitSuiteObjects::FitSuiteObjects() : m_total_weight(0), m_experiment_normalize(false)
{
    setName("FitSuiteObjects");
    init_parameters();
}


/* ************************************************************************* */
// clear all data
/* ************************************************************************* */
void FitSuiteObjects::clear()
{
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) delete (*it);
    m_fit_objects.clear();
}


/* ************************************************************************* */
// add to kit pair of (experiment, real data) for consecutive simulation and chi2 module
/* ************************************************************************* */
void FitSuiteObjects::add(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module, double weight)
{
    m_total_weight += weight;
    m_fit_objects.push_back(new FitObject(experiment, real_data, chi2_module, weight));
}


/* ************************************************************************* */
// loop through all defined experiments and run they simulation
/* ************************************************************************* */
void FitSuiteObjects::runSimulation()
{
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        (*it)->getExperiment()->runSimulation();
        if(m_experiment_normalize) (*it)->getExperiment()->normalize();
    }
}


/* ************************************************************************* */
// get sum of chi squared values for all fit objects
// FIXME: refactor FitSuiteObjects::getChiSquaredValue() (the main problem is duplication calculateChiSquared() for ChiSquaredModule and FitObject)
/* ************************************************************************* */
double FitSuiteObjects::getChiSquaredValue(int n_free_fit_parameters)
{
    double max_intensity = getSimulationMaxIntensity();
    double chi_sum(0);
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        IChiSquaredModule *chi = (*it)->getChiSquaredModule();

        chi->setNdegreeOfFreedom( (int)(m_fit_objects.size() * (*it)->getRealData()->getAllocatedSize() - n_free_fit_parameters) );
        // normalizing datasets to the maximum intensity over all fit objects defined
        OutputDataNormalizerScaleAndShift *data_normalizer =  dynamic_cast<OutputDataNormalizerScaleAndShift *>(chi->getOutputDataNormalizer());
        if( data_normalizer) data_normalizer->setMaximumIntensity( max_intensity );

        double weight = (*it)->getWeight()/m_total_weight;
        double chi_squared = (weight*weight) * (*it)->calculateChiSquared();
        chi_sum += chi_squared;
//        std::cout << " chi " << chi_squared << " chi_sum:" << chi_sum << std::endl;
    }
    return chi_sum;
}


double FitSuiteObjects::getResidualValue(int index)
{
    double residual_sum(0);
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        IChiSquaredModule *chi = (*it)->getChiSquaredModule();
        const OutputData<double> *data_real = (*it)->getRealData();
        const OutputData<double> *data_simu = (*it)->getSimulationData();
        double value_real = (*data_real)[index];
        double value_simu = (*data_simu)[index];
        double squared_difference = chi->getSquaredFunction()->calculateSquaredDifference(value_real, value_simu);
        double weight = (*it)->getWeight()/m_total_weight;
        double residual(0);
        (squared_difference > 0 ? residual = weight*std::sqrt(squared_difference) : 0.0);
        residual_sum += residual;
    }
    return residual_sum;
}



/* ************************************************************************* */
// calculate maximum intensity in simulated data over all fit objects defined
/* ************************************************************************* */
double FitSuiteObjects::getSimulationMaxIntensity()
{
    double max_intensity(0);
    for(FitObjects_t::iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it) {
        const OutputData<double > *data = (*it)->getExperiment()->getOutputData();
        OutputData<double >::const_iterator cit = std::max_element(data->begin(), data->end());
        max_intensity = std::max(max_intensity, *cit);
    }
    return max_intensity;
}


/* ************************************************************************* */
// add parameters from local pool to external pool
/* ************************************************************************* */
std::string FitSuiteObjects::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    (void)copy_number;
    // add own parameters
    // so far it is top object in our chain, and its without parameters, lets exclude its name from path
    //std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);
    std::string new_path = path;

    int ncopy(0);
    if(m_fit_objects.size()==1) ncopy=-1; // if we have only one object, lets get rid from copy number
    for(FitObjects_t::const_iterator it = m_fit_objects.begin(); it!= m_fit_objects.end(); ++it, ++ncopy) {
        (*it)->addParametersToExternalPool(new_path, external_pool, ncopy);
    }

    return new_path;
}


void FitSuiteObjects::init_parameters()
{

}

