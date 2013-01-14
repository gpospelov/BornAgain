#include "ROOTMinimizerFunction.h"

//ROOTMinimizerFunction::ROOTMinimizerFunction()
//{
//}


///* *************************************************************************** */
//// evaluation of single data element residual
///* *************************************************************************** */
//double ROOTMinimizerElementFunction::DataElement(const double *pars, unsigned int i_selected_element, double *gradient) const
//{
//    bool parameters_changed = parametersHaveChanged(pars);
//    for(size_t i=0; i<m_ndims; ++i) {
//        std::cout << pars[i] << " ";
//    }
//    std::cout << "  parameters_changed:" << parameters_changed << " selected_element:" << i_selected_element << " index_prev:" << m_prev_element << std::endl;

//    int diff = i_selected_element-m_prev_element;
//    if( diff >1 &&  ( diff != -1.*(int)m_nelements) ) std::cout << "XXXXX 1.1 Warning! (i-prev>1) Non sequential access to elements!" << std::endl;
//    if( parameters_changed && i_selected_element!= 0 )std::cout << "XXXXX 1.2 Warning! Parameters changed and i!= 0" << std::endl;
//    if( parameters_changed && i_selected_element == m_prev_element )std::cout << "XXXXX 1.2 Warning! Parameters changed and i=prev_element" << std::endl;
//    m_prev_element = i_selected_element;

//    if(parameters_changed) {
//        m_fcn(pars);
//        for(size_t i_element=0; i_element<m_nelements; ++i_element) {
//            m_residuals[i_element] = m_element_fcn(pars, i_element, gradient);
//        }
//    }

//    if( gradient ) {
//        std::cout << " gradient " << std::endl;
//        if(i_selected_element == 0 || parameters_changed) {
//            std::cout << "g!=0 parameters_changed " << parameters_changed << std::endl;
//        }
//        for(size_t i_par=0; i_par<m_ndims; ++i_par) {
//            gradient[i_par] = m_gradients[i_par][i_selected_element];
//            std::cout << " gradient_result i_par:" << i_par << " " << gradient[i_par] << std::endl;
//        }
//    }

//    // ./root/hist/hist/src/TF1.cxx  - how root estimate derivative

//    m_ncalls_element++;
//    return m_residuals[i_selected_element];
//}



//class ROOTMinimizerElementFunction : public ROOT::Math::FitMethodFunction
//{
//public:
//    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t  Type_t;

//    ROOTMinimizerElementFunction(IMinimizer::function_chi2_t fcn, size_t ndims, IMinimizer::function_gradient_t element_fcn, size_t nelements)
//        : ROOT::Math::FitMethodFunction(ndims, nelements)
//        , m_fcn(fcn)
//        , m_element_fcn(element_fcn)
//        , m_ndims(ndims)
//        , m_nelements(nelements)
//        , m_ncalls(0)
//        , m_ncalls_element(0)
//        , m_prev_element(0)
//    {
//        m_parameter_values.resize(ndims, 0.0);
//        m_residuals.resize(nelements, 0.0);
//        m_gradients.resize(ndims);
//        for(size_t i_dim=0; i_dim<ndims; ++i_dim) {
//            m_gradients[i_dim].resize(nelements, 0.0);
//        }
//    }

//    virtual ~ROOTMinimizerElementFunction(){}

//    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }
//    ROOT::Math::IMultiGenFunction * Clone() const { return new ROOTMinimizerElementFunction(m_fcn, m_ndims, m_element_fcn, m_nelements); }

//    //! evaluation of chi2
//    double DoEval(const double * pars) const
//    {
//        double chi2 = 0.0;
//        for(size_t i_data=0; i_data<m_nelements; ++i_data) {
//            chi2 += DataElement(pars, i_data);
//        }
//        ++m_ncalls;
//        std::cout << " ROOTMinimizerElementFunction::DoEval() -> " << chi2 << std::endl;
//        return chi2;
//    }

//    //! evaluation of single data element residual
//    double DataElement(const double *pars, unsigned int i_selected_element, double *gradient = 0) const ;

//    virtual unsigned int NCalls() const { return m_ncalls; }
//    virtual unsigned int NCallsElement() const { return m_ncalls_element; }

//    bool isEqual(double a, double b) const
//    {
//        return std::abs(a-b) < 2.*Numeric::double_epsilon;
//    }

//    bool parametersHaveChanged(const double *pars) const
//    {
//        for(size_t i=0; i<m_ndims; ++i) {
//            if( !isEqual(pars[i], m_parameter_values[i])) {
//                std::copy(pars, pars+m_ndims, m_parameter_values.begin());
//                return true;
//            }
//        }
//        return false;
//    }


//private:

//    IMinimizer::function_chi2_t m_fcn;
//    IMinimizer::function_gradient_t m_element_fcn;
//    size_t m_ndims;
//    size_t m_nelements;
//    mutable std::vector<double > m_parameter_values;
//    mutable size_t m_ncalls;
//    mutable size_t m_ncalls_element;
//    mutable size_t m_prev_element;
//    mutable std::vector<double > m_residuals; // [m_nelements]
//    mutable std::vector<std::vector<double> > m_gradients; // [m_ndims][m_nelements]
//};



