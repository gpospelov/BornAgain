# BornAgain Core library
# settings for Python API generation by codegenerator.py

from pyplusplus.module_builder import call_policies
from pyplusplus import messages

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


lib_name = 'libBornAgainCore'

temp_dir    = 'output/PyCore'
install_inc = '../../Core/PythonAPI/inc'
install_src = '../../Core/PythonAPI/src'

master_include = "PythonCoreList.h"
cache_filename = "cache_core.xml"
special_flags = "-DBORNAGAIN_PYTHON"

with_pure_virtual = True
with_Numpy = True
with_converter = True


include_dirs = [
    '../../Core/Samples/inc',
    '../../Core/FormFactors/inc',
    '../../Core/Algorithms/inc',
    '../../Core/Tools/inc',
    '../../Core/PythonAPI/inc',
    '../../Core/Geometry/inc',
    '../../Core/InputOutput',
]

include_classes = [
    "AttLimits",
    "FixedBinAxis",
    "VariableBinAxis",
    "ConstKBinAxis",
    "CustomBinAxis",
    "BasicVector3D<double>",
    "BasicVector3D<std::complex<double> >",
    "Beam",
    "Bin1D",
    "Bin1DCVector",
    "Crystal",
    "DistributionGate",
    "DistributionLorentz",
    "DistributionGaussian",
    "DistributionLogNormal",
    "DistributionCosine",
    "FTDistribution1DCauchy",
    "FTDistribution1DGauss",
    "FTDistribution1DGate",
    "FTDistribution1DTriangle",
    "FTDistribution1DCosine",
    "FTDistribution1DVoigt",
    "FTDistribution2DCauchy",
    "FTDistribution2DGauss",
    "FTDistribution2DGate",
    "FTDistribution2DCone",
    "FTDistribution2DVoigt",
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
    "FormFactorPrism3",
    "FormFactorPrism6",
    "FormFactorPyramid",
    "FormFactorRipple1",
    "FormFactorRipple2",
    "FormFactorSphereGaussianRadius",
    "FormFactorSphereLogNormalRadius",
    "FormFactorSphereUniformRadius",
    "FormFactorTetrahedron",
    "FormFactorTrivial",
    "FormFactorTruncatedCube",
    "FormFactorTruncatedSphere",
    "FormFactorTruncatedSpheroid",
    "FormFactorWeighted",
    "GISASSimulation",
    "HomogeneousMaterial",
    "HomogeneousMagneticMaterial",
    "IAbstractParticle",
    "IAxis",
    "ICloneable",
    "IClusteredParticles",
    "ICompositeSample",
    "IDetector2D",
    "ILayout",
    "IDetectorResolution",
    "IDistribution1D",
    "IFTDistribution1D",
    "IFTDistribution2D",
    "IFormFactor",
    "IFormFactorBorn",
    "IFormFactorDecorator",
    "IInterferenceFunction",
    "IHistogram",
    "Histogram1D",
    "Histogram2D",
    "IMaterial",
    "IntensityDataFunctions",
    "IObserver",
    "IObservable",
    "IParameterized",
    "IParticle",
    "IResolutionFunction2D",
    "IRotation",
    "ISample",
    "ISampleBuilder",
    "ISelectionRule",
    "IsGISAXSDetector",
    "Instrument",
    "InterferenceFunction1DLattice",
    "InterferenceFunctionRadialParaCrystal",
    "InterferenceFunction2DLattice",
    "InterferenceFunction2DParaCrystal",
    "InterferenceFunctionNone",
    "Lattice",
    "Lattice1DIFParameters",
    "Lattice2DIFParameters",
    "Layer",
    "LayerInterface",
    "LayerRoughness",
    "MesoCrystal",
    "MultiLayer",
    "OffSpecSimulation",
    "OutputData<double>",
    "IntensityDataIOFactory",
    "ParameterDistribution",
    "ParameterPool",
    "Particle",
    "ParticleComposition",
    "ParticleDistribution",
    "ParticleCoreShell",
    "ParticleLayout",
    "RealParameterWrapper",
    "RectangularDetector",
    "ResolutionFunction2DGaussian",
    "RotationX",
    "RotationY",
    "RotationZ",
    "RotationEuler",
    "SpecularSimulation",
    "SphericalDetector",
    "Simulation",
    "SimulationParameters",
    "SimpleSelectionRule",
    "ThreadInfo",
    "cvector_t",
    "kvector_t",
    "IShape2D",
    "Line",
    "VerticalLine",
    "HorizontalLine",
    "Ellipse",
    "Rectangle",
    "Polygon",
    "WavevectorInfo"
]


