# generate python API wrappers for Fit library
# used by codegenerator.py

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
from pyplusplus import function_transformers as FT
from pygccxml import parser


import builder_utils


include_dirs = [
'../../Core/Samples/inc',
'../../Core/Algorithms/inc',
'../../Core/Tools/inc',
'../../Core/Geometry/inc',
'../../Fit/Factory/inc',
'../../Fit/PythonAPI/inc',
#'../../ThirdParty/eigen3',
]

include_classes = [
"AttLimits",
"ChiSquaredModule",
"FitSuite",
"FitSuiteParameters",
"IChiSquaredModule",
"IMinimizer",
"IOutputDataNormalizer",
"ISquaredFunction",
"MinimizerFactory",
"OutputDataNormalizer",
"OutputDataSimpleNormalizer",
"SquaredFunctionDefault",
"SquaredFunctionWhichOnlyWorks",
"SquaredFunctionWithGaussianError",
"SquaredFunctionWithSystematicError",
]


# -----------------------------------------------------------------------------
# AdditionalRules
# -----------------------------------------------------------------------------
def ManualClassTunings(mb):
    cl = mb.class_("IMinimizer")
    cl.member_function("setChiSquaredFunction").exclude()
    cl.member_function("setGradientFunction").exclude()
    #
    cl = mb.class_("FitSuite")
    cl.member_functions().exclude()
    for fun in cl.member_functions(allow_empty=True):
      if "addFitParameter" in fun.name:
          fun.include()
    cl.member_function("getMinimizer").include()
    cl.member_function("setMinimizer").include()
    cl.member_function("addSimulationAndRealData").include()
    cl.member_function("runFit").include()
    cl.member_function("printResults").include()
    cl.member_function("getNCalls").include()
    cl.member_function("initPrint").include()
    cl.member_function("getFitParameters").include()
    #
    cl = mb.class_("FitSuiteParameters")
    cl.member_functions().exclude()
    cl.member_function("getValues").include()
    for fun in cl.member_operators():
        if "operator[]" in fun.name:
            fun.exclude()
    #
    cl = mb.class_("MinimizerFactory")
    cl.member_function( "createMinimizer" ).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )


# excluding specific member functions
def ManualExcludeMemberFunctions(mb):
    pass


#------------------------------------------------------------------------------
# produces boost python code
#------------------------------------------------------------------------------
def MakePythonAPI(OutputTempDir):
    print "Generating PythonAPI for libBornAgainFit."
    # getting paths
    include_dirs.append( builder_utils.get_python_path() )
    include_dirs.append( builder_utils.get_gcc_path() )
    mygccxml = builder_utils.get_gccxml_path()

    #If the cache file cache_core.xml doesn't exist it gets created, otherwise it just gets loaded
    print "NOTE: If you update the source library code you need to manually delete the cache_fit.xml file, or run 'python codegenerator.py clean'"
    xml_cached_fc = parser.create_cached_source_fc( "PythonFitList.h", "cache_fit.xml" )
    mb = module_builder.module_builder_t( [xml_cached_fc], include_paths=include_dirs, gccxml_path=mygccxml, cflags="-m64 -DGCCXML_SKIP_THIS")

    # -----------------
    # general rules
    # -----------------

    builder_utils.IncludeClasses(mb, include_classes)

    builder_utils.DefineGeneralRules(mb)

    builder_utils.ExcludeConstructorsArgPtr(mb)

    builder_utils.ExcludeMemberFunctionsArgPtr(mb)

    builder_utils.ManageNewReturnPolicy(mb)

    # -----------------
    # manual tuning
    # -----------------

    ManualExcludeMemberFunctions(mb)

    ManualClassTunings(mb) 

    # -----------------
    # default policies for what remained unchainged
    # -----------------

    #builder_utils.IncludePureVirtualMethods(mb, include_classes)

    builder_utils.DefaultReturnPolicy(mb)

    # disabling some warnings
    messages.disable(
        messages.W1020  # Warnings 1020 - 1031 are all about why Py++ generates wrapper for class X
      , messages.W1021
      , messages.W1022
      , messages.W1023
      , messages.W1024
      , messages.W1025
      , messages.W1026
      , messages.W1027
      , messages.W1028
      , messages.W1029
      , messages.W1030
      , messages.W1031
      #, messages.W1035
      #, messages.W1040
      #, messages.W1038
      #, messages.W1041
      , messages.W1036 # pointer to Python immutable member
      #, messages.W1033 # unnamed variables
      #, messages.W1018 # expose unnamed classes
      #, messages.W1049 # returns reference to local variable
      #, messages.W1014 # unsupported '=' operator
       )

    # ---------------------------------------------------------
    # generating output
    # ---------------------------------------------------------
    mb.build_code_creator( module_name=builder_utils.ModuleName)
    mb.code_creator.license = builder_utils.license
    
    mb.code_creator.user_defined_directories.append( os.path.abspath('./') )
    mb.split_module(OutputTempDir)


#------------------------------------------------------------------------------
# main()
#------------------------------------------------------------------------------
if __name__ == '__main__':
    tempDir='output/PyFit'
    if not os.path.exists(tempDir): os.makedirs(tempDir)
    start_time = time.clock()
    MakePythonAPI(tempDir)
    print '\nPythonFitAPI source code was generated ( %f seconds ).' % (  ( time.clock() - start_time ) )
    print 'Run InstallPyFit.py to install generated code into BornAgain source tree'
    print 'Done'

