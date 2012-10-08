# c++ wrapper generator for accessing libScattCore from python
#
# Usage: 'python codegenerator.py make'  - to generate python-boost C++ wrappers
# Usage: 'python codegenerator.py install'  - to copy files into GISASFW/Core/PythonAPI directory
#
# requires boost, python27, py27-pyplusplus-devel, py-pygccxml-devel, gccxml-devel
#

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


ModuleName = 'PythonInterface'
nOutputFiles = 3 # generated code for classes will be splitted in this number of files
OutputTempDir='output'
InstallDir = '../../Core/PythonAPI'

# list of files to analyse and corresponding functions with rules for analysis
myFiles=[
  'BasicVector3D.h',
  'Experiment.h',
  'FormFactorCrystal.h',
  'FormFactorCylinder.h',
  'FormFactorFullSphere.h',
  'FormFactorGauss.h',
  'FormFactorLorentz.h',
  'FormFactorPrism3.h',
  'FormFactorPyramid.h',
  'GISASExperiment.h',
  'HomogeneousMaterial.h',
  'IClusteredParticles.h',
  'ICompositeSample.h',
  'IFormFactor.h',
  'IInterferenceFunction.h',
  'InterferenceFunctionNone.h',
  'InterferenceFunction1DParaCrystal.h',
  'IMaterial.h',
  'ISample.h',
  'ISingleton.h',
  'Lattice.h',
  'LatticeBasis.h',
  'Layer.h',
  'LayerDecorator.h',
  'LayerRoughness.h',
  'MaterialManager.h',
  'MesoCrystal.h',
  'MultiLayer.h',
  'Particle.h',
  'Crystal.h',
  'ParticleDecoration.h',
  'OpticalFresnel.h',
  'ParameterPool.h',
  'ParticleInfo.h',
  'DiffuseParticleInfo.h',
  'PythonOutputData.h',
  'PythonPlusplusHelper.h',
  'Transform3D.h',
  'Units.h',
  'Types.h',
]

# list of include directories
myIncludes = ['../../Core/Samples/inc','../../Core/FormFactors/inc','../../Core/Algorithms/inc','../../Core/Tools/inc','../../Core/PythonAPI/inc','../../Core/Geometry/inc']


#-------------------------------------------------------------
#
# additional class-specific rules for parsing
#
#-------------------------------------------------------------

# -------------------------------------------------------------------
# BasicVector3D.h
# -------------------------------------------------------------------
def RulesBasicVector3D(mb):
  # we exclude everyting related to complex BasicVector3D<complex_t>
  mb.class_("BasicVector3D<std::complex<double> >").exclude()
  mb.free_operators( lambda decl: 'Geometry::BasicVector3D<std::complex<double> >' in decl.decl_string ).exclude()
  mb.free_functions( lambda decl: 'Geometry::BasicVector3D<std::complex<double> >' in decl.decl_string ).exclude()
  #cl = mb.class_( "BasicVector3D<double>" )
  #for fun in cl.member_functions(): # setting policy for functions returning internal reference
    #if declarations.type_traits.is_reference(fun.return_type):
      #fun.call_policies = call_policies.return_internal_reference( )
  # excluding transform member_function to get rid from warning, anyway we are not using it in python
  # (otherwise pyplusplus keeps complaining about unexposed Trasform3D class, dont know why)
  #cl.member_function("transform").exclude()


