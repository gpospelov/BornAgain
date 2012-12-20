#include "ROOTMinimizerFunction.h"

//ROOTMinimizerFunction::ROOTMinimizerFunction()
//{
//}


/* *************************************************************************** */
// evaluation of single data element residual
/* *************************************************************************** */
double ROOTMinimizerElementFunction::DataElement(const double *pars, unsigned int i_selected_element, double *gradient) const
{
    bool parameters_changed = parametersHaveChanged(pars);
    for(size_t i=0; i<m_ndims; ++i) {
        std::cout << pars[i] << " ";
    }
    std::cout << "  parameters_changed:" << parameters_changed << " selected_element:" << i_selected_element << " index_prev:" << m_prev_element << std::endl;

    int diff = i_selected_element-m_prev_element;
    if( diff >1 &&  ( diff != -1.*(int)m_nelements) ) std::cout << "XXXXX 1.1 Warning! (i-prev>1) Non sequential access to elements!" << std::endl;
    if( parameters_changed && i_selected_element!= 0 )std::cout << "XXXXX 1.2 Warning! Parameters changed and i!= 0" << std::endl;
    if( parameters_changed && i_selected_element == m_prev_element )std::cout << "XXXXX 1.2 Warning! Parameters changed and i=prev_element" << std::endl;
    m_prev_element = i_selected_element;

    if(parameters_changed) {
        m_fcn(pars);
        for(size_t i_element=0; i_element<m_nelements; ++i_element) {
            m_residuals[i_element] = m_element_fcn(pars, i_element, gradient);
        }
    }

    if( gradient ) {
        std::cout << " gradient " << std::endl;
        if(i_selected_element == 0 || parameters_changed) {
            std::cout << "g!=0 parameters_changed " << parameters_changed << std::endl;
            const double kEps = 1.0E-4;
            for(size_t i_par=0; i_par<m_ndims; ++i_par ) {
                std::vector<double > pars_deriv; // values of parameters for derivative calculation
                pars_deriv.resize(m_ndims);
                std::copy(pars, pars+m_ndims, pars_deriv.begin());
                pars_deriv[i_par] += kEps;
                m_fcn(&pars_deriv.front());
                for(size_t j=0; j<pars_deriv.size(); ++j) {
                    std::cout << "i_par:" << i_par << " j:" << j << " " << pars[j] << " " << pars_deriv[j] << std::endl;
                }
                std::vector<double> m_residuals2;
                m_residuals2.resize(m_nelements);
                for(size_t i_element=0; i_element<m_nelements; ++i_element) {
                    m_residuals2[i_element] = m_element_fcn(&pars_deriv.front(), i_element, gradient);
                }

                for(size_t i_element=0; i_element <m_nelements; ++i_element) {
                    m_gradients[i_par][i_element] = (m_residuals2[i_element] - m_residuals[i_element])/kEps;
                }
            }
        }
        for(size_t i_par=0; i_par<m_ndims; ++i_par) {
            gradient[i_par] = m_gradients[i_par][i_selected_element];
            std::cout << " gradient_result i_par:" << i_par << " " << gradient[i_par] << std::endl;
        }
    }

    // ./root/hist/hist/src/TF1.cxx  - how root estimate derivative

    m_ncalls_element++;
    return m_residuals[i_selected_element];
}




