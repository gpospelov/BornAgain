#include "FitSuiteFunctions.h"
#include "FitSuite.h"
#include <iomanip>

/* ************************************************************************* */
// evaluate chi squared value
/* ************************************************************************* */
double FitSuiteChiSquaredFunction::evaluate(const double *pars)
{
    assert(m_fit_suite != NULL);

    m_fit_suite->getFitParameters()->setValues(pars);
    m_fit_suite->getFitObjects()->runSimulation();
    double chi_squared = m_fit_suite->getFitObjects()->getChiSquaredValue();
    m_fit_suite->notifyObservers();
    m_ncall++;
    return chi_squared;
}


/* ************************************************************************* */
// evaluate residual and derivative for given data element
// (calculations are done for all dataset when index==0, when index!=0 already
// calculated data just returned
/* ************************************************************************* */
double FitSuiteGradientFunction::evaluate(const double *pars, unsigned int index, double *gradients)
{
    assert(m_fit_suite != NULL);

    bool parameters_changed(true);
    if(m_ncalls_total != 0) parameters_changed = m_fit_suite->getFitParameters()->valuesAreDifferrent(pars, 2);

    verify_arrays();
    verify_minimizer_logic(parameters_changed, (int)index);

    if(parameters_changed) calculate_residuals(pars);

    if(gradients) {
        if(index == 0 || parameters_changed ) {
            calculate_gradients(pars);
            m_ncalls_gradient++;
        }
        for(size_t i_par=0; i_par<m_npars; ++i_par) {
            gradients[i_par] = m_gradients[i_par][index];
        }
    }

    m_ncalls_total++;
    if(index == 0 && !gradients) {
        m_fit_suite->notifyObservers();
        m_ncall++;
    }
    return m_residuals[index];
}


void FitSuiteGradientFunction::verify_arrays()
{
    if( m_npars != m_fit_suite->getFitParameters()->size() || m_ndatasize != m_fit_suite->getFitObjects()->getSizeOfDataSet() ) {
        //std::cout << "FitSuiteGradientFunction::verify_arrays() -> Info. " << std::endl;
        m_npars = m_fit_suite->getFitParameters()->size();
        m_ndatasize = m_fit_suite->getFitObjects()->getSizeOfDataSet();
        m_residuals.clear();
        m_residuals.resize(m_ndatasize, 0.0);
        m_gradients.clear();
        m_gradients.resize(m_npars);
        for(size_t i_par=0; i_par<m_npars; ++i_par) {
            m_gradients[i_par].resize(m_ndatasize, 0.0);
        }
    }
}

void FitSuiteGradientFunction::verify_minimizer_logic(bool parameters_have_changed, int current_index)
{
    int index_difference = current_index - m_prev_index;
    if(index_difference != 1 && (current_index!=0 && int(m_prev_index)!= int(m_ndatasize-1) ) ) {
        std::cout << "FitSuiteGradientFunction::verify_minimizer_logic() -> Warning! Non sequential access to elements.";
        std::cout << " current_index:" << current_index << " prev_index:" << m_prev_index << std::endl;
    }
    if(parameters_have_changed && current_index != 0) {
        std::cout << "FitSuiteGradientFunction::verify_minimizer_logic() -> Warning! Parameters have changed while current_index!=0" << std::endl;
        std::cout << " current_index:" << current_index << " prev_index:" << m_prev_index << std::endl;
    }
    if(parameters_have_changed && current_index == m_prev_index) {
        std::cout << "FitSuiteGradientFunction::verify_minimizer_logic() -> Warning! Parameters have changed while index remained the same"  << std::endl;
        std::cout << " current_index:" << current_index << " prev_index:" << m_prev_index << std::endl;
    }
    m_prev_index = current_index;
}

void FitSuiteGradientFunction::calculate_residuals(const double *pars)
{
    //std::cout << " FitSuiteGradientFunction::calculate_residuals() -> Info. " << std::endl;
    runSimulation(pars);
    for(size_t i_data=0; i_data<m_ndatasize; ++i_data) {
        m_residuals[i_data] = m_fit_suite->getFitObjects()->getResidualValue(i_data);
        //std::cout << i_data << " " << m_residuals[i_data] << std::endl;
    }

}

void FitSuiteGradientFunction::calculate_gradients(const double *pars)
{
    std::cout << " FitSuiteGradientFunction::calculate_gradients() -> Info. " << std::endl;
    // FIXME get kEps from outside fit_suite->getMinimizer()->getPrecision();
    const double kEps = 1.0E-9; // Good for Fumili
    //const double kEps = 1.0E-5;
    for(size_t i_par=0; i_par<m_npars; ++i_par ) {
        std::vector<double > pars_deriv; // values of parameters for derivative calculation
        pars_deriv.resize(m_npars);
        std::copy(pars, pars+m_npars, pars_deriv.begin());
        pars_deriv[i_par] += kEps;

        //std::cout << "   " << (pars[i_par]- pars_deriv[i_par]) << std::endl;
        runSimulation(&pars_deriv.front());

        std::vector<double> residuals2;
        residuals2.resize(m_ndatasize);
        for(size_t i_data=0; i_data<m_ndatasize; ++i_data) {
            residuals2[i_data] = m_fit_suite->getFitObjects()->getResidualValue(i_data);
        }

        for(size_t i_data=0; i_data <m_ndatasize; ++i_data) {
            m_gradients[i_par][i_data] = (residuals2[i_data] - m_residuals[i_data])/kEps;
            //std::cout << "AAA " << m_gradients[i_par][i_data] << " " <<  residuals2[i_data] << " " <<  m_residuals[i_data] << " " << (residuals2[i_data]-m_residuals[i_data]) << std::endl;
        }
    }
    // returning back old parameters
    m_fit_suite->getFitParameters()->setValues(pars);
    runSimulation(pars);

}


void FitSuiteGradientFunction::runSimulation(const double *pars){
    assert(m_fit_suite);
    m_fit_suite->getFitParameters()->setValues(pars);
    m_fit_suite->getFitObjects()->runSimulation();
    //m_fit_suite->getFitObjects()->getChiSquaredValue();
}