exclude_patterns = []


# -----------------------------------------------------------------------------
# AdditionalRules
# -----------------------------------------------------------------------------
def ManualClassTunings(mb):
    #mb.class_("AxisDouble").member_function("clone").exclude()
    #mb.class_("AxisDouble").member_functions("createDoubleBinSize").exclude()

    axis_operators = mb.free_operators( lambda decl: 'IAxis' in decl.decl_string )
    axis_operators.include()

    # shared ptrs
    shared_ptrs = mb.decls(lambda decl: decl.name.startswith('shared_ptr<' ))
    shared_ptrs.disable_warnings(messages.W1040)

    # IDetector2D
    cl = mb.class_('IDetector2D')
    cl.member_functions("addAxis").exclude()
    cl.member_functions("clone").exclude()

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
        "phi", "theta", "cosTheta", "sin2Theta", "getPhi", "getTheta", "setPhi", "setTheta", "setR",
        "setMag", "perp", "perp2", "setPerp", "angle", "unit", "orthogonal", "rotated", "rotatedX",
        "rotatedY", "rotatedZ", "cross", "dot", "normalize"
    ]
    classes_to_exclude = ["BasicVector3D<std::complex<double> >", "BasicVector3D<double>", "BasicVector3D<int>"]
    utils_build.ExcludeMemberFunctionsForClasses(mb, methods_to_exclude, classes_to_exclude)
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
    cl = mb.class_("ParticleComposition")
    cl.constructors( lambda decl: bool( decl.arguments ) ).exclude() # exclude non-default constructors
    cl.member_functions().exclude()
    cl.member_function("addParticles").include()
    cl.member_functions("addParticle").include()
    #
    cl = mb.class_('RealParameterWrapper')
    cl.member_functions().exclude()
    cl.member_function("setValue").include()
    cl.member_function("getValue").include()
    cl.member_function("isNull").include()
    #
    funs = mb.free_functions()
    for ff in funs:
        if 'SetLevel' in ff.name:
            ff.alias = 'SetMessageLevel'
            ff.include()
        if 'CreateProduct' in ff.name:
            ff.include()
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
    cl = mb.class_("InterferenceFunction2DParaCrystal")
    cl.member_function("getProbabilityDistributions").exclude()
    #
    cl = mb.class_("IParameterized")
    cl.member_function("registerParameter").include()
    cl.member_function("registerParameter").add_transformation( utils_build.from_address_custom( 1 ) )
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
    cl = mb.class_("IDistribution1D")
    for fun in cl.member_functions():
        print fun.name
        if "generateSamples" in fun.name:
            fun.exclude()
    #
    # cl = mb.class_("IObserver")
    # cl.member_function("update").include()

    #cl = mb.class_("MaterialManager")
    #cl.constructors().exclude()
    #
    cl = mb.class_("OutputData<double>")
    cl.add_code('def("__setitem__", &pyplusplus_setitem<OutputData<double >,int,double> )')  # [] operator for OutputData
    cl.member_function("getArray").call_policies = call_policies.custom_call_policies("")
    #cl.member_function("getArray").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    fun = cl.member_functions("getAxis").call_policies = call_policies.return_internal_reference()

    #
    cl = mb.class_("Particle")
    for cls in cl.constructors():
        if "( ::Particle::* )( ::IMaterial const *,::IFormFactor const & )" in cls.decl_string:
            cls.include()
        if "( ::Particle::* )( ::IMaterial const *,::IFormFactor const &,::IRotation const & )" in cls.decl_string:
            cls.include()

    #
    cl = mb.class_("ParticleDistribution")
    cl.member_function("generateParticleInfos").exclude()
    #
    cl = mb.class_("ParticleLayout")
    #cl.constructors(lambda decl: bool(decl.arguments)).exclude()  # exclude non-default constructors
    #
    cl = mb.class_("ParameterDistribution")
    cl.member_function("generateSamples").exclude()
    cl.member_function("getLinkedParameterNames").exclude()
    #
    cl = mb.class_("ParameterPool")
    cl.member_function("registerParameter").add_transformation(utils_build.from_address_custom(1))
    # cl.member_function("getMatchedParameters").exclude()
    # cl.member_function("getParameterNames").exclude()
    #
    mb.namespace("Units").include()
    #
    cl = mb.class_("Layer")
    # including back methods which have been excluded by our pointer policy
    for fun in cl.member_functions():
        if fun.name == "setMaterial":
            fun.include()
    for fun in cl.member_functions():
        if "void ( ::Layer::* )( ::ILayout * )" in fun.decl_string:
            fun.exclude()
    cl.constructors().include()  # including back constructors with pointers
    #
    cl = mb.class_("Simulation")
    cl.member_function("setSampleBuilder").include()
    # cl.member_function("getIntensityData").call_policies = \
    #     call_policies.return_value_policy(call_policies.manage_new_object)
    #
    cl = mb.class_("GISASSimulation")
    cl.member_function("getOutputData").exclude()
    cl.member_function("getIntensityData").call_policies = \
        call_policies.return_value_policy(call_policies.manage_new_object)
    cl.member_function("getDetectorIntensity").call_policies = \
        call_policies.return_value_policy(call_policies.manage_new_object)
    #
    cl = mb.class_("SpecularSimulation")
    cl.member_function("setSampleBuilder").include()
    # cl.member_function("getEvanescentWaveIntensity").call_policies = \
    # call_policies.return_value_policy(call_policies.manage_new_object)
    #
    cl = mb.class_("OffSpecSimulation")
    cl.member_function("getOutputData").exclude()
    cl.member_function("getIntensityData").call_policies = \
        call_policies.return_value_policy(call_policies.manage_new_object)
    cl.member_function("getDetectorIntensity").call_policies = \
        call_policies.return_value_policy(call_policies.manage_new_object)
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

    cl = mb.class_("IHistogram")
    cl.member_function("getArray").call_policies = call_policies.custom_call_policies("")
    cl.member_function("getXaxis").call_policies = call_policies.return_internal_reference()
    cl.member_function("getYaxis").call_policies = call_policies.return_internal_reference()
    cl.member_function("createOutputData").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    cl.member_function("createRelativeDifferenceHistogram").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)

    cl = mb.class_("Histogram1D")
    cl.member_function("getBinCenters").exclude()
    cl.member_function("getBinValues").exclude()
    cl.member_function("getBinErrors").exclude()
    cl.member_function("getBinCentersNumpy").call_policies = call_policies.custom_call_policies("")
    cl.member_function("getBinValuesNumpy").call_policies = call_policies.custom_call_policies("")
    cl.member_function("getBinErrorsNumpy").call_policies = call_policies.custom_call_policies("")
    cl.member_function("getBinCentersNumpy").alias = "getBinCenters"
    cl.member_function("getBinValuesNumpy").alias = "getBinValues"
    cl.member_function("getBinErrorsNumpy").alias = "getBinErrors"

    #
    cl = mb.class_("Histogram2D")
    for fun in cl.member_functions():
        if "projection" in fun.name:
            fun.call_policies = call_policies.return_value_policy(call_policies.manage_new_object)


    cl = mb.class_("IntensityDataIOFactory")

    cl.member_function("readOutputData").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    # cl.member_function("readHistogram").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)
    cl.member_function("readIntensityData").call_policies = call_policies.return_value_policy(call_policies.manage_new_object)

    cl = mb.class_("IDetector2D")
    cl.member_function("setDetectorParameters").exclude()


# excluding specific member functions
def ManualExcludeMemberFunctions(mb):
    # with given name in function name
    to_exclude=['Iterator', 'iterator', 'DWBASimulation']
    to_exclude_exact=['inverse', 'transformed',
        'getNearestLatticeVectorCoordinates',
        'getNearestReciprocalLatticeVectorCoordinates', 'collectBraggAngles',
        'getKVectorContainer', 'begin', 'end'
    ]
    for f in mb.member_functions():
        for x in to_exclude:
            if x in f.name: f.exclude()
        for x in to_exclude_exact:
            if x == f.name: f.exclude()
