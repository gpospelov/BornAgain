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


import builder_utils


include_dirs = [
    '../../Core/Samples/inc',
    '../../Core/FormFactors/inc',
    '../../Core/Algorithms/inc',
    '../../Core/Tools/inc',
    '../../Core/PythonAPI/inc',
    '../../Core/Geometry/inc',
]

include_classes = [
    "AxisDouble",
    "AxisBin",
    "BasicVector3D<double>",
    "BasicVector3D<std::complex<double> >",
    "Beam",
    "Bin1D",
    "Bin1DCVector",
    "Crystal",
    "Detector",
    "FTDistribution2DCauchy",
    "FormFactorAnisoPyramid",
    "FormFactorBox",
    "FormFactorCone",
    "FormFactorCone6",
    "FormFactorCuboctahedron",
    "FormFactorCylinder",
    "FormFactorCrystal",
    "FormFactorDecoratorDebyeWaller",
    "FormFactorEllipsoidalCylinder",
    "FormFactorFullSphere",
    "FormFactorFullSpheroid",
    "FormFactorGauss",
    "FormFactorHemiEllipsoid",
    "FormFactorLorentz",
    "FormFactorParallelepiped",
    "FormFactorPrism3",
    "FormFactorPrism6",
    "FormFactorPyramid",
    "FormFactorRipple1",
    "FormFactorRipple2",
    "FormFactorSphere",
    "FormFactorSphereGaussianRadius",
    "FormFactorSphereUniformRadius",
    "FormFactorSpheroid",
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
    "IFormFactorDecorator",
    "IInterferenceFunction",
    "IMaterial",
    "IObserver",
    "IObservable",
    "IParameterized",
    "IResolutionFunction2D",
    "ISample",
    "ISampleBuilder",
    #"SampleBuilder_t",
    #"ISampleVisitor",
    "ISelectionRule",
    "Transform3D",
    "Instrument",
    "InterferenceFunction1DParaCrystal",
    "InterferenceFunction2DLattice",
    "InterferenceFunction2DParaCrystal",
    "InterferenceFunctionNone",
    "Lattice",
    "Lattice2DIFParameters",
    "LatticeBasis",
    "Layer",
    #"LayerDecorator",
    "LayerInterface",
    "LayerRoughness",
    "MaterialManager",
    "MesoCrystal",
    "MultiLayer",
    "OutputData<double>",
    "OutputDataIOFactory",
    "ParameterPool",
    "Particle",
    "ParticleCoreShell",
    "ParticleBuilder",
    "ParticleDecoration",
    "ParticleInfo",
    "PositionParticleInfo",
    "RealParameterWrapper",
    "ResolutionFunction2DSimple",
    "Simulation",
    "SimulationParameters",
    "SimpleSelectionRule",
    "StochasticDoubleGate",
    "StochasticDoubleGaussian",
    "StochasticParameter<double>",
    "StochasticSampledParameter",
    "ThreadInfo",
    "cvector_t",
    "kvector_t",
]


