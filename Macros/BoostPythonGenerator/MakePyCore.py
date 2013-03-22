# generate python API wrappers for Core library
# used by codegenerator.py

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
  'BasicVector3D.h',
  'Bin.h',
  'Crystal.h',
  'DiffuseParticleInfo.h',
  'FTDistributions.h',
  'FormFactorBox.h',
  'FormFactorCrystal.h',
  'FormFactorCylinder.h',
  'FormFactorDecoratorDebyeWaller.h',
  'FormFactorFullSphere.h',
  'FormFactorGauss.h',
  'FormFactorLorentz.h',
  'FormFactorParallelepiped.h',
  'FormFactorPrism3.h',
  'FormFactorPyramid.h',
  'FormFactorSphereGaussianRadius.h',
  'HomogeneousMaterial.h',
  'ICloneable.h',
  'IClusteredParticles.h',
  'ICompositeSample.h',
  'IDecoration.h',
  'IFormFactor.h',
  'IFormFactorBorn.h',
  'IFormFactorDecorator.h',
  'IInterferenceFunction.h',
  'IMaterial.h',
  'IParameterized.h',
  'ISample.h',
  'ISampleBuilder.h',
  'ISelectionRule.h',
  'ISingleton.h',
  'Instrument.h',
  'InterferenceFunction1DParaCrystal.h',
  'InterferenceFunction2DLattice.h',
  'InterferenceFunction2DParaCrystal.h',
  'InterferenceFunctionNone.h',
  'Lattice.h',
  'Lattice2DIFParameters.h',
  'LatticeBasis.h',
  'Layer.h',
  'LayerDecorator.h',
  'LayerRoughness.h',
  'Lattice2DIFParameters.h',
  'MaterialManager.h',
  'MesoCrystal.h',
  'MultiLayer.h',
  'OpticalFresnel.h',
  'ParameterPool.h',
  'Particle.h',
  'ParticleBuilder.h',
  'ParticleCoreShell.h',
  'ParticleDecoration.h',
  'ParticleInfo.h',
  'PositionParticleInfo.h',
  'PythonOutputData.h',
  'PythonPlusplusHelper.h',
  'RealParameterWrapper.h',
  'Simulation.h',
  'SimulationParameters.h',
  'IStochasticParameter.h',
  'StochasticGaussian.h',
  'StochasticSampledParameter.h',
  'StochasticDoubleGate.h',
  'Transform3D.h',
  'Types.h',
  'Units.h',
]

# list of include directories
myIncludes = ['../../Core/Samples/inc','../../Core/FormFactors/inc','../../Core/Algorithms/inc','../../Core/Tools/inc','../../Core/PythonAPI/inc','../../Core/Geometry/inc']


