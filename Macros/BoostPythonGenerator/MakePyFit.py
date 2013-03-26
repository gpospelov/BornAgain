# generate python API wrappers for Fit library, see codegenerator.py

import os
import sys
import glob
from pyplusplus import module_builder
from pyplusplus.module_builder import call_policies
from pyplusplus import messages
from pyplusplus import file_writers
from pygccxml.declarations.matchers import access_type_matcher_t
from pygccxml.declarations.matchers import virtuality_type_matcher_t
from pygccxml import declarations
from pyplusplus import function_transformers as FT

ModuleName = 'PythonInterface'

# list of files to analyse and corresponding functions with rules for analysis
myFiles=[
  'AttLimits.h',
  'IChiSquaredModule.h',
  'IMinimizer.h',
  #'IResolutionFunction2D.h',
  #'ISquaredFunction.h',
  'ChiSquaredModule.h',
  'FitSuite.h',
  'MinimizerFactory.h',
  'OutputData.h',
  'PythonPlusplusFitHelper.h',
  #'OutputDataIterator.h',
  #'ResolutionFunction2DSimple.h'
]


# list of include directories
myIncludes = [
    '../../Core/Samples/inc',
    '../../Core/Algorithms/inc',
    '../../Core/Tools/inc',
    '../../Core/Geometry/inc',
    '../../Core/Fitting/inc',
    '../../Fit/Factory/inc',
    '../../Fit/PythonAPI/inc'
]


# -------------------------------------------------------------------
# AdditionalRules
# -------------------------------------------------------------------
def AdditionalRules(mb):

  if "IChiSquaredModule.h" in myFiles:
    cl = mb.class_("IChiSquaredModule")
    #cl.member_functions().exclude()

  if "IMinimizer.h" in myFiles:
    cl = mb.class_("IMinimizer")
    cl.member_function("setChiSquaredFunction").exclude()
    cl.member_function("setGradientFunction").exclude()

  if "ChiSquaredModule.h" in myFiles:
    cl = mb.class_("ChiSquaredModule")
    #cl.member_functions().exclude()

  if "FitSuite.h" in myFiles:
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

  if "MinimizerFactory.h" in myFiles:
    cl = mb.class_("MinimizerFactory")
    #cl.member_function( "createMinimizer" ).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )
    cl.member_function( "createMinimizer" ).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )

  if "OutputData.h" in myFiles:
    cl = mb.class_("OutputData<double>")
    cl.member_functions().exclude()
    cl.member_function("totalSum").include()

  # --- PythonPlusplusHelper.h ----------------------------------------
  if "PythonPlusplusFitHelper.h" in myFiles:
    cl = mb.class_( "PythonPlusplusFitHelper" )
    cl.exclude() # given class is only to teach pyplusplus to templates, but we do not need class itself to be visible in python, excluding it...



def MakePythonAPI(OutputTempDir):
  from pyplusplus.file_writers.balanced_files import balanced_files_t
  balanced_files_t.HEADER_EXT='.h'
  balanced_files_t.SOURCE_EXT='.cpp'
  from pyplusplus.file_writers.multiple_files import multiple_files_t
  multiple_files_t.HEADER_EXT='.pypp.h'
  multiple_files_t.SOURCE_EXT='.pypp.cpp'

  myIncludes.append('/opt/local/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7')
  myIncludes.append('/opt/local/include/')
  mb = module_builder.module_builder_t(files=myFiles, include_paths=myIncludes, gccxml_path='/opt/local/bin', cflags="-m64")
  #mb = module_builder.module_builder_t(files=myFiles, include_paths=myIncludes, gccxml_path='/opt/local/bin')

  # ---------------------------------------------------------
  # common properties
  # ---------------------------------------------------------
  mb.always_expose_using_scope = True

  # Generated code containing errors will not compile on
  mem_funs = mb.calldefs ()
  mem_funs.create_with_signature = True

  # Exclude protected and private that are not pure virtual (we still have to expose pure virtual functions to have them overriden in the wrapper)
  query = declarations.access_type_matcher_t( 'private' ) & ~declarations.virtuality_type_matcher_t( declarations.VIRTUALITY_TYPES.PURE_VIRTUAL )
  mb.global_ns.calldefs( query, allow_empty=True ).exclude()
  query = declarations.access_type_matcher_t( 'protected' ) & ~declarations.virtuality_type_matcher_t( declarations.VIRTUALITY_TYPES.PURE_VIRTUAL )
  mb.global_ns.calldefs( query, allow_empty=True ).exclude()

  # excluding generation of methods for implicit conversion
  mb.constructors().allow_implicit_conversion = False

  # return policy for singletons, clone and create methods
  classes = mb.classes();
  for cl in classes:
    cl.member_functions('instance', allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
    cl.member_functions('clone', allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )
    cl.member_functions( lambda x: x.name.startswith('create'), allow_empty=True ).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )

  # excluding constructors which have pointers in argument list
  for cl in classes:
    for ctor in cl.constructors(allow_empty=True):
      for arg in ctor.arguments:
        if declarations.type_traits.is_pointer(arg.type):
          ctor.exclude()

  # excluding member functions if they have pointers in argument list
  for cl in classes:
    for fun in cl.member_functions(allow_empty=True):
      has_pointers = False
      for arg in fun.arguments:
        if declarations.type_traits.is_pointer(arg.type):
          has_pointers = True
      if has_pointers:
          fun.exclude();


  # ---------------------------------------------------------
  # calling class individual parsing properties
  # ---------------------------------------------------------
  AdditionalRules(mb)

  # set the default return policies (for references/pointers) on classes if it wasn't already been done for
  mem_funs = mb.calldefs()
  for mem_fun in mem_funs:
    if mem_fun.call_policies:
      continue
    if not mem_fun.call_policies and (declarations.is_reference(mem_fun.return_type) or declarations.is_pointer(mem_fun.return_type) ):
      mem_fun.call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )

  # exluding classes which are dublicated in libBornAgainCore
  DublicatesToExclude=[ 
    "std::vector<unsigned long, std::allocator<unsigned long> >", 
    "std::vector<double, std::allocator<double> >",
    "std::vector<int, std::allocator<int> >",
    "std::vector<std::vector<double, std::allocator<double> >",
    "vdouble2d_t",
    "vdouble1d_t",
  ]

  for cl in mb.classes():
    for name in DublicatesToExclude:
      if name in cl.name or name in cl.alias:
        cl.exclude()


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
       )

  # ---------------------------------------------------------
  # generating output
  # ---------------------------------------------------------
  mb.build_code_creator( module_name=ModuleName)
  mb.code_creator.user_defined_directories.append( os.path.abspath('./') )
  mb.split_module( OutputTempDir)


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  PyFitTempDir='output/PyFit'
  if not os.path.exists(PyFitTempDir): os.makedirs(PyFitTempDir)
  MakePythonAPI(PyFitTempDir)