# -----------------------------------------------------------------------------
# AdditionalRules
# -----------------------------------------------------------------------------
def ManualClassTunings(mb):
    mb.class_("AxisDouble").member_function("clone").exclude()
    mb.class_("AxisDouble").member_functions("createDoubleBinSize").exclude()

    mb.class_("Detector").member_functions("addAxis").exclude()
    #
    shared_ptrs = mb.decls(lambda decl: decl.name.startswith('shared_ptr<' ))
    shared_ptrs.disable_warnings(messages.W1040)
    # ISample
    cl = mb.class_('ISample') 
    cl.member_function("accept").include()
    cl.member_function("printSampleTree").include()
    
    # ICompositeSample
    cl = mb.class_('ICompositeSample')
    for f in cl.member_functions():
        if "shallow" in f.name:
            f.exclude()
    
    # BasicVector3D
    methods_to_exclude=[
        "phi", "theta", "cosTheta", "getPhi", "getTheta", "setPhi", "setTheta", "setR",
        "setMag", "perp", "perp2", "setPerp", "angle", "unit", "orthogonal",
        "rotated", "rotatedX", "rotatedY", "rotatedZ", "cross", "dot"
    ]
    classes_to_exclude = ["BasicVector3D<std::complex<double> >", "BasicVector3D<double>", "BasicVector3D<int>"]
    builder_utils.ExcludeMemberFunctionsForClasses(mb, methods_to_exclude, classes_to_exclude)
    # Pure virtual should always be included
    mb.class_("IDetectorResolution").member_function("applyDetectorResolution").include()
    #
    cl = mb.class_("Lattice")
    cl.member_functions().exclude()
    cl.member_function("getBasisVectorA").include()
    cl.member_function("getBasisVectorB").include()
    cl.member_function("getBasisVectorC").include()
    cl.member_function("createTrigonalLattice").include()
    cl.member_function("createTrigonalLattice").call_policies = call_policies.return_value_policy(call_policies.return_by_value)
    cl.member_function("setSelectionRule").include()
    #
    cl = mb.class_("LatticeBasis")
    cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    cl.member_functions().exclude()
    cl.member_function("addParticle").include()
    #
    cl = mb.class_('RealParameterWrapper') 
    cl.member_functions().exclude()
    cl.member_function("setValue").include()
    cl.member_function("getValue").include()
    cl.member_function("isNull").include()
    # 
    #mb.free_function("GetOutputDataNdimensions").include()
    #mb.free_function("GetOutputData").include()
    #mb.free_function("GetPolarizedOutputDataComponent").include()
    #mb.free_function("GetOutputDataAxis").include()
    #mb.free_function('GetOutputData').call_policies = call_policies.custom_call_policies("")
    #mb.free_function('GetPolarizedOutputDataComponent').call_policies = call_policies.custom_call_policies("")
    #mb.free_function('GetOutputDataAxis').call_policies = call_policies.custom_call_policies("")
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
    cl = mb.class_("IParameterized")
    cl.member_function("registerParameter").include()
    cl.member_function("registerParameter").add_transformation( builder_utils.from_address_custom( 1 ) )
    #
    cl = mb.class_("ISampleBuilder")
    #cl = mb.class_("SampleBuilder_t")
    cl.member_functions().exclude()
    cl.member_function("buildSample").include()
    cl.member_function("buildSample").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    #
    cl = mb.class_("IClusteredParticles")
    cl.member_function("setAmbientMaterial").include()
    #
    cl = mb.class_("IObserver")
    cl.member_function("update").include()

    cl = mb.class_("MaterialManager")
    cl.constructors().exclude()
    #
    cl = mb.class_("OutputData<double>")
    cl.add_code('def("__setitem__", &pyplusplus_setitem<OutputData<double >,int,double> )')  # [] operator for OutputData
    cl.member_function("getArray").call_policies = call_policies.custom_call_policies("")
    #cl.member_function("getArray").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    fun = cl.member_functions("getAxis").call_policies = call_policies.return_internal_reference()

    #
    cl = mb.class_("Particle")
    cl.member_function("createDiffuseParticleInfo").exclude()
    cl.member_function("createDistributedParticles").exclude()
    for cls in cl.constructors():
        if "( ::Particle::* )( ::IMaterial const *,::IFormFactor const & )" in cls.decl_string:
            cls.include()
        if "( ::Particle::* )( ::IMaterial const *,::IFormFactor const &,::Geometry::Transform3D const & )" in cls.decl_string:
            cls.include()

    #
    cl = mb.class_("ParticleDecoration")
    cl.constructors(lambda decl: bool(decl.arguments)).exclude()  # exclude non-default constructors
    #
    cl = mb.class_("ParameterPool")
    cl.member_function("registerParameter").add_transformation(builder_utils.from_address_custom(1))
    cl.member_function("getMatchedParameters").exclude()
    #
    mb.namespace("Units").include()
    #
    cl = mb.class_("Layer")
    # including back methods which have been excluded by our pointer policy
    for fun in cl.member_functions():
        if fun.name == "setMaterial":
            fun.include()
    for fun in cl.member_functions():
        if "void ( ::Layer::* )( ::IDecoration * )" in fun.decl_string:
            fun.exclude()
    cl.constructors().include()  # including back constructors with pointers
    #
    cl = mb.class_("Simulation")
    cl.member_function("setSampleBuilder").include()
    cl.member_function("getOutputData").exclude()
    cl.member_function("getIntensityData").call_policies = \
        call_policies.return_value_policy(call_policies.manage_new_object)
    cl.member_function("getPolarizedIntensityData").call_policies = \
        call_policies.return_value_policy(call_policies.manage_new_object)
    #
    mb.class_("Transform3D").member_function("createIdentity").call_policies = \
        call_policies.return_value_policy(call_policies.return_by_value)
    mb.class_("Transform3D").member_function("createRotateX").call_policies = \
        call_policies.return_value_policy(call_policies.return_by_value)
    mb.class_("Transform3D").member_function("createRotateY").call_policies = \
        call_policies.return_value_policy(call_policies.return_by_value)
    mb.class_("Transform3D").member_function("createRotateZ").call_policies = \
        call_policies.return_value_policy(call_policies.return_by_value)
    #
    cl = mb.class_("ParticleCoreShell")
    cl.member_functions().exclude()
    #
    cl = mb.class_("MesoCrystal")
    cl.member_functions().exclude()
    #
    mb.namespace("MathFunctions").free_function("GenerateNormalRandom").include()
    #
    mb.namespace("BornAgain").free_function("GetMajorVersionNumber").include()
    mb.namespace("BornAgain").free_function("GetMinorVersionNumber").include()
    mb.namespace("BornAgain").free_function("GetPatchVersionNumber").include()
    mb.namespace("BornAgain").free_function("GetVersionNumber").include()
    mb.namespace("BornAgain").free_function("GetName").include()


