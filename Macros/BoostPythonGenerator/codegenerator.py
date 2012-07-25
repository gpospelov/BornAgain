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
from pygccxml import declarations


ModuleName = 'PythonInterface'
nOutputFiles = 3 # generated code for classes will be splitted in this number of files
OutputTempDir='output'
InstallDir = '../../Core/PythonAPI'

# list of files to analyse and corresponding functions with rules for analysis
myFiles=[
  'BasicVector3D.h',
  'Experiment.h',
  'FormFactorCylinder.h',
  'FormFactorFullSphere.h',
  'FormFactorPyramid.h',
  'GISASExperiment.h',
  'HomogeneousMaterial.h',
  'IClusteredNanoParticles.h',
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
  'NanoParticle.h',
  'NanoParticleCrystal.h',
  'NanoParticleDecoration.h',
  'OpticalFresnel.h',
  'ParameterPool.h',
##  'Point3D.h',
  'PythonOutputData.h',
  'PythonPlusplusHelper.h',
  'Transform3D.h',
  'Units.h',
  'Types.h',
##  'Vector3D.h',
]
  #'IClusteredNanoParticles.h',

# list of include directories
myIncludes = ['../../Core/Samples/inc','../../Core/Algorithms/inc','../../Core/Tools/inc','../../Core/PythonAPI/inc','../../Core/Geometry/inc']


#-------------------------------------------------------------
#
# additional class-specific rules for parsing
#
#-------------------------------------------------------------

# -------------------------------------------------------------------
# BasicVector3D.h
# -------------------------------------------------------------------
def RulesBasicVector3D(mb):
  cl = mb.class_( "BasicVector3D<double>" )
  for fun in cl.member_functions(): # setting policy for functions returning internal reference
    if declarations.type_traits.is_reference(fun.return_type):
      fun.call_policies = call_policies.return_internal_reference( )