# -------------------------------------------------------------------
# Experiment.h
# -------------------------------------------------------------------
def RulesExperiment(mb):
  cl = mb.class_( "Experiment" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()
  cl.member_function("runSimulation").include()
  cl.member_function("normalize").include()
  cl.member_function("setSample").include()
  cl.member_function("setBeamParameters").include()
  cl.member_function("setBeamIntensity").include()

# -------------------------------------------------------------------
# FormFactorCylinder.h
# -------------------------------------------------------------------
def RulesFormFactorCylinder(mb):
  cl = mb.class_( "FormFactorCylinder" )
  #cl.constructors().exclude() # excluding all constructors
  #cl.constructors( arg_types=[ "double", "double" ] ).include() # including constructor with 2 double parameters
  #cl.member_functions().exclude() # excluding all member functions

# -------------------------------------------------------------------
# FormFactorPyramid.h
# -------------------------------------------------------------------
def RulesFormFactorPyramid(mb):
  cl = mb.class_( "FormFactorPyramid" )
  #cl.constructors().exclude() # excluding all constructors
  #cl.constructors( arg_types=[ "double", "double", "double" ] ).include() # including constructor with 3 double parameters
  #cl.member_functions().exclude() # excluding all member functions

# -------------------------------------------------------------------
# FormFactorFullSphere.h
# -------------------------------------------------------------------
def RulesFormFactorFullSphere(mb):
  cl = mb.class_( "FormFactorFullSphere" )
  #cl.constructors().exclude() # excluding all constructors
  #cl.constructors( arg_types=[ "double" ] ).include() # including constructor with 3 double parametes
  #cl.member_functions().exclude() # excluding all member functions

  
# -------------------------------------------------------------------
# GISASExperiment.h
# -------------------------------------------------------------------
def RulesGISASExperiment(mb):
  cl = mb.class_( "GISASExperiment" )
  cl.member_function( "setDetectorResolutionFunction" ).exclude()

# -------------------------------------------------------------------
# HomogeneousMaterial.h
# -------------------------------------------------------------------
#def RulesHomogeneousMaterial(mb):

# -------------------------------------------------------------------
# IClusteredParticles.h
# -------------------------------------------------------------------
def RulesIClusteredParticles(mb):
  cl = mb.class_( "IClusteredParticles" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  #cl.member_functions().exclude()
  #cl.member_function("createTotalFormFactor").call_policies = call_policies.return_value_policy(call_policies.manage_new_object )


# -------------------------------------------------------------------
# ICompositeSample.h
# -------------------------------------------------------------------
def RulesICompositeSample(mb):
  cl = mb.class_( "ICompositeSample" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()


# -------------------------------------------------------------------
# IFormFactor.h
# -------------------------------------------------------------------
def RulesIFormFactor(mb):
  cl = mb.class_( "IFormFactor" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  #cl.member_functions( ).exclude()
  #cl.member_function( "clone" ).include() # including one virtual function back to have wrappers properly generated
  #cl.member_functions("createTotalFormFactor").exclude()
  
  cl = mb.class_( "IFormFactorBorn" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  #cl.member_functions( ).exclude()
  #cl.member_function( "clone" ).include() # including one virtual function back to have wrappers properly generated

  cl = mb.class_( "IFormFactorDecorator" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  #cl.member_functions( ).exclude()
  #cl.member_function( "clone" ).include() # including one virtual function back to have wrappers properly generated

# -------------------------------------------------------------------
# IInterferenceFunction.h
# -------------------------------------------------------------------
def RulesIInterferenceFunction(mb):
  cl = mb.class_( "IInterferenceFunction" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  #cl.member_functions().exclude()
  #cl.member_function( "clone" ).include() # including one virtual function back to have wrappers properly generated

# -------------------------------------------------------------------
# InterferenceFunctionNone.h
# -------------------------------------------------------------------
def RulesInterferenceFunctionNone(mb):
  cl = mb.class_( "InterferenceFunctionNone" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  #cl.member_functions().exclude()
  #cl.member_function( "clone" ).include() # including one virtual function back to have wrappers properly generated

# -------------------------------------------------------------------
# InterferenceFunction1DParaCrystal.h
# -------------------------------------------------------------------
def RulesInterferenceFunction1DParaCrystal(mb):
  cl = mb.class_( "InterferenceFunction1DParaCrystal" )
  #cl.member_functions().exclude()
  #cl.member_function( "clone" ).include() # including one virtual function back to have wrappers properly generated


# -------------------------------------------------------------------
# IMaterial.h
# -------------------------------------------------------------------
#def RulesIMaterial(mb):


# -------------------------------------------------------------------
# ISingleton.h
# -------------------------------------------------------------------
#def RulesISingleton(mb):


# -------------------------------------------------------------------
# ISample.h
# -------------------------------------------------------------------
def RulesISample(mb):
  cl = mb.class_( "ISample" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()
  cl.member_function( "clone" ).include()
  cl.member_function("walk_and_print").include()
  cl.member_function("createParameterTree").include()


# -------------------------------------------------------------------
# Lattice.h
# -------------------------------------------------------------------
def RulesLattice(mb):
  cl = mb.class_( "Lattice" )
  cl.member_functions().exclude()
  cl.member_function("getBasisVectorA").include()
  cl.member_function("getBasisVectorB").include()
  cl.member_function("getBasisVectorC").include()
  cl.member_function("createTrigonalLattice").include()
  cl.member_function("createTrigonalLattice").call_policies = call_policies.return_value_policy(call_policies.return_by_value )


  
# -------------------------------------------------------------------
# LatticeBasis.h
# -------------------------------------------------------------------
def RulesLatticeBasis(mb):
  cl = mb.class_( "LatticeBasis" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()
  cl.member_function("addParticle").include()


# -------------------------------------------------------------------
# Layer.h
# -------------------------------------------------------------------
def RulesLayer(mb):
  cl = mb.class_( "Layer" )
  cl.member_function( "createDWBASimulation" ).exclude()
  # we need to include back setMaterial methods since they have pointers in argument list (and our default policy is to exclude them)
  for fun in cl.member_functions(): # excluding constructors which have pointers
    if fun.name == "setMaterial":
      fun.include()
      print fun
  # why following method doesn't work?
  #cl.member_functions(lambda decl: 'setMaterial' in decl.decl_string, allow_empty=True).include()
  #cl.member_functions().exclude()
  #cl.member_functions( "setMaterial" ).include()
  #cl.member_functions( "setThickness" ).include()
  #cl.member_functions( "getThickness" ).include()


# -------------------------------------------------------------------
# LayerDecorator.h
# -------------------------------------------------------------------
def RulesLayerDecorator(mb):
  cl = mb.class_( "LayerDecorator" )
  cl.member_function( "createDiffuseDWBASimulation").exclude()
  cl.member_function( "createDWBASimulation").exclude()
  cl.member_function( "createStrategy").exclude()
  #cl.constructors( ).exclude() # excluding all constructors
  #cl.member_functions( ).exclude() # excluding all member functions
  #cl.member_function( "clone" ).include()
  #cl.constructors( lambda x: len(x.arguments)==2).include() # including constructor with two parameters


# -------------------------------------------------------------------
# LayerRoughness.h
# -------------------------------------------------------------------
def RulesLayerRoughness(mb):
  cl = mb.class_( "LayerRoughness" )
  cl.member_function( "getSpectralFun" ).exclude()
  cl.member_function( "getCorrFun" ).exclude()


# -------------------------------------------------------------------
# MaterialManager.h
# -------------------------------------------------------------------
def RulesMaterialManager(mb):
  cl = mb.class_( "MaterialManager" )
  cl.constructors().exclude()
  #cl.member_function( "getMaterial" ).call_policies = call_policies.return_internal_reference( )
  #cl.member_function( "addHomogeneousMaterial" ).call_policies = call_policies.return_internal_reference( )
  #cl.disable_warnings( messages.W1051 ) # not sure


# -------------------------------------------------------------------
# MesoCrystal.h
# -------------------------------------------------------------------
def RulesMesoCrystal(mb):
  cl = mb.class_( "MesoCrystal" )
  cl.member_functions( ).exclude() # excluding all member functions, leaving only constructors
  #for fun in cl.constructors(): # excluding constructors which have pointers
    #for arg in fun.arguments:
      #if declarations.type_traits.is_pointer(arg.type):
        #fun.exclude()

  
# -------------------------------------------------------------------
# MultiLayer.h
# -------------------------------------------------------------------
def RulesMultiLayer(mb):
  cl = mb.class_( "MultiLayer" )
  cl.member_functions( ).exclude()
  cl.member_function( "addLayer" ).include()
  cl.member_function( "addLayer" ).include()
  cl.member_function( "addLayerWithTopRoughness" ).include()


# -------------------------------------------------------------------
# Particle.h
# -------------------------------------------------------------------
def RulesParticle(mb):
  cl = mb.class_( "Particle" )
  cl.member_function( "createDiffuseParticleInfo" ).exclude()
  cl.member_function( "createDistributedParticles" ).exclude()

  #cl.member_functions( ).exclude() # excluding all member functions, leaving only constructors
  #for fun in cl.constructors(): # excluding constructors which have pointers
    #for arg in fun.arguments:
      #if declarations.type_traits.is_pointer(arg.type):
        #fun.exclude()


# -------------------------------------------------------------------
# Crystal.h
# -------------------------------------------------------------------
def RulesCrystal(mb):
  cl = mb.class_( "Crystal" )
  #cl.member_functions( ).exclude() # excluding all member functions, leaving only constructors
  #cl.member_function("createTotalFormFactor").call_policies = call_policies.return_value_policy(call_policies.manage_new_object )
  #cl.member_function("setAmbientRefractiveIndex").include()


# -------------------------------------------------------------------
# ParticleDecoration.h
# -------------------------------------------------------------------
def RulesParticleDecoration(mb):
  cl = mb.class_( "ParticleDecoration" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_function("createStrategy").exclude()
  #cl.member_functions( ).exclude() # exclude all member functions
  # including following methods if they doesn't have pointers in argument list
  #methods = ['addNanoParticle', 'addInterferenceFunction', 'setTotalParticleSurfaceDensity']
  #for m in methods:
    #for fun in cl.member_functions(m): # including methods if they don't have pointers in argument list
      #has_pointers = False
      #for arg in fun.arguments:
        #if declarations.type_traits.is_pointer(arg.type):
          #has_pointers = True
      #if not has_pointers:
        #fun.include()

# -------------------------------------------------------------------
# OpticalFresnel.h
# -------------------------------------------------------------------
#def RulesOpticalFresnel(mb):

# -------------------------------------------------------------------
# Point3D.h
# -------------------------------------------------------------------
def RulesPoint3D(mb):
  cl = mb.class_( "Point3D<double>" )
  #for fun in cl.member_functions(): 
    #if declarations.type_traits.is_reference(fun.return_type):
      #fun.call_policies = call_policies.return_internal_reference( )


# -------------------------------------------------------------------
# ParameterPool.h
# -------------------------------------------------------------------
def RulesParameterPool(mb):
  cl = mb.class_( "ParameterPool" )
  #cl.member_function( "cloneWithPrefix" ).call_policies = call_policies.return_value_policy(call_policies.manage_new_object )

# -------------------------------------------------------------------
# PythonOutputData.h
# -------------------------------------------------------------------
def RulesPythonOutputData(mb):
  # these functions returns PyObject, the empty custom policy is the only way I know 
  mb.free_function('GetOutputData').call_policies = call_policies.custom_call_policies("")
  mb.free_function('GetOutputDataAxis').call_policies = call_policies.custom_call_policies("")
  #mb.free_function('ExportOutputData').exclude()
  #mb.free_function('GetOutputData').exclude()
  #mb.free_function('GetOutputData').call_policies = call_policies.return_value_policy(call_policies.return_opaque_pointer )
  #mb.free_function('GetOutputDataAxis').call_policies = call_policies.return_value_policy(call_policies.return_opaque_pointer )
  #mb.free_function('GetOutputData').call_policies = call_policies.default_call_policies()
  #mb.free_function('GetOutputDataAxis').call_policies = call_policies.default_call_policies()
  #mb.free_function('GetOutputData').call_policies = call_policies.custom_call_policies("bp::return_value_policy< bp::return_by_value >")
  #mb.free_function('GetOutputDataAxis').call_policies = call_policies.custom_call_policies("bp::return_value_policy< bp::return_by_value >" )


# -------------------------------------------------------------------
# PythonPlusplusHelper.h
# -------------------------------------------------------------------
def RulesPythonPlusplusHelper(mb):
  mb.class_('PythonPlusplusHelper').exclude() # given class is only to teach pyplusplus to templates, but we do not need class itself to be visible in python, excluding it...

# -------------------------------------------------------------------
# Transform3D.h
# -------------------------------------------------------------------
def RulesTransform3D(mb):
  # removing mentioning of Point3D from constructors and member_functions
  mb.class_( "Point3D<double>").exclude()
  TransformClasses={"Transform3D","Reflect3D","Translate3D", "Scale3D", "Rotate3D"}
  for clname in TransformClasses:
    cl = mb.class_(clname)
    cl.constructors(lambda decl: 'Point3D' in decl.decl_string, allow_empty=True ).exclude()
    cl.member_functions(lambda decl: 'Point3D' in decl.decl_string, allow_empty=True ).exclude()
    #for fun in cl.member_functions(allow_empty=True): # setting policy for functions returning internal reference
      #if declarations.type_traits.is_reference(fun.return_type):
        #fun.call_policies = call_policies.return_internal_reference( )


# -------------------------------------------------------------------
# Types.h
# -------------------------------------------------------------------
#def RulesTypes(mb):

        #typedef bp::class_< KVector< double > > KVector_less__double__greater__exposer_t;
        #KVector_less__double__greater__exposer_t KVector_less__double__greater__exposer = KVector_less__double__greater__exposer_t( "KVector_less__double__greater_", bp::init< >() );

# -------------------------------------------------------------------
# Units.h
# -------------------------------------------------------------------
#def RulesUnits(mb):

# -------------------------------------------------------------------
# Vector3D.h
# -------------------------------------------------------------------
#def RulesVector3D(mb):
  #cl = mb.class_("Vector3D<double>")
  #for fun in cl.member_functions(): # including method 'addNanoParticle' if it doesnt have pointers in argument list
    #if declarations.type_traits.is_reference(fun.return_type):
      #fun.call_policies = call_policies.return_internal_reference( )


# list of additional rules which have to be executed for every processed header file
myRules = {
  'BasicVector3D.h'            : RulesBasicVector3D,
  'Experiment.h'               : RulesExperiment,
  'FormFactorCylinder.h'       : RulesFormFactorCylinder,
  'FormFactorFullSphere.h'     : RulesFormFactorFullSphere,
  'FormFactorPyramid.h'        : RulesFormFactorPyramid,
  'GISASExperiment.h'          : RulesGISASExperiment,
  #'HomogeneousMaterial.h'      : RulesHomogeneousMaterial,
  'IClusteredParticles.h'      : RulesIClusteredParticles,
  'ICompositeSample.h'         : RulesICompositeSample,
  'IFormFactor.h'              : RulesIFormFactor,
  'IInterferenceFunction.h'    : RulesIInterferenceFunction,
  'InterferenceFunctionNone.h' : RulesInterferenceFunctionNone,
  'InterferenceFunction1DParaCrystal' : RulesInterferenceFunction1DParaCrystal,
  #'IMaterial.h'                : RulesIMaterial,
  #'ISingleton.h'               : RulesISingleton,
  'ISample.h'                  : RulesISample,
  'Lattice.h'                  : RulesLattice,
  'LatticeBasis.h'             : RulesLatticeBasis,
  'Layer.h'                    : RulesLayer,
  'LayerDecorator.h'           : RulesLayerDecorator,
  'LayerRoughness.h'           : RulesLayerRoughness,
  'MaterialManager.h'          : RulesMaterialManager,
  'MesoCrystal.h'              : RulesMesoCrystal,
  'MultiLayer.h'               : RulesMultiLayer,
  'Particle.h'                 : RulesParticle,
  'Crystal.h'                  : RulesCrystal,
  'ParticleDecoration.h'       : RulesParticleDecoration,
  #'OpticalFresnel.h'           : RulesOpticalFresnel,
  'Point3D.h'                  : RulesPoint3D,
  'ParameterPool.h'            : RulesParameterPool,
  'PythonOutputData.h'         : RulesPythonOutputData,
  'PythonPlusplusHelper.h'     : RulesPythonPlusplusHelper,
  'Transform3D.h'              : RulesTransform3D,
  #'Types.h'                    : RulesTypes,
  #'Units.h'                    : RulesUnits,
  #'Vector3D.h'                 : RulesVector3D
}

#-------------------------------------------------------------
# GenerateCode()
#-------------------------------------------------------------
def GenerateCode():
  from pyplusplus.file_writers.balanced_files import balanced_files_t
  balanced_files_t.HEADER_EXT='.h'
  balanced_files_t.SOURCE_EXT='.cpp'

  myIncludes.append('/opt/local/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7')
  myIncludes.append('/opt/local/include/')
  mb = module_builder.module_builder_t(files=myFiles, include_paths=myIncludes, gccxml_path='/opt/local/bin')

  # ---------------------------------------------------------
  # common properties
  # ---------------------------------------------------------
  mb.always_expose_using_scope = True

  # Generated code containing errors will not compile on
  mem_funs = mb.calldefs ()
  mem_funs.create_with_signature = True

  # Exclude protected and private that are not pure virtual (we have to expose pure virtual functions to have them overriden in the wrapper)
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
  for x in myFiles:
    if x in myRules:
      myRules[x](mb)

  # set the default return policies (for references/pointers) on classes if it wasn't already been done for
  mem_funs = mb.calldefs()
  for mem_fun in mem_funs:
    if mem_fun.call_policies:
      continue
    if not mem_fun.call_policies and (declarations.is_reference(mem_fun.return_type) or declarations.is_pointer(mem_fun.return_type) ):
      mem_fun.call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )

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
      #, messages.W1036 # pointer to Python immutable member
      #, messages.W1033 # unnamed variables
      #, messages.W1018 # expose unnamed classes
      #, messages.W1049 # returns reference to local variable
      #, messages.W1014 # unsupported '=' operator
       )

  # ---------------------------------------------------------
  # generating output
  # ---------------------------------------------------------
  mb.build_code_creator( module_name=ModuleName)
  mb.code_creator.user_defined_directories.append( os.path.abspath('./') )
  if nOutputFiles > 0:
    mb.balanced_split_module( OutputTempDir, nOutputFiles)
  else:
    mb.write_module( "tmp.cpp")



#-------------------------------------------------------------
# InstallCode()
#-------------------------------------------------------------
def InstallCode():
  files=glob.glob(OutputTempDir+"/*.h");
  files+= glob.glob(OutputTempDir+"/*.cpp");

  copycommand='cp '

  # copying files
  overwriteAnswer=''
  for f in files:
    fileName = os.path.basename(f)

    # we are skipping PythonInterface.main.cpp file since we have somewhere our own 
    if 'main' in f:
      continue

    # different output directory for source and headers
    outputName=''
    if '.cpp' in fileName:
      outputName=InstallDir+"/src/"+fileName
    elif '.h' in fileName:
      outputName=InstallDir+"/inc/"+fileName

    # check file existance
    if os.path.exists(outputName) and overwriteAnswer != 'a':
      prompt="File '"+outputName+"' exists, Overwrite? [y/a/n] "
      overwriteAnswer=raw_input(prompt)
    if overwriteAnswer == 'y' or overwriteAnswer=='a':
      command = copycommand + f + " " + outputName
      print command
      os.system(command)

    else:
      continue



#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
def main():
  if len(sys.argv)!=2:
    print "Usage: 'python codegenerator.py make' - generates python boost wrapping code in ./output subdirectory"
    print "Usage: 'python codegenerator.py install' - installs generated code to GISASFW/PythonAPI"
    print " "

  else:
    if sys.argv[1] == 'make':
      GenerateCode()
    elif sys.argv[1] == 'install':
      InstallCode()
    else:
      print "Nothing to do, run 'python codegenerator.py' to get help"



#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()

  