# -------------------------------------------------------------------
# AdditionalRules
# -------------------------------------------------------------------
def AdditionalRules(mb):

  # --- BasicVector3D.h -----------------------------------------------
  if "BasicVector3D.h" in myFiles:
    ##cl = mb.class_("BasicVector3D<std::complex<double> >")
    #mb.classes(lambda decl: 'Geometry::BasicVector3D<std::complex<double> >' in decl.decl_string ).exclude()
    #mb.free_operators( lambda decl: 'Geometry::BasicVector3D<std::complex<double> >' in decl.decl_string ).exclude()
    #mb.free_functions( lambda decl: 'Geometry::BasicVector3D<std::complex<double> >' in decl.decl_string ).exclude()
    #mb.classes(lambda decl: 'Geometry::BasicVector3D<std::complex<double> const>' in decl.decl_string ).exclude()
    #mb.free_operators( lambda decl: 'Geometry::BasicVector3D<std::complex<double> const>' in decl.decl_string ).exclude()
    #mb.free_functions( lambda decl: 'Geometry::BasicVector3D<std::complex<double> const>' in decl.decl_string ).exclude()
    classes = mb.classes()
    # here we have to exclude all templated methods which are not defined complex<double>, otherwise py++ will try to generate wrappers
    MethodsWhichAreNotSuitable=[
        "phi", "theta", "cosTheta", "getPhi", "getTheta", "setPhi", "setTheta", "setR",
        "setMag", "perp", "perp2", "setPerp", "angle", "unit", "orthogonal",
        "rotate","rotateX","rotateY","rotateZ"
    ]
    for cl in classes:
      if "BasicVector3D<std::complex<double> >" in cl.decl_string or "BasicVector3D<double>" in cl.decl_string or "BasicVector3D<int>" in cl.decl_string:
        for fun in cl.member_functions(allow_empty=True):
          MethodIsBad = False
          for x in MethodsWhichAreNotSuitable:
            if fun.name == x:
              MethodIsBad = True
          if MethodIsBad:
            fun.exclude()

    MethodsWhichAreNotUsed=["dot","mag","mag2","cross","magxy","magxy2","transform"]
    for cl in classes:
      if "BasicVector3D<int>" in cl.decl_string:
        for fun in cl.member_functions(allow_empty=True):
          MethodIsBad = False
          for x in MethodsWhichAreNotUsed:
            if fun.name == x:
              MethodIsBad = True
          if MethodIsBad:
            fun.exclude()

  #if "FTDistributions.h" in myFiles:
      #cl = mb.class_("IFTDistribution2D")
      #cl = mb.class_("FTDistribution2DCauchy")
      #cl.member_function("transformToStarBasis").exclude()
      


  # --- Experiment.h --------------------------------------------------
  if "Experiment.h" in myFiles:
    cl = mb.class_( "Experiment" )
    cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    #cl.member_functions().exclude()
    #cl.member_function("runSimulation").include()
    #cl.member_function("normalize").include()
    #cl.member_function("setBeamParameters").include()
    #cl.member_function("setBeamIntensity").include()
    #cl.member_function("setSample").include()
    #cl.member_function("setSampleBuilder").include()

  # --- FormFactorCylinder.h ------------------------------------------
  if "FormFactorCrystal.h" in myFiles:
    cl = mb.class_( "FormFactorCrystal" )
    cl.member_function("evaluate").exclude()
    cl.member_function("evaluate_for_q").exclude()


  # --- FormFactorCylinder.h ------------------------------------------
  #if "FormFactorCylinder.h" in myFiles:
    #cl = mb.class_( "FormFactorCylinder" )

  # --- FormFactorDecoratorDebyeWaller.h ------------------------------
  #if "FormFactorDecoratorDebyeWaller" in myFiles:
    #cl = mb.class_( "FormFactorDecoratorDebyeWaller" )

  # --- FormFactorFullSphere.h ----------------------------------------
  #if "FormFactorFullSphere.h" in myFiles:
    #cl = mb.class_( "FormFactorFullSphere" )

  # --- FormFactorPyramid.h -------------------------------------------
  #if "FormFactorPyramid.h" in myFiles:
    #cl = mb.class_( "FormFactorPyramid" )

  # --- FormFactorSphereGaussianRadius.h ------------------------------
  if "FormFactorSphereGaussianRadius.h" in myFiles:
    cl = mb.class_( "FormFactorSphereGaussianRadius" )
    cl.member_functions("createDistributedFormFactors").exclude()

  # --- GISASExperiment.h ---------------------------------------------
  if "GISASExperiment.h" in myFiles:
    cl = mb.class_( "GISASExperiment" )
    cl.member_function( "setDetectorResolutionFunction" ).exclude()

  # --- HomogeneousMaterial.h -----------------------------------------
  #if "HomogeneousMaterial.h" in myFiles:
    #cl = mb.class_( "HomogeneousMaterial" )

  # --- IClusteredParticles.h -----------------------------------------
  #if "IClusteredParticles.h" in myFiles:
    #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    #cl.member_function("createTotalFormFactor").call_policies = call_policies.return_value_policy(call_policies.manage_new_object )

  # --- ICompositeSample.h --------------------------------------------
  if "ICompositeSample.h" in myFiles:
    cl = mb.class_( "ICompositeSample" )
    #cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    #cl.member_functions().exclude()
    cl.member_function( "createIterator" ).exclude()

  # --- IFormFactor.h -------------------------------------------------
  #if "IFormFactor.h" in myFiles:
    #cl = mb.class_( "IFormFactor" )

  # --- IFormFactorBorn.h ---------------------------------------------
  #if "IFormFactorBorn.h" in myFiles:
    #cl = mb.class_( "IFormFactorBorn" )

  # --- IFormFactorBornSeparable.h ------------------------------------
  #if "IFormFactorBornSeparable.h" in myFiles:
    #cl = mb.class_( "IFormFactorBornSeparable" )

  # --- IFormFactorDecorator.h ----------------------------------------
  #if "IFormFactorDecorator.h" in myFiles:
    #cl = mb.class_( "IFormFactorDecorator" )

  # --- IInterferenceFunction.h ---------------------------------------
  #if "IInterferenceFunction.h" in myFiles:
    #cl = mb.class_( "IInterferenceFunction" )

  # --- InterferenceFunctionNone.h ------------------------------------
  #if "InterferenceFunctionNone.h" in myFiles:
    #cl = mb.class_( "InterferenceFunctionNone" )

  # --- InterferenceFunction1DParaCrystal.h ---------------------------
  #if "InterferenceFunction1DParaCrystal.h" in myFiles:
    #cl = mb.class_( "InterferenceFunction1DParaCrystal" )

  # --- IMaterial.h ---------------------------------------------------
  #if "IMaterial.h" in myFiles:
    #cl = mb.class_( "IMaterial" )

  # --- IParameterized.h ----------------------------------------------
  #if "IParameterized.h" in myFiles:
    #cl = mb.class_( "IParameterized" )
    #cl.member_functions().exclude()
    #cl.member_function( "createParameterTree" ).include()
    #cl.member_function( "addParametersToExternalPool" ).include()

  # --- ISingleton.h --------------------------------------------------
  #if "ISingleton.h" in myFiles:
    #cl = mb.class_( "ISingleton" )

  # --- ISample.h -----------------------------------------------------
  if "ISample.h" in myFiles:
    cl = mb.class_( "ISample" )
    cl.member_functions().exclude()
    cl.member_function( "clone" ).include()
    cl.member_function("print_structure").include()

  # --- ISampleBuilder.h ----------------------------------------------
  if "ISampleBuilder.h" in myFiles:
    cl = mb.class_( "ISampleBuilder" )
    cl.member_functions().exclude()
    cl.member_function( "buildSample" ).include()
    cl.member_function( "buildSample" ).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )

  # --- Lattice.h -----------------------------------------------------
  if "Lattice.h" in myFiles:
    cl = mb.class_( "Lattice" )
    cl.member_functions().exclude()
    cl.member_function("getBasisVectorA").include()
    cl.member_function("getBasisVectorB").include()
    cl.member_function("getBasisVectorC").include()
    cl.member_function("createTrigonalLattice").include()
    cl.member_function("createTrigonalLattice").call_policies = call_policies.return_value_policy(call_policies.return_by_value )
    cl.member_function("setSelectionRule").include()

  # --- LatticeBasis.h ------------------------------------------------
  if "LatticeBasis.h" in myFiles:
    cl = mb.class_( "LatticeBasis" )
    cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    cl.member_functions().exclude()
    cl.member_function("addParticle").include()

  # --- Layer.h -------------------------------------------------------
  if "Layer.h" in myFiles:
    cl = mb.class_( "Layer" )
    cl.member_function( "createDWBASimulation" ).exclude()
    # we need to include back setMaterial methods since they have pointers in argument list (and our default policy is to exclude them)
    for fun in cl.member_functions():
      if fun.name == "setMaterial":
        fun.include()
        print fun
    # including back constructors with pointers (general policy is to exclude them)
    cl.constructors().include()

  # --- LayerDecorator.h ----------------------------------------------
  if "LayerDecorator.h" in myFiles:
    cl = mb.class_( "LayerDecorator" )
    cl.member_functions().exclude()
    #cl.member_function( "createDiffuseDWBASimulation").exclude()
    #cl.member_function( "createDWBASimulation").exclude()
    #cl.member_function( "createStrategy").exclude()

  # --- LayerRoughness.h ----------------------------------------------
  if "LayerRoughness.h" in myFiles:
    cl = mb.class_( "LayerRoughness" )
    cl.member_function( "getSpectralFun" ).exclude()
    cl.member_function( "getCorrFun" ).exclude()

  # --- MaterialManager.h ---------------------------------------------
  if "MaterialManager.h" in myFiles:
    cl = mb.class_( "MaterialManager" )
    cl.constructors().exclude()

  # --- MesoCrystal.h -------------------------------------------------
  if "MesoCrystal.h" in myFiles:
    cl = mb.class_( "MesoCrystal" )
    cl.member_functions( ).exclude() # excluding all member functions, leaving only constructors

  # --- MultiLayer.h --------------------------------------------------
  if "MultiLayer.h" in myFiles:
    cl = mb.class_( "MultiLayer" )
    cl.member_functions( ).exclude()
    cl.member_function( "addLayer" ).include()
    cl.member_function( "addLayer" ).include()
    cl.member_function( "addLayerWithTopRoughness" ).include()

  # --- Particle.h ----------------------------------------------------
  if "Particle.h" in myFiles:
    cl = mb.class_( "Particle" )
    cl.member_function( "createDiffuseParticleInfo" ).exclude()
    cl.member_function( "createDistributedParticles" ).exclude()

  # --- Crystal.h -----------------------------------------------------
  #if "Crystal.h" in myFiles:
    #cl = mb.class_( "Crystal" )

  # --- ParticleDecoration.h ------------------------------------------
  if "ParticleDecoration.h" in myFiles:
    cl = mb.class_( "ParticleDecoration" )
    cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    #cl.member_function("createStrategy").exclude()

  #if "ParticleInfo.h" in myFiles:
    #cl = mb.class_( "ParticleInfo" )



  # --- OpticalFresnel.h ----------------------------------------------
  #if "OpticalFresnel.h" in myFiles:
    #cl = mb.class_( "OpticalFresnel" )

  # --- Point3D.h -----------------------------------------------------
  #if "Point3D.h" in myFiles:
    #cl = mb.class_( "Point3D<double>" )

  # --- ParameterPool.h -----------------------------------------------
  if "ParameterPool.h" in myFiles:
    cl = mb.class_( "ParameterPool" )
    cl.member_function("registerParameter").include()
    cl.member_function("registerParameter").add_transformation( FT.from_address( 1 ) )
    cl.member_function("getMatchedParameters").exclude()

  # --- ParameterPool.h -----------------------------------------------
  if "ParticleCoreShell.h" in myFiles:
    cl = mb.class_( "ParticleCoreShell" )
    cl.member_functions().exclude()

  # --- PythonOutputData.h --------------------------------------------
  if "PythonOutputData.h" in myFiles:
    # these functions returns PyObject, the empty custom policy is the only way I know
    mb.free_function('GetOutputData').call_policies = call_policies.custom_call_policies("")
    mb.free_function('GetOutputDataAxis').call_policies = call_policies.custom_call_policies("")

  # --- PythonPlusplusHelper.h ----------------------------------------
  if "PythonPlusplusHelper.h" in myFiles:
    cl = mb.class_( "PythonPlusplusHelper" )
    cl.exclude() # given class is only to teach pyplusplus to templates, but we do not need class itself to be visible in python, excluding it...

  # --- RealParameterWrapper.h ----------------------------------------
  if "RealParameterWrapper.h" in myFiles:
    cl = mb.class_('RealParameterWrapper') # given class is only to teach pyplusplus to templates, but we do not need class itself to be visible in python, excluding it...
    cl.member_functions().exclude()
    cl.member_function("setValue").include()
    cl.member_function("getValue").include()
    cl.member_function("isNull").include()

  if "Simulation.h" in myFiles:
    mb.class_('DWBASimulation').exclude()

  # --- Transform3D.h -------------------------------------------------
  #if "Transform3D.h" in myFiles:
    # removing mentioning of Point3D from constructors and member_functions
    #mb.class_( "Point3D<double>").exclude()
    #TransformClasses={"Transform3D","Reflect3D","Translate3D", "Scale3D", "Rotate3D"}
    #for clname in TransformClasses:
      #cl = mb.class_(clname)
      #cl.constructors(lambda decl: 'Point3D' in decl.decl_string, allow_empty=True ).exclude()
      #cl.member_functions(lambda decl: 'Point3D' in decl.decl_string, allow_empty=True ).exclude()

  # --- Types.h -------------------------------------------------------
  if "Types.h" in myFiles:
    cl = mb.class_("KVectorContainer")
    cl.exclude()


def MakePythonAPI(OutputTempDir):
  from pyplusplus.file_writers.balanced_files import balanced_files_t
  balanced_files_t.HEADER_EXT='.h'
  balanced_files_t.SOURCE_EXT='.cpp'
  from pyplusplus.file_writers.multiple_files import multiple_files_t
  multiple_files_t.HEADER_EXT='.pypp.h'
  multiple_files_t.SOURCE_EXT='.pypp.cpp'

  #GCCXML_COMPILER="/opt/local/bin/g++"
  #GCCXML_CXXFLAGS=""

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
  mb.split_module( OutputTempDir)
  #nOutputFiles = 8 # generated code for classes will be splitted in this number of files
  #if nOutputFiles > 0:
    #mb.split_module( OutputTempDir)
    #mb.balanced_split_module( OutputTempDir, nOutputFiles)
  #else:
    #mb.write_module( "tmp.cpp")

#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  PyCoreTempDir='output/PyCore'
  if not os.path.exists(PyCoreTempDir): os.makedirs(PyCoreTempDir)
  MakePythonAPI(PyCoreTempDir)
