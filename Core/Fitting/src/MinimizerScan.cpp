#include "MinimizerScan.h"
#include <algorithm>


/* ************************************************************************* */
//
/* ************************************************************************* */
void MinimizerScan::minimize()
{
    construct_parameter_map();

    // scanning values of fit parameters
    for(OutputData<double>::iterator it = m_parameter_map->begin(); it!=m_parameter_map->end(); ++it) {
        for(size_t i_axis=0; i_axis<m_parameter_map->getNdimensions(); ++i_axis) {
            size_t xbin = m_parameter_map->toCoordinate(it.getIndex(), i_axis);
            double value = (*m_parameter_map->getAxis(i_axis))[xbin];
            std::string parname = m_parameter_map->getAxis(i_axis)->getName();
            m_fit_parameters.getParameter(parname)->setValue(value);
        }
        std::vector<double> current_values=m_fit_parameters.getValues();
        (*it) = m_fcn(&current_values[0]);
    }

    set_parvalues_to_minimum();
}


/* ************************************************************************* */
// Construct N dimensional space over all fit parameters with lower and upper limits
// defined.
/* ************************************************************************* */
void MinimizerScan::construct_parameter_map()
{
    delete m_parameter_map;
    m_parameter_map = new OutputData<double>;
    for(size_t i_par=0; i_par < m_fit_parameters.size(); i_par++ ) {
        const FitParameter *par = m_fit_parameters[i_par];
        if( par->hasLowerLimit() && par->hasUpperLimit() ) {
            AxisDouble axis(par->getName(), m_nbins, par->getLowerLimit(), par->getUpperLimit());
            m_parameter_map->addAxis(axis);
        }
    }
    m_parameter_map->setAllTo(0.0);
}


void MinimizerScan::set_parvalues_to_minimum()
{
    assert(m_parameter_map);
    OutputData<double>::iterator it = std::min_element(m_parameter_map->begin(), m_parameter_map->end());
    for(size_t i_axis=0; i_axis<m_parameter_map->getNdimensions(); ++i_axis) {
        size_t xbin = m_parameter_map->toCoordinate(it.getIndex(), i_axis);
        double value = (*m_parameter_map->getAxis(i_axis))[xbin];
        std::string parname = m_parameter_map->getAxis(i_axis)->getName();
        m_fit_parameters.getParameter(parname)->setValue(value);
    }

}


double MinimizerScan::getMinValue() const
{
    assert(m_parameter_map);
    return *std::min_element(m_parameter_map->begin(), m_parameter_map->end());
}


void MinimizerScan::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)
{
    (void) fun_gradient;
    (void) nparameters;
    (void) ndatasize;
}


double MinimizerScan::getValueOfVariableAtMinimum(size_t index) const
{
    return m_fit_parameters[index]->getValue();
}


void MinimizerScan::printResults() const
{
    std::cout << "MinimizerScan::printResults() -> Info" << std::endl;
}


void MinimizerScan::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)
{
    (void)nparameters;
    m_fcn = fun_chi2;
}


void MinimizerScan::setParameters(const FitSuiteParameters &parameters)
{
    m_fit_parameters.clear();
    for(size_t i_par = 0; i_par<parameters.size(); ++i_par) {
        m_fit_parameters.push_back(new FitParameter( *parameters[i_par] ) );
    }
}