# excluding specific member functions
def ManualExcludeMemberFunctions(mb):
    # with given name in function name
    to_exclude=['Iterator', 'iterator', 'DWBASimulation']
    to_exclude_exact=['createDiffuseParticleInfo', 'createDistributedParticles',
        'inverse', 'transformed', 'getNearestLatticeVectorCoordinates', 'getNearestReciprocalLatticeVectorCoordinates',
        'collectBraggAngles', 'getKVectorContainer',
        'begin', 'end', 'getBinOfAxis', 'addMask', 'getMask', 'setMask',
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
    print "Generating PythonAPI for libBornAgainCore."
    # getting paths
    include_dirs.append( builder_utils.get_python_path() )
    include_dirs.append( builder_utils.get_gcc_path() )
    mygccxml = builder_utils.get_gccxml_path()

    #If the cache file cache_core.xml doesn't exist it gets created, otherwise it just gets loaded
    print """
        NOTE: If you update the source library code you need to manually delete the cache_core.xml file,
        or run 'python codegenerator.py clean'
        """
    xml_cached_fc = parser.create_cached_source_fc("PythonCoreList.h", "cache_core.xml")
    #xml_cached_fc = parser.create_cached_source_fc( ["PythonCoreList.h","PythonCoreExposer.h"], "cache_core.xml" )
    #mb = module_builder.module_builder_t( [xml_cached_fc], include_paths=include_dirs, gccxml_path=mygccxml, cflags="-m64 -msse -msse2 -fno-strict-aliasing -msse3")
    mb = module_builder.module_builder_t([xml_cached_fc], include_paths=include_dirs, gccxml_path=mygccxml,
                                         cflags="-m64 -DGCCXML_SKIP_THIS -DBORNAGAIN_PYTHON")

    # -----------------
    # general rules
    # -----------------

    #for x in mb.classes():
        #if "SampleBuilder" in x.name:
            #print "XXX",x.name

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
    # default policies for what remained unchanged
    # -----------------

    builder_utils.IncludePureVirtualMethods(mb, include_classes)

    builder_utils.DefaultReturnPolicy(mb)

    # disabling some warnings
    messages.disable(
        messages.W1020,  # Warnings 1020 - 1031 are all about why Py++ generates wrapper for class X
        messages.W1021,
        messages.W1022,
        messages.W1023,
        messages.W1024,
        messages.W1025,
        messages.W1026,
        messages.W1027,
        messages.W1028,
        messages.W1029,
        messages.W1030,
        messages.W1031,
        #messages.W1035,
        #messages.W1040,
        #messages.W1038,
        #messages.W1041,
        messages.W1036,  # pointer to Python immutable member
        #messages.W1033,  # unnamed variables
        #messages.W1018,  # expose unnamed classes
        #messages.W1049,  # returns reference to local variable
        #messages.W1014,  # unsupported '=' operator
    )

    # ---------------------------------------------------------
    # generating output
    # ---------------------------------------------------------
    mb.build_code_creator( module_name=builder_utils.ModuleName)
    mb.code_creator.license = builder_utils.license
    
    mb.code_creator.user_defined_directories.append(os.path.abspath('./'))
    mb.split_module(OutputTempDir)


if __name__ == '__main__':
    tempDir = 'output/PyCore'
    if not os.path.exists(tempDir): os.makedirs(tempDir)
    start_time = time.clock()
    MakePythonAPI(tempDir)
    print '\nPythonCoreAPI source code was generated ( %f seconds ).' % ((time.clock() - start_time))
    print 'Run InstallPyCore.py to install generated code into BornAgain source tree'
    print 'Done'

