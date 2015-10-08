# BornAgain Fit library
# settings for Python API generation by codegenerator.py

from pyplusplus.module_builder import call_policies
#from pyplusplus import messages
import utils_build

license = '''\
// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
'''

lib_name = 'libBornAgainFit'

temp_dir    = 'output/PyFit'
install_inc = '../../Fit/PythonAPI/inc'
install_src = '../../Fit/PythonAPI/src'

master_include = "PythonFitList.h"
cache_filename = "cache_fit.xml"
special_flags = ""

with_pure_virtual = False
with_Numpy = False
with_converter = False


include_dirs = [
    '../../Core/Samples/inc',
    '../../Core/Algorithms/inc',
    '../../Core/Tools/inc',
    '../../Core/Geometry/inc',
    '../../Fit/FitKernel/inc',
    '../../Fit/PythonAPI/inc',
]

include_classes = [
    "INamed",
    "IObservable",
    "IObserver",
    "IParameterized",
    "AttFitting",
    "ChiSquaredModule",
    "FitSuite",
    "FitObject",
    "FitParameter",
    "FitSuiteParameters",
    "FitSuiteObjects",
    "IChiSquaredModule",
    "IMinimizer",
    "IIntensityNormalizer",
    "IIntensityFunction",
    "IntensityFunctionLog",
    "IntensityFunctionSqrt",
    "ISquaredFunction",
    "IFitStrategy",
    "FitStrategyDefault",
    "FitStrategyAdjustParameters",
    "FitStrategyFixParameters",
    "FitStrategyReleaseParameters",
    "FitStrategyAdjustMinimizer",
    "MinimizerFactory",
    "MinimizerOptions",
    "IntensityNormalizer",
    "IntensityScaleAndShiftNormalizer",
    "SquaredFunctionDefault",
    "SquaredFunctionMeanSquaredError",
    "SquaredFunctionGaussianError",
    "SquaredFunctionSystematicError",
    "SquaredFunctionSimError",
    "IFitObserver",
]


exclude_patterns = [
    # already contained in Core API:
    "vdouble1d_t",
    "vcomplex1d_t",
    "IObservable",
    "IObserver",
    "IParameterized",
    "vector_string_t"]


# -----------------------------------------------------------------------------
# AdditionalRules
# -----------------------------------------------------------------------------
def ManualClassTunings(mb):

    # IMinimizer
    cl = mb.class_("IMinimizer")
    cl.member_function("setChiSquaredFunction").exclude()
    cl.member_function("setGradientFunction").exclude()
    # cl.member_function("getAlgorithmName").exclude() # removed due to compilation problems under MSVC
    #cl.member_function("getMinimizerName").exclude() # temporarily due to compilation problems under MSVC
    for fun in cl.member_functions():
        if "getOptions" in fun.name:
            if "::MinimizerOptions const & ( ::IMinimizer::* )(  ) const" in fun.decl_string:
                fun.exclude()
            else:
                fun.call_policies = call_policies.return_internal_reference()

    # adding hand made wrapper code to bypass a error with std::string conversion under Windows & MSVC2012
    # code = """
    # virtual ::std::string getAlgorithmName(  ) const  {
    #     if( bp::override func_getAlgorithmName = this->get_override( "getAlgorithmName" ) )
    #         return boost::python::call<std::string>(func_getAlgorithmName(  ));
    #     else{
    #         return this->IMinimizer::getAlgorithmName(  );
    #     }
    # }
    #
    # ::std::string default_getAlgorithmName(  ) const  {
    #     return IMinimizer::getAlgorithmName( );
    # }
    # """
    # cl.add_wrapper_code(code)
    utils_build.InjectGetStringCustomCode(cl, "getAlgorithmName")
    utils_build.InjectGetStringCustomCode(cl, "getMinimizerName")

    # code = """
    #         def(
    #             "getAlgorithmName"
    #             , (::std::string ( ::IMinimizer::*)(  ) const)(&::IMinimizer::getAlgorithmName)
    #             , (::std::string ( IMinimizer_wrapper::*)(  ) const)(&IMinimizer_wrapper::default_getAlgorithmName) )
    # """
    # cl.add_code(code)


    #
    cl = mb.class_("FitSuite")
    #cl.member_functions().exclude()
    #for fun in cl.member_functions(allow_empty=True):
      #if "addFitParameter" in fun.name:
          #fun.include()
    # cl.member_function("getMinimizer").include()

    # cl.member_function( "getMinimizer" ).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
    cl.member_function( "getMinimizer" ).call_policies= call_policies.return_internal_reference() # which one is correct ?
    cl.member_function("getRealData").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    cl.member_function("getSimulationData").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    cl.member_function("getChiSquaredMap").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)

    cl.member_function( "getFitObjects" ).call_policies = call_policies.return_internal_reference()
    cl.member_function( "getFitParameters" ).call_policies = call_policies.return_internal_reference()
    cl.member_function( "getFitStrategies" ).call_policies = call_policies.return_internal_reference()


    # cl.member_function("setMinimizer").include()
    #cl.member_function("addSimulationAndRealData").include()
    #cl.member_function("runFit").include()
    #cl.member_function("printResults").include()
    #cl.member_function("getNCalls").include()
    #cl.member_function("initPrint").include()
    #cl.member_function("getFitParameters").include()
    #
    #cl = mb.class_("FitSuiteParameters")
    #cl.member_functions().exclude()
    #cl.member_function("getValues").include()
    #for fun in cl.member_operators():
        #if "operator[]" in fun.name:
            #fun.exclude()
    #
    cl = mb.class_("MinimizerFactory")
    #cl.member_function( "createMinimizer" ).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
    for fun in cl.member_functions():
        if "createMinimizer" in fun.name:
            fun.call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )

    cl = mb.class_("FitStrategyAdjustMinimizer")
    cl.member_function( "getMinimizer" ).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
    cl.member_function( "setMinimizer" ).include()

    cl = mb.class_("MinimizerOptions") # alternatively transformation can be used
    for fun in cl.member_functions():
        if "getValue" in fun.name:
            fun.exclude()

    # cl = mb.class_("IObserver")
    # cl.member_function("update").include()
    cl = mb.class_("IFitObserver")
    cl.member_function("update").include()

    cl = mb.class_("FitSuiteParameters")
    for fun in cl.member_functions():
        if "__gnu_cxx::__normal_iterator" in fun.decl_string:
            fun.exclude()

    cl = mb.class_("FitSuiteObjects")
    cl.member_function("getChiSquaredMap").call_policies = \
        call_policies.return_value_policy(call_policies.manage_new_object)

    cl = mb.class_("ChiSquaredModule")
    cl.member_function("processFitElements").exclude()
    cl = mb.class_("IChiSquaredModule")
    cl.member_function("processFitElements").exclude()

    cl = mb.class_("FitObject")
    cl.member_function("prepareFitElements").exclude()
    cl.member_function("getChiSquaredMap").exclude()


# excluding specific member functions
def ManualExcludeMemberFunctions(mb):
    pass
