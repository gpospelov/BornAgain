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

from pyplusplus.function_transformers import transformers
from pygccxml import parser

import common


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
"Crystal",
"Detector",
"FTDistribution2DCauchy",
"FormFactorBox",
"FormFactorCone",
"FormFactorCylinder",
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
"ParameterPool",
"Particle",
"Particle",
"ParticleBuilder",
"ParticleDecoration",
"ParticleInfo",
"PositionParticleInfo",
"RealParameterWrapper",
"RotateY_3D",
"RotateZ_3D",
"Simulation",
"SimulationParameters",
"StochasticDoubleGaussian",
"StochasticDoubleGaussian",
"StochasticParameter<double>",
"cvector_t",
"kvector_t",
]


from pyplusplus.file_writers.balanced_files import balanced_files_t
balanced_files_t.HEADER_EXT='.h'
balanced_files_t.SOURCE_EXT='.cpp'
from pyplusplus.file_writers.multiple_files import multiple_files_t
multiple_files_t.HEADER_EXT='.pypp.h'
multiple_files_t.SOURCE_EXT='.pypp.cpp'


ModuleName = 'PythonInterface'


# Usefull links
# (nice code example)
# http://publicsvn.edmstudio.com/ogre/OgreAR/python/ogrear/generate_code.py  (nice code example)
# (about smart pointers registration)
# http://www.gamedev.net/topic/553076-py-automatically-register-boostshared_ptr-to-python/ 
# (smart pointers to be exported)
# http://pygccxml.svn.sourceforge.net/viewvc/pygccxml/pyplusplus_dev/unittests/data/smart_pointers_to_be_exported.hpp?revision=1837&view=markup

# --------------------------------------------------------------------------
# This is patched version of pyplusplus.function_transformers classes to
# pass address of ctype(double) into C++. The pointer is passed now in the 
# form of long unsigned, which correspond to 64 bit (before it was unsigned int)
# --------------------------------------------------------------------------
class from_address_custom_t(transformers.type_modifier_t):
    def __init__(self, function, arg_ref):
        modifier = lambda type_: declarations.FUNDAMENTAL_TYPES[ 'long unsigned int' ]
        print modifier
        transformers.type_modifier_t.__init__( self, function, arg_ref, modifier )
        if not transformers.is_ptr_or_array( self.arg.type ):
            raise ValueError( '%s\nin order to use "from_address_t" transformation, argument %s type must be a pointer or a array (got %s).' ) \
                  % ( function, self.arg_ref.name, arg.type)
    def __str__(self):
        return "from_address(%s)"%(self.arg.name)

def from_address_custom( *args, **keywd ):
    def creator( function ):
        return from_address_custom_t( function, *args, **keywd )
    return creator


# for classes with names from 'class_names' exclude methods from 'method_names'
def ExcludeMemberFunctionsForClasses(mb, method_names, class_names):
    # if class decl_string is present in class_names
    def ClassInList(cl):
        for name in class_names:
            if name in cl.decl_string: return True
        return False
    # method name is present in method_names
    def MethodInList(method):
        for name in method_names:
            if method.name == name: return True
        return False
    #
    for cl in mb.classes():
        if ClassInList(cl):
            #print "class in list",cl.decl_string, class_names
            for fun in cl.member_functions(allow_empty=True):
                if MethodInList(fun):
                    #print "method in list",fun.name, method_names
                    fun.exclude()


# -----------------------------------------------------------------------------
# AdditionalRules
# -----------------------------------------------------------------------------
def ManualClassTunings(mb):
    mb.class_("Detector").member_functions("addAxis").exclude()
    mb.class_("Instrument").member_functions("setDetectorParameters").exclude()
    mb.class_("Simulation").member_functions("setDetectorParameters").exclude()
    mb.class_("IFTDistribution2D").member_functions("transformToStarBasis").exclude()
    mb.class_("FTDistribution2DCauchy").member_functions("transformToStarBasis").exclude()
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
    ExcludeMemberFunctionsForClasses(mb, methods_to_exclude, classes_to_exclude)
    pass


# include list of defined classes
def IncludeClasses(mb):
    # check if classes defined in list are presented in module builder
    not_found_classes=[]
    for name in include_classes:
        isFound = False
        for cl in mb.classes():
            if name == cl.name or name == cl.alias: isFound = True
        if not isFound: not_found_classes.append(name)
    if len(not_found_classes): 
        print "Error! Can't find classes with requested names ", not_found_classes
        exit()
    mb.classes( lambda cls: cls.name in include_classes ).include()



# excluding specific member functions
def ManualExcludeMemberFunctions(mb):
    # with given name in function name
    to_exclude=['Iterator','iterator','DWBASimulation']
    to_exclude_exact=['evaluate','evaluate_for_q','createDiffuseParticleInfo','createDistributedParticles',
    'inverse','transformed','getNearestLatticeVectorCoordinates','getNearestReciprocalLatticeVectorCoordinates',
    'coordinateSelected','collectBraggAngles','getKVectorContainer','getInterferenceFunctions',
    'begin','end','getBinOfAxis','addMask','getMask','setMask',
    ]
    for f in mb.member_functions():
        for x in to_exclude:
            if x in f.name: f.exclude()
        for x in to_exclude_exact:
            if x == f.name: f.exclude()
    pass


# general rules
def DefineGeneralRules(mb):
    mb.classes().always_expose_using_scope = True
    #mb.always_expose_using_scope = True
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
def ManageNewReturnPolicy(mb):
    for cl in mb.classes():
        cl.member_functions('instance', allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
        cl.member_functions('clone', allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )
        cl.member_functions( lambda x: x.name.startswith('create'), allow_empty=True ).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )


# set the default return policies (for references/pointers) on classes if it wasn't already been done for
def DefaultReturnPolicy(mb):
    mem_funs = mb.calldefs()
    for mem_fun in mem_funs:
        if mem_fun.call_policies:
            continue
        if not mem_fun.call_policies and (declarations.is_reference(mem_fun.return_type) or declarations.is_pointer(mem_fun.return_type) ):
            mem_fun.call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )



#------------------------------------------------------------------------------
#
# produces boost python code
#
#------------------------------------------------------------------------------
def MakePythonAPI(OutputTempDir):


    #---------------------------------------------------------------
    # getting paths
    #---------------------------------------------------------------
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
    print "NOTE: If you update the source library code you need to manually delete the cache_core.xml file, or 'make -f Makefile.am clean'"
  
    xml_cached_fc = parser.create_cached_source_fc( "PythonCoreList.h", "cache_core.xml" )
    #mb = module_builder.module_builder_t( [xml_cached_fc], include_paths=include_dirs, gccxml_path=mygccxml)
    mb = module_builder.module_builder_t( [xml_cached_fc], include_paths=include_dirs, gccxml_path=mygccxml, cflags="-m64")


    IncludeClasses(mb)

    DefineGeneralRules(mb)

    common.ExcludeConstructorsArgPtr(mb)

    common.ExcludeMemberFunctionsArgPtr(mb)

    # difficult to expose functions
    ManualExcludeMemberFunctions(mb)

    # policies for clone, create, singleton methods
    ManageNewReturnPolicy(mb)

    # all hand made rules for classes goes here
    ManualClassTunings(mb) 

    # default return policy which should be called last
    DefaultReturnPolicy(mb)

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
    mb.build_code_creator( module_name=ModuleName)
    mb.code_creator.license = common.license
    
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
    print 'Done. PythonCoreAPI source code was updated( %f seconds ).' % (  ( time.clock() - start_time ) )

