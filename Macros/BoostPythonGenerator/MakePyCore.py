# generate python API wrappers for Core library
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


import builder_rules


include_dirs = [
    '../../Core/Samples/inc',
    '../../Core/FormFactors/inc',
    '../../Core/Algorithms/inc',
    '../../Core/Tools/inc',
    '../../Core/PythonAPI/inc',
    '../../Core/Geometry/inc'
]

include_classes = [
"BasicVector3D<double>",
"BasicVector3D<std::complex<double> >",
"Beam",
"Bin1D",
"Bin1DCVector",
"Crystal",
"Detector",
"FTDistribution2DCauchy",
"FormFactorBox",
"FormFactorCone",
"FormFactorCylinder",
"FormFactorDecoratorDebyeWaller",
"FormFactorEllipsoid",
"FormFactorFullSphere",
"FormFactorFullSpheroid",
"FormFactorGauss",
"FormFactorHemiSpheroid",
"FormFactorLorentz",
"FormFactorParallelepiped",
"FormFactorPrism3",
"FormFactorPrism6",
"FormFactorPyramid",
"FormFactorSphere",
"HomogeneousMaterial",
"IAxis",
"ICloneable",
"IClusteredParticles",
"ICompositeSample",
"IDecoration",
"IDetectorResolution",
"IFTDistribution2D",
"IFormFactor",
"IFormFactorBorn",
"IInterferenceFunction",
"IMaterial",
"IParameterized",
"IResolutionFunction2D",
"ISample",
"ISampleBuilder",
"ISelectionRule",
"ITransform3D",
"Instrument",
"InterferenceFunction1DParaCrystal",
"InterferenceFunction2DLattice",
"InterferenceFunction2DParaCrystal",
"InterferenceFunctionNone",
"Lattice",
"Lattice2DIFParameters",
"LatticeBasis",
"Layer",
"LayerDecorator",
"LayerInterface",
"LayerRoughness",
"MaterialManager",
"MultiLayer",
"OutputData<double>",
"OutputDataIOFactory",
"ParameterPool",
"Particle",
"Particle",
"ParticleCoreShell",
"ParticleBuilder",
"ParticleDecoration",
"ParticleInfo",
"PositionParticleInfo",
"RealParameterWrapper",
"ResolutionFunction2DSimple",
"RotateY_3D",
"RotateZ_3D",
"Simulation",
"SimulationParameters",
"StochasticDoubleGate",
"StochasticDoubleGaussian",
"StochasticParameter<double>",
"StochasticSampledParameter",
"cvector_t",
"kvector_t",
]


from pyplusplus.file_writers.balanced_files import balanced_files_t
balanced_files_t.HEADER_EXT='.h'
balanced_files_t.SOURCE_EXT='.cpp'
from pyplusplus.file_writers.multiple_files import multiple_files_t
multiple_files_t.HEADER_EXT='.pypp.h'
multiple_files_t.SOURCE_EXT='.pypp.cpp'




# -----------------------------------------------------------------------------
# AdditionalRules
# -----------------------------------------------------------------------------
def ManualClassTunings(mb):
    mb.class_("Detector").member_functions("addAxis").exclude()
    #mb.class_("Instrument").member_functions("setDetectorParameters").exclude()
    #mb.class_("Simulation").member_functions("setDetectorParameters").exclude()
    #mb.class_("IFTDistribution2D").member_functions("transformToStarBasis").exclude()
    #mb.class_("FTDistribution2DCauchy").member_functions("transformToStarBasis").exclude()
    #
    shared_ptrs = mb.decls( lambda decl: decl.name.startswith( 'shared_ptr<' ) )
    shared_ptrs.disable_warnings( messages.W1040 )
    # BasicVector3D
    methods_to_exclude=[
        "phi", "theta", "cosTheta", "getPhi", "getTheta", "setPhi", "setTheta", "setR",
        "setMag", "perp", "perp2", "setPerp", "angle", "unit", "orthogonal",
        "rotated","rotatedX","rotatedY","rotatedZ"
    ]
    classes_to_exclude = ["BasicVector3D<std::complex<double> >","BasicVector3D<double>","BasicVector3D<int>"]
    builder_rules.ExcludeMemberFunctionsForClasses(mb, methods_to_exclude, classes_to_exclude)
    pass
    # Pure virtual should always be included
    mb.class_("IDetectorResolution").member_function("applyDetectorResolution").include()
    #
    cl = mb.class_( "Lattice" )
    cl.member_functions().exclude()
    cl.member_function("getBasisVectorA").include()
    cl.member_function("getBasisVectorB").include()
    cl.member_function("getBasisVectorC").include()
    cl.member_function("createTrigonalLattice").include()
    cl.member_function("createTrigonalLattice").call_policies = call_policies.return_value_policy(call_policies.return_by_value )
    cl.member_function("setSelectionRule").include()
    #
    cl = mb.class_("LatticeBasis")
    cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    cl.member_functions().exclude()
    cl.member_function("addParticle").include()
    #
    cl = mb.class_('RealParameterWrapper') # given class is only to teach pyplusplus to templates, but we do not need class itself to be visible in python, excluding it...
    cl.member_functions().exclude()
    cl.member_function("setValue").include()
    cl.member_function("getValue").include()
    cl.member_function("isNull").include()
    # 
    mb.free_function("GetOutputDataNdimensions").include()
    mb.free_function("GetOutputData").include()
    mb.free_function("GetOutputDataAxis").include()
    mb.free_function('GetOutputData').call_policies = call_policies.custom_call_policies("")
    mb.free_function('GetOutputDataAxis').call_policies = call_policies.custom_call_policies("")
    #
    cl = mb.class_("BasicVector3D<double>")
    cl.add_code("def( bp::self - bp::self )")
    cl.add_code("def( bp::self + bp::self )")
    cl.add_code("def( bp::other< double >() * bp::self )")
    cl.add_code("def( bp::self * bp::other< double >() )")
    cl.add_code("def( +bp::self )")
    cl.add_code("def( -bp::self )")
    cl.add_code("def( bp::self / bp::other< double >() )")
    cl.add_code("def( bp::self_ns::str( bp::self ) )")
    #
    cl = mb.class_( "IParameterized" )
    cl.member_function("registerParameter").include()
    cl.member_function("registerParameter").add_transformation( builder_rules.from_address_custom( 1 ) )
    #
    cl = mb.class_( "ISampleBuilder" )
    cl.member_functions().exclude()
    cl.member_function( "buildSample" ).include()
    cl.member_function( "buildSample" ).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )
    #
    cl = mb.class_( "MaterialManager" )
    cl.constructors().exclude()
    #
    cl = mb.class_("OutputData<double>")
    cl.add_code('def("__setitem__", &pyplusplus_setitem<OutputData<double >,int,double> )')
    #
    cl = mb.class_( "Particle" )
    cl.member_function( "createDiffuseParticleInfo" ).exclude()
    cl.member_function( "createDistributedParticles" ).exclude()
    #
    cl = mb.class_( "ParticleDecoration" )
    cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    #
    cl = mb.class_( "ParameterPool" )
    cl.member_function("registerParameter").add_transformation( builder_rules.from_address_custom( 1 ) )
    cl.member_function("getMatchedParameters").exclude()
    #
    mb.namespace( "Units" ).include()
    #
    cl = mb.class_( "Layer" )
    # including back methods which have been excluded by our pointer policy
    for fun in cl.member_functions():
        if fun.name == "setMaterial":fun.include()
    cl.constructors().include() # including back constructors with pointers
    #
    cl = mb.class_("Simulation")
    cl.member_function("setSampleBuilder").include()
    #
    cl = mb.class_( "ParticleCoreShell" )
    cl.member_functions().exclude()




