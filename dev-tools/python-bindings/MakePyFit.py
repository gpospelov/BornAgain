# BornAgain Fit library
# settings for Python API generation by codegenerator.py

import os
import sys
import glob
import subprocess
import time
from pyplusplus import module_builder
from pyplusplus.module_builder import call_policies
from pyplusplus import messages
from pyplusplus import file_writers
from pygccxml.declarations.matchers import access_type_matcher_t
from pygccxml.declarations.matchers import virtuality_type_matcher_t
from pygccxml import declarations
from pygccxml import parser

import builder_utils


license = '''\
// BornAgain: simulate and fit scattering at grazing incidence
//! @brief Automatically generated boost::python code for PythonFitAPI
'''


temp_dir    ='output/PyFit'
install_dir = '../../Fit/PythonAPI'


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
    "AttLimits",
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
]


exclude_patterns = [
    # already contained in Core API:
    "vdouble1d_t",
    "vcomplex1d_t",
    "IObservable",
    "IObserver",
    "IParameterized" ]


# -----------------------------------------------------------------------------
# AdditionalRules
# -----------------------------------------------------------------------------
def ManualClassTunings(mb):
    cl = mb.class_("IMinimizer")
    cl.member_function("setChiSquaredFunction").exclude()
    cl.member_function("setGradientFunction").exclude()
    cl.member_function("getAlgorithmName").exclude() # temporarily due to compilation problems under MSVC
    cl.member_function("getMinimizerName").exclude() # temporarily due to compilation problems under MSVC
    for fun in cl.member_functions():
        if "getOptions" in fun.name:
            if "::MinimizerOptions const & ( ::IMinimizer::* )(  ) const" in fun.decl_string:
                fun.exclude()
            else:
                fun.call_policies = call_policies.return_internal_reference()

    #
    cl = mb.class_("FitSuite")
    #cl.member_functions().exclude()
    #for fun in cl.member_functions(allow_empty=True):
      #if "addFitParameter" in fun.name:
          #fun.include()
    cl.member_function("getMinimizer").include()
    cl.member_function( "getMinimizer" ).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
    cl.member_function("setMinimizer").include()
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

    cl = mb.class_("IObserver")
    cl.member_function("update").include()

    cl = mb.class_("FitSuiteParameters")
    for fun in cl.member_functions():
        if "__gnu_cxx::__normal_iterator" in fun.decl_string:
            fun.exclude()


# excluding specific member functions
def ManualExcludeMemberFunctions(mb):
    pass