# -------------------------------------------------------------------
# FormFactorPyramid.h
# -------------------------------------------------------------------
def RulesExperiment(mb):
  cl = mb.class_( "Experiment" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()
  cl.member_function("setSample").include()
  cl.member_function("runSimulation").include()
  cl.member_function("setBeamParameters").include()

# -------------------------------------------------------------------
# FormFactorCylinder.h
# -------------------------------------------------------------------
def RulesFormFactorCylinder(mb):
  cl = mb.class_( "FormFactorCylinder" )
  cl.member_functions().exclude() # excluding all member functions
  cl.constructors().exclude() # excluding all constructors
  cl.constructors( arg_types=[ "double", "double" ] ).include() # including constructor with 2 double parameters

# -------------------------------------------------------------------
# FormFactorPyramid.h
# -------------------------------------------------------------------
def RulesFormFactorPyramid(mb):
  cl = mb.class_( "FormFactorPyramid" )
  cl.member_functions().exclude() # excluding all member functions
  cl.constructors().exclude() # excluding all constructors
  cl.constructors( arg_types=[ "double", "double", "double" ] ).include() # including constructor with 3 double parameters

# -------------------------------------------------------------------
# FormFactorFullSphere.h
# -------------------------------------------------------------------
def RulesFormFactorFullSphere(mb):
  cl = mb.class_( "FormFactorFullSphere" )
  cl.member_functions().exclude() # excluding all member functions
  cl.constructors().exclude() # excluding all constructors
  cl.constructors( arg_types=[ "double" ] ).include() # including constructor with 3 double parametes

# -------------------------------------------------------------------
# GISASExperiment.h
# -------------------------------------------------------------------
def RulesGISASExperiment(mb):
  mb.class_( "GISASExperiment" ).member_function( "setDetectorResolutionFunction" ).exclude()

# -------------------------------------------------------------------
# HomogeneousMaterial.h
# -------------------------------------------------------------------
#def RulesHomogeneousMaterial(mb):

# -------------------------------------------------------------------
# IClusteredNanoParticles.h
# -------------------------------------------------------------------
def RulesIClusteredNanoParticles(mb):
  cl = mb.class_( "IClusteredNanoParticles" )
  #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()
  cl.member_function("createTotalFormFactor").call_policies = call_policies.return_value_policy(call_policies.manage_new_object )


# -------------------------------------------------------------------
# ICompositeSample.h
# -------------------------------------------------------------------
def RulesICompositeSample(mb):
  cl = mb.class_( "ICompositeSample" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()
  #cl.member_function( "getCompositeSample" ).include()
  #cl.member_function( "getCompositeSample" ).call_policies = call_policies.return_internal_reference( )

# -------------------------------------------------------------------
# IFormFactor.h
# -------------------------------------------------------------------
def RulesIFormFactor(mb):
  mb.class_( "IFormFactor" ).constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  mb.class_( "IFormFactor" ).member_functions( ).exclude()
  mb.class_( "IBornFormFactor" ).constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  mb.class_( "IBornFormFactor" ).member_functions( ).exclude()

# -------------------------------------------------------------------
# IInterferenceFunction.h
# -------------------------------------------------------------------
def RulesIInterferenceFunction(mb):
  cl = mb.class_( "IInterferenceFunction" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()

# -------------------------------------------------------------------
# InterferenceFunctionNone.h
# -------------------------------------------------------------------
def RulesInterferenceFunctionNone(mb):
  cl = mb.class_( "InterferenceFunctionNone" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()

# -------------------------------------------------------------------
# InterferenceFunction1DParaCrystal.h
# -------------------------------------------------------------------
def RulesInterferenceFunction1DParaCrystal(mb):
  cl = mb.class_( "InterferenceFunction1DParaCrystal" )
  cl.member_functions().exclude()
  
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
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions().exclude()
  #cl.member_function( "getCompositeSample" ).include()
  #cl.member_function( "getCompositeSample" ).call_policies = call_policies.return_internal_reference( )

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
  cl.member_function( "clone" ).exclude()
  cl.member_function( "setThickness" ).exclude()
  cl.member_function( "getThickness" ).exclude()
  cl.member_function( "getMaterial" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )
  cl.member_function( "getRefractiveIndex" ).exclude()
  cl.member_function( "createDWBASimulation" ).exclude()
  cl.member_functions( "setMaterial" ).include()

# -------------------------------------------------------------------
# LayerDecorator.h
# -------------------------------------------------------------------
def RulesLayerDecorator(mb):
  cl = mb.class_( "LayerDecorator" )
  cl.constructors( ).exclude() # excluding all constructors
  cl.member_functions( ).exclude() # excluding all member functions
  cl.constructors( lambda x: len(x.arguments)==2).include() # including constructor with two parameters

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
  cl.member_function( "getMaterial" ).call_policies = call_policies.return_internal_reference( )
  cl.member_function( "addHomogeneousMaterial" ).call_policies = call_policies.return_internal_reference( )
  cl.disable_warnings( messages.W1051 ) # not sure

# -------------------------------------------------------------------
# MesoCrystal.h
# -------------------------------------------------------------------
def RulesMesoCrystal(mb):
  cl = mb.class_( "MesoCrystal" )
  cl.member_functions( ).exclude() # excluding all member functions, leaving only constructors
  for fun in cl.constructors(): # excluding constructors which have pointers
    for arg in fun.arguments:
      if declarations.type_traits.is_pointer(arg.type):
        fun.exclude()

  
# -------------------------------------------------------------------
# MultiLayer.h
# -------------------------------------------------------------------
def RulesMultiLayer(mb):
  cl = mb.class_( "MultiLayer" )
  cl.member_function( "getLayer" ).exclude();
  cl.member_function( "getLayerBottomZ" ).exclude();
  cl.member_function( "getLayerThickness" ).exclude();
  cl.member_function( "getLayerTopInterface" ).exclude();
  cl.member_function( "getLayerBottomInterface" ).exclude();
  cl.member_function( "clear" ).exclude();
  cl.member_function( "clone" ).exclude()
  cl.member_function( "getCrossCorrSpectralFun" ).exclude();
  cl.member_function( "setLayerThickness" ).exclude();
  cl.member_function( "createDWBASimulation" ).exclude()

# -------------------------------------------------------------------
# NanoParticle.h
# -------------------------------------------------------------------
def RulesNanoParticle(mb):
  cl = mb.class_( "NanoParticle" )
  cl.member_functions( ).exclude() # excluding all member functions, leaving only constructors
  for fun in cl.constructors(): # excluding constructors which have pointers
    for arg in fun.arguments:
      if declarations.type_traits.is_pointer(arg.type):
        fun.exclude()

# -------------------------------------------------------------------
# NanoParticleCrystal.h
# -------------------------------------------------------------------
def RulesNanoParticleCrystal(mb):
  cl = mb.class_( "NanoParticleCrystal" )
  cl.member_functions( ).exclude() # excluding all member functions, leaving only constructors
  cl.member_function("createTotalFormFactor").call_policies = call_policies.return_value_policy(call_policies.manage_new_object )
  #cl.member_function("setAmbientRefractiveIndex").include()


# -------------------------------------------------------------------
# NanoParticleDecoration.h
# -------------------------------------------------------------------
def RulesNanoParticleDecoration(mb):
  cl = mb.class_( "NanoParticleDecoration" )
  cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
  cl.member_functions( ).exclude() # exclude all member functions
  # including following methods if they doesn't have pointers in argument list
  methods = ['addNanoParticle', 'addInterferenceFunction']
  for m in methods:
    for fun in cl.member_functions(m): # including methods if they don't have pointers in argument list
      has_pointers = False
      for arg in fun.arguments:
        if declarations.type_traits.is_pointer(arg.type):
          has_pointers = True
      if not has_pointers:
        fun.include()

# -------------------------------------------------------------------
# OpticalFresnel.h
# -------------------------------------------------------------------
#def RulesOpticalFresnel(mb):

# -------------------------------------------------------------------
# Point3D.h
# -------------------------------------------------------------------
def RulesPoint3D(mb):
  cl = mb.class_( "Point3D<double>" )
  for fun in cl.member_functions(): 
    if declarations.type_traits.is_reference(fun.return_type):
      fun.call_policies = call_policies.return_internal_reference( )


# -------------------------------------------------------------------
# ParameterPool.h
# -------------------------------------------------------------------
def RulesParameterPool(mb):
  cl = mb.class_( "ParameterPool" )
  cl.member_function( "cloneWithPrefix" ).call_policies = call_policies.return_value_policy(call_policies.manage_new_object )

# -------------------------------------------------------------------
# PythonOutputData.h
# -------------------------------------------------------------------
#def RulesPythonOutputData(mb):
  #mb.free_function('ExportOutputData').exclude()
  #mb.free_function('GetOutputData').exclude()
  #mb.free_function('GetOutputData').call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )

# -------------------------------------------------------------------
# PythonPlusplusHelper.h
# -------------------------------------------------------------------
def RulesPythonPlusplusHelper(mb):
  mb.class_('PythonPlusplusHelper').exclude() # given class is only to teach pyplusplus to templates, but we do not need class itself to be visible in python, excluding it...

# -------------------------------------------------------------------
# Transform3D.h
# -------------------------------------------------------------------
def RulesTransform3D(mb):
  cl = mb.class_( "Transform3D" )
  for fun in cl.member_functions(): # setting policy for functions returning internal reference
    if declarations.type_traits.is_reference(fun.return_type):
      fun.call_policies = call_policies.return_internal_reference( )
  mb.class_( "Reflect3D" ).exclude()
  mb.class_( "Translate3D" ).exclude()
  mb.class_( "TranslateX3D" ).exclude()
  mb.class_( "TranslateY3D" ).exclude()
  mb.class_( "TranslateZ3D" ).exclude()
  mb.class_( "Scale3D" ).exclude()
  mb.class_( "ScaleX3D" ).exclude()
  mb.class_( "ScaleY3D" ).exclude()
  mb.class_( "ScaleZ3D" ).exclude()


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
def RulesVector3D(mb):
  cl = mb.class_("Vector3D<double>")
  for fun in cl.member_functions(): # including method 'addNanoParticle' if it doesnt have pointers in argument list
    if declarations.type_traits.is_reference(fun.return_type):
      fun.call_policies = call_policies.return_internal_reference( )


# list of additional rules which have to be executed for every processed header file
myRules = {
  'BasicVector3D.h'            : RulesBasicVector3D,
  'Experiment.h'               : RulesExperiment,
  'FormFactorCylinder.h'       : RulesFormFactorCylinder,
  'FormFactorFullSphere.h'     : RulesFormFactorFullSphere,
  'FormFactorPyramid.h'        : RulesFormFactorPyramid,
  'GISASExperiment.h'          : RulesGISASExperiment,
  #'HomogeneousMaterial.h'      : RulesHomogeneousMaterial,
  'IClusteredNanoParticles.h'    : RulesIClusteredNanoParticles,
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
  'NanoParticle.h'             : RulesNanoParticle,
  'NanoParticleCrystal.h'      : RulesNanoParticleCrystal,
  'NanoParticleDecoration.h'   : RulesNanoParticleDecoration,
  #'OpticalFresnel.h'           : RulesOpticalFresnel,
  'Point3D.h'                  : RulesPoint3D,
  'ParameterPool.h'            : RulesParameterPool,
  #'PythonOutputData.h'         : RulesPythonOutputData,
  'PythonPlusplusHelper.h'     : RulesPythonPlusplusHelper,
  'Transform3D.h'              : RulesTransform3D,
  #'Types.h'                    : RulesTypes,
  #'Units.h'                    : RulesUnits,
  'Vector3D.h'                 : RulesVector3D
}

#-------------------------------------------------------------
# GenerateCode()
#-------------------------------------------------------------
def GenerateCode():
  from pyplusplus.file_writers.balanced_files import balanced_files_t
  balanced_files_t.HEADER_EXT='.h'
  balanced_files_t.SOURCE_EXT='.cpp'

  myIncludes.append('/opt/local/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7')
  mb = module_builder.module_builder_t(files=myFiles, include_paths=myIncludes, gccxml_path='/opt/local/bin')

  # ---------------------------------------------------------
  # common properties
  # ---------------------------------------------------------
  mb.always_expose_using_scope = False

  # excluding generation of access code for  private methods
  mb.calldefs( access_type_matcher_t( 'private' ) ).exclude()

  # excluding generation of access code for protected methods
  mb.calldefs( access_type_matcher_t( 'protected' ) ).exclude()

  # excluding generation of methods for implicit conversion
  mb.constructors().allow_implicit_conversion = False

  # policy for singletons and clone methods
  classes = mb.classes();
  for cs in classes:
    cs.member_functions('instance',allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
    cs.member_functions('clone',allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )

  # excluding all member functions which have pointers in argument list to not to bother our self with python<-->cpp object ownership, only const references is allowed
  #for fun in mb.member_functions():
    #for arg in fun.arguments:
      #if declarations.type_traits.is_pointer(arg.type):
        #fun.exclude()

  # excluding all operators
  #mb.member_operators( lambda x: x.name in ("operator++", "operator--",
                                            #"operator*", "operator->",
                                            #"operator()", "operator[]") ).exclude()
  mb.member_operators( lambda x: x.name in ("operator>>","operator()") ).exclude()

  # disable some warnings
  messages.disable( messages.W1035 )

  #Generated code will not compile on
  mem_funs = mb.calldefs ()
  mem_funs.create_with_signature = True

  # ---------------------------------------------------------
  # calling class individual parsing properties
  # ---------------------------------------------------------
  for x in myFiles:
    if x in myRules:
      myRules[x](mb)

  # ---------------------------------------------------------
  # generating output
  # ---------------------------------------------------------
  mb.build_code_creator( module_name=ModuleName)
  mb.code_creator.user_defined_directories.append( os.path.abspath('./') )
  if nOutputFiles > 0:
    mb.balanced_split_module( OutputTempDir, nOutputFiles)
  else:
    mb.write_module( "tmp.cpp")
#---


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

    # we are skipping files like PythonInterface.main.cpp
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
# ---


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
# ---


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()
# ---





    #X.constructor( arg_types=[ "StochasticParameter<double> *", "StochasticParameter<double> *", "StochasticParameter<double> *" ] ).exclude()

  #def criteria( constructor ):
    #if len( constructor.arguments ) != 3:
        #return False
    #arg0_type = constructor.arguments[0].type
    #print arg0_type
    #if "StochasticParameter" in arg0_type:
      #return False
    #else:
      #return True
    #if not declarations.is_pointer( arg0_type ):
        #return
    #tmp = declarations.remove_pointer( arg0_type ):
    #if not declarations.is_const( tmp ):
         #return False
    #return declarations.is_same( declarations.remove_const( tmp ),mb.class_( "Y" ) )

  #X.constructors(criteria).exclude()
  #mb.class_( "Renderer" ).member_function( "GetDrawTools", return_type = '::xfx::DrawTools const &' ).exclude( )






    #mb.class_( "MaterialManager" ).constructors().exclude()
  #mb.class_( "MaterialManager" ).member_function( "getMaterial" ).call_policies = call_policies.return_internal_reference( )
  #mb.class_( "MaterialManager" ).member_function( "addHomogeneousMaterial" ).call_policies = call_policies.return_internal_reference( )
  ##mb.class_( "MaterialManager" ).member_function( "getMaterial" ).call_policies = call_policies.reference_existing_object( )
  ##mb.class_( "MaterialManager" ).member_function( "addHomogeneousMaterial" ).call_policies = call_policies.reference_existing_object( )
  ##mb.class_( "MaterialManager" ).disable_warnings( messages.W1035 )

  ##mb.class_( "ISample" ).member_function( "getCompositeSample" ).call_policies = call_policies.return_self( )
  ##mb.class_( "ISample" ).member_function( "createParameterTreeTest" ).exclude()
  ##mb.class_( "ISample" ).member_function( "getParameterPool" ).call_policies = call_policies.return_internal_reference( )
  ##mb.class_( "ISample" ).member_function( "createParameterTree" ).call_policies = call_policies.manage_new_object( )
  ##mb.class_( "ISample" ).member_function( "clone" ).call_policies = call_policies.custom_call_policies("bp::return_value_policy<bp::clone_const_reference>")

  #mb.class_( "LayerRoughness" ).member_function( "getSpectralFun" ).exclude()
  #mb.class_( "LayerRoughness" ).member_function( "getCorrFun" ).exclude()

  ##mb.class_( "ParameterPool" ).member_function( "cloneWithPrefix" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )
  #mb.class_( "ParameterPool" ).member_function( "cloneWithPrefix" ).call_policies = call_policies.return_value_policy(call_policies.manage_new_object )
  ##mb.class_( "ParameterPool" ).member_function( "begin" ).exclude()
  ##mb.class_( "ParameterPool" ).member_function( "end" ).exclude()
  #mb.class_( "MaterialManager" ).disable_warnings( messages.W1051 ) # not sure

  #mb.class_( "Layer" ).member_function( "clone" ).exclude()
  #mb.class_( "Layer" ).member_function( "setThickness" ).exclude()
  #mb.class_( "Layer" ).member_function( "getThickness" ).exclude()
  #mb.class_( "Layer" ).member_function( "getMaterial" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )
  #mb.class_( "Layer" ).member_function( "getRefractiveIndex" ).exclude()
  ##mb.class_( "Layer" ).member_function( "getMaterial" ).call_policies = call_policies.return_internal_reference( )
  #mb.class_( "Layer" ).member_function( "createDWBASimulation" ).exclude()

  #mb.class_( "MultiLayer" ).member_function( "getLayer" ).exclude();
  #mb.class_( "MultiLayer" ).member_function( "getLayerBottomZ" ).exclude();
  #mb.class_( "MultiLayer" ).member_function( "getLayerThickness" ).exclude();
  #mb.class_( "MultiLayer" ).member_function( "getLayerTopInterface" ).exclude();
  #mb.class_( "MultiLayer" ).member_function( "getLayerBottomInterface" ).exclude();
  #mb.class_( "MultiLayer" ).member_function( "clear" ).exclude();
  #mb.class_( "MultiLayer" ).member_function( "clone" ).exclude()
  #mb.class_( "MultiLayer" ).member_function( "getCrossCorrSpectralFun" ).exclude();
  #mb.class_( "MultiLayer" ).member_function( "setLayerThickness" ).exclude();
  ##mb.class_( "MultiLayer").member_function( "getDWBASimulation" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )
  #mb.class_( "MultiLayer" ).member_function( "createDWBASimulation" ).exclude()

  ##mb.namespace('Units').exclude()
  ##mb.variables().always_expose_using_scope = True
  ##mb.classes().always_expose_using_scope = True

  ## OpticalFresnel
  ##mb.class_('KVector<double>').already_exposed=True
  ##mb.class_('MultiLayer').already_exposed=True
  ##mb.class_('PyHelperKVector').exclude()

  ## from PythonPlusplusHelper.h - we do not need these classes visbile in python
  #mb.class_('PythonPlusplusKVector').exclude()


  ## from PythonOutputData.h
  #print mb
  #mb.free_function('ExportOutputData').exclude()


# -----
# mb.class_( "DrawTools" ).member_functions( "PushDraw2DSprite" ).rename( "push_draw_2d_sprite" )

# http://nullege.com/codes/show/src@p@y@python-ogre-HEAD@python-ogre@code_generators@cegui@generate_code.py
#https://svn.janelia.org/penglab/projects/vaa3d/trunk/experimental/brunsc/python_console/wrap_v3d_boost.py
#http://www.koders.com/python/fid4297F8DF95E4911ADD6CA942FC59D01FC0455A63.aspx?s=matrix#L237


  #default constructor does not have arguments
  #mb.class_( "NanoParticleDecoration" ).constructors( lambda decl: bool( decl.arguments ), allow_empty=True, recursive=True ).include()

  # ---- Exclude non-default constructors
  #mb.class_( "NanoParticleDecoration" ).constructors( lambda decl: bool( decl.arguments ), allow_empty=True, recursive=True ).exclude() # exclude non-default constructors

  # - how to select function having name
  #mb.class_( "NanoParticleDecoration" ).member_functions( lambda x: x.name.startswith('addNanoParticle') ).include()

  # ---- loop over constructors
  #def criteria( constructor ):
    #print len(constructor.arguments)
    #for a in constructor.arguments:
      ##print a
      #print a.type
    ###if len( constructor.arguments ) != 1:
        ###return False
    ###arg0_type = constructor.arguments[0].type
  #mb.class_( "NanoParticleDecoration" ).constructors( criteria )

  #--- probably exclude whole class NanoParticle
  #mb.class_( "NanoParticle" ).include(already_exposed=True)

#  simtk.class_('CoordinateAxis').constructors(arg_types=[None]).exclude()

# ---- exclude most operators
 ## default: exclude most operators
    #mb.member_operators( lambda x: x.name in ("operator++", "operator--",
                                              #"operator*", "operator->",
                                              #"operator()", "operator[]") ).exclude()

#mb.free_functions( lambda mem_fun: mem_fun.name.startswith( prefix )).exclude()

#       if declarations.is_pointer (fun.return_type) and not fun.documentation:

    ## problem with a constructor on Cloth
    #main_ns.class_('::NxOgre::Cloth').constructor(arg_types=[None,'::NxClothDesc','::NxMeshData',None,None]).exclude()

    ## functions specified in the headers but not implemented
    #main_ns.class_('::NxOgre::Blueprints::ActorBlueprint').member_function('unserialise',arg_types=[None]).exclude()

    
        #for op in cls.casting_operators():
            #if op.name.find("QVariant") >= 0:
                #op.exclude()
                