# excluding specific member functions
def ManualExcludeMemberFunctions(mb):
    # with given name in function name
    to_exclude=['Iterator','iterator','DWBASimulation']
    to_exclude_exact=['createDiffuseParticleInfo','createDistributedParticles',
    'inverse','transformed','getNearestLatticeVectorCoordinates','getNearestReciprocalLatticeVectorCoordinates',
    'collectBraggAngles','getKVectorContainer',
    'begin','end','getBinOfAxis','addMask','getMask','setMask',
    ]
    for f in mb.member_functions():
        for x in to_exclude:
            if x in f.name: f.exclude()
        for x in to_exclude_exact:
            if x == f.name: f.exclude()
    pass


#------------------------------------------------------------------------------
# produces boost python code
#------------------------------------------------------------------------------
def MakePythonAPI(OutputTempDir):
    # getting paths
    include_dirs.append(sys.prefix +"/include/python"+ sys.version[:3])
    # looking for general headers
    proc = subprocess.Popen(["which g++"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    path = out.strip()
    if path.endswith("bin/g++"):
        include_dirs.append(path[:-7]+"include")
    else:
        exit("Can't find g++")
    # looking for gccxml
    proc = subprocess.Popen(["which gccxml"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    path = out.strip()
    if path.endswith("/gccxml"):
        mygccxml = path[:-7]
    else:
        exit("No gccxml!")
  
    print mygccxml

    #If the cache file cache_core.xml doesn't exist it gets created, otherwise it just gets loaded
    print "NOTE: If you update the source library code you need to manually delete the cache_core.xml file, or 'python codegenerator.py clean'"
    xml_cached_fc = parser.create_cached_source_fc( "PythonCoreList.h", "cache_core.xml" )
    #xml_cached_fc = parser.create_cached_source_fc( ["PythonCoreList.h","PythonCoreExposer.h"], "cache_core.xml" )
    mb = module_builder.module_builder_t( [xml_cached_fc], include_paths=include_dirs, gccxml_path=mygccxml, cflags="-m64")

    # -----------------
    # general rules
    # -----------------

    builder_rules.IncludeClasses(mb, include_classes)

    builder_rules.DefineGeneralRules(mb)

    builder_rules.ExcludeConstructorsArgPtr(mb)

    builder_rules.ExcludeMemberFunctionsArgPtr(mb)

    builder_rules.ManageNewReturnPolicy(mb)

    # -----------------
    # manual tuning
    # -----------------

    ManualExcludeMemberFunctions(mb)

    ManualClassTunings(mb) 

    # -----------------
    # default policies for what remained unchainged
    # -----------------

    #builder_rules.IncludePureVirtualMethods(mb, include_classes)

    builder_rules.DefaultReturnPolicy(mb)

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
    mb.build_code_creator( module_name=builder_rules.ModuleName)
    mb.code_creator.license = builder_rules.license
    
    mb.code_creator.user_defined_directories.append( os.path.abspath('./') )
    mb.split_module(OutputTempDir)


#------------------------------------------------------------------------------
# main()
#------------------------------------------------------------------------------
if __name__ == '__main__':
    PyCoreTempDir='output/PyCore'
    if not os.path.exists(PyCoreTempDir): os.makedirs(PyCoreTempDir)
    start_time = time.clock()
    MakePythonAPI(PyCoreTempDir)
    print '\nPythonCoreAPI source code was generated ( %f seconds ).' % (  ( time.clock() - start_time ) )
    print 'Run InstallPyCore.py to install generated code into BornAgain source tree'
    print 'Done'

