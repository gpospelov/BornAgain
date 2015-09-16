# common rules and utilities for boost python code generation

import os
import sys
import subprocess
import platform

from pygccxml import declarations
from pygccxml import parser

from pyplusplus import module_builder
from pyplusplus.module_builder import call_policies
from pyplusplus import messages
from pyplusplus.function_transformers import transformers
from pyplusplus.file_writers.balanced_files import balanced_files_t
from pyplusplus.file_writers.multiple_files import multiple_files_t

import utils_docstring

balanced_files_t.HEADER_EXT = '.h'
balanced_files_t.SOURCE_EXT = '.cpp'
multiple_files_t.HEADER_EXT = '.pypp.h'
multiple_files_t.SOURCE_EXT = '.pypp.cpp'


incref_code = \
"""
if( !this->m_pyobj) {
    this->m_pyobj = boost::python::detail::wrapper_base_::get_owner(*this);
    Py_INCREF(this->m_pyobj);
}
"""


extractor = utils_docstring.DoxygenDocExtractor()

def my_doc_extractor( decl ):
    # print "========================"
    # print decl.name
    # print decl.location.file_name + str(decl.location.line)
    # print "-----------"
    # print extractor(decl)
    # print "-----------"
    return extractor(decl)

def ExcludeConstructorsArgPtr(mb):
    '''Excludes constructors which have pointers in argument list.'''
    for cl in mb.classes():
        for ctor in cl.constructors(allow_empty=True):
            for arg in ctor.arguments:
                if declarations.type_traits.is_pointer(arg.type):
                    ctor.exclude()


def ExcludeMemberFunctionsArgPtr(mb):
    '''Excludes member functions if they have pointers in argument list.'''
    for cl in mb.classes():
        for fun in cl.member_functions(allow_empty=True):
            if any( declarations.type_traits.is_pointer(arg.type)
                    for arg in fun.arguments ):
                fun.exclude();


def IncludePureVirtualMethods(mb, include_classes):
    '''Includes pure virtual methods.'''
    for cl in mb.classes():
        if not any( name == cl.name or name == cl.alias
                    for name in include_classes ):
            continue
        query = declarations.virtuality_type_matcher_t(
            declarations.VIRTUALITY_TYPES.PURE_VIRTUAL )
        fun = cl.member_functions( query, allow_empty=True )
        for f in fun:
            f.include()


def IncludeClasses(mb, include_classes):
    '''Includes list of defined classes.'''
    # check if classes defined in list are presented in module builder
    not_found_classes=[]
    for name in include_classes:
        if not any( name == cl.name or name == cl.alias
                    for cl in mb.classes() ):
            not_found_classes.append(name)
    if len(not_found_classes):
        print( "Error! Can't find classes with requested names {0}".format(not_found_classes) )
        exit()
    mb.classes( lambda cls: cls.name in include_classes ).include()


def ExcludeMemberFunctionsForClasses(mb, method_names, class_names):
    '''If class name in 'class_names' then exclude 'method_names'.'''
    for cl in mb.classes():
        if any( name in cl.decl_string for name in class_names ):
            for fun in cl.member_functions(allow_empty=True):
                if any( fun.name == name for name in method_names ):
                    fun.exclude()


def DefineGeneralRules(mb):
    '''General rules.'''
    mb.classes().always_expose_using_scope = True
    #mb.always_expose_using_scope = True
    # Generated code containing errors will not compile on
    mem_funs = mb.calldefs ()
    mem_funs.create_with_signature = True
    # Exclude protected and private that are not pure virtual
    # (we still have to expose pure virtual functions to have them
    #  overriden in the wrapper)
    query = declarations.access_type_matcher_t( 'private' ) & \
            ~declarations.virtuality_type_matcher_t(
                declarations.VIRTUALITY_TYPES.PURE_VIRTUAL )
    mb.global_ns.calldefs( query, allow_empty=True ).exclude()
    query = declarations.access_type_matcher_t( 'protected' ) & \
            ~declarations.virtuality_type_matcher_t(
                declarations.VIRTUALITY_TYPES.PURE_VIRTUAL )
    mb.global_ns.calldefs( query, allow_empty=True ).exclude()
    # excluding generation of methods for implicit conversion
    mb.constructors().allow_implicit_conversion = False


def ManageNewReturnPolicy(mb):
    '''Returns policy for singletons, clone and create methods.'''
    for cl in mb.classes():
        cl.member_functions('instance',
                            allow_empty=True).call_policies = \
            call_policies.return_value_policy( call_policies.reference_existing_object )
        cl.member_functions('clone',
                            allow_empty=True).call_policies = \
            call_policies.return_value_policy( call_policies.manage_new_object )
        cl.member_functions( lambda x: x.name.startswith('create'),
                             allow_empty=True ).call_policies = \
            call_policies.return_value_policy( call_policies.manage_new_object )


def ManageTransferOwnership(mb):
    '''Increases reference count during transfer of ownership.'''
    for clone_fun in mb.member_functions('clone'):
        cl = clone_fun.parent
        cl.add_wrapper_code('PyObject* m_pyobj;')
        cl.set_constructors_body('m_pyobj = 0;')
        cl.member_functions('transferToCPP', allow_empty=True).add_override_precall_code(incref_code)
        cl.member_functions('transferToCPP', allow_empty=True).add_default_precall_code(incref_code)
        cl.held_type = 'std::auto_ptr< %s >' % cl.wrapper_alias


def DefaultReturnPolicy(mb):
    '''Sets the default return policies (for references/pointers) on classes
       if it wasn't already been done for. Should be called last.'''
    mem_funs = mb.calldefs()
    for mem_fun in mem_funs:
        if mem_fun.call_policies:
            continue
        if ( not mem_fun.call_policies and
             (declarations.is_reference(mem_fun.return_type) or
              declarations.is_pointer(mem_fun.return_type) ) ):
            mem_fun.call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )


def InjectGetStringCustomCode(cls, method_name):
    '''Injects custom wrapper for getString to deal with Windows and MSVC2012'''
    cls.member_function(method_name).exclude()
    wrapper_code = '''
    virtual ::std::string {1}(  ) const  {{
        if( bp::override func_{1} = this->get_override( \"{1}\" ) )
            return boost::python::call<std::string>(func_{1}(  ));
        else{{
            return this->{0}::{1}(  );
        }}
    }}

    ::std::string default_{1}(  ) const  {{
        return {0}::{1}( );
    }}
    '''
    wrapper_code = wrapper_code.format(cls.name, method_name)
    cls.add_wrapper_code(wrapper_code)
    registration_code = """
            def(
                \"{1}\"
                , (::std::string ( ::{0}::*)(  ) const)(&::{0}::{1})
                , (::std::string ( {0}_wrapper::*)(  ) const)(&{0}_wrapper::default_{1}) )
    """
    registration_code = registration_code.format(cls.name, method_name)
    cls.add_code(registration_code)




class from_address_custom_t(transformers.type_modifier_t):

    '''This is a patched version of pyplusplus.function_transformers classes to
pass address of ctype(double) into C++. The pointer is passed now in the form
of long unsigned, which correspond to 64 bit (before it was unsigned int)'''

    def __init__(self, function, arg_ref):
        modifier = lambda type_: declarations.FUNDAMENTAL_TYPES[
            'long unsigned int' ]
        transformers.type_modifier_t.__init__(
            self, function, arg_ref, modifier )
        if not transformers.is_ptr_or_array( self.arg.type ):
            raise ValueError( '%s\nin order to use "from_address_t" transformation, argument %s type must be a pointer or a array (got %s).' %
                              ( function, self.arg_ref.name, self.arg.type) )

    def __str__(self):
        return "from_address(%s)"%(self.arg.name)


def from_address_custom( *args, **keywd ):
    '''Returns creator function.'''
    def creator( function ):
        return from_address_custom_t( function, *args, **keywd )
    return creator


def get_python_path():
    '''Returns Python include directory.'''
    return sys.prefix +"/include/python"+ sys.version[:3]


def get_gcc_path():
    '''Returns g++ include directory.'''
    proc = subprocess.Popen(["which g++"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    path = out.strip()
    if not path.endswith("bin/g++"):
        exit("Can't find g++")
    return path[:-7]+"include"


def get_gccxml_path():
    '''Returns gccxml path.'''
    proc = subprocess.Popen(["which gccxml"], stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    path = out.strip()
    if not path.endswith("/gccxml"):
        exit("No gccxml!")
    return path[:-7]


def MakePythonAPI(prj):
    '''Produces boost-python code.'''

    if not os.path.exists(prj.temp_dir):
        os.makedirs(prj.temp_dir)

    print( "Generating PythonAPI from %s." % ( prj.master_include ) )

    #If the cache file cache_core.xml doesn't exist it gets created, otherwise it just gets loaded
    print("NOTE: If you update the source library code, run 'codegenerator.py clean'")

    xml_cached_fc = parser.create_cached_source_fc( prj.master_include, prj.cache_filename)
    arch_flag = ""
    arch = platform.architecture()[0]
    if   arch == '64bit':
        arch_flag = "-m64 "
    elif arch == '32bit':
        pass
    else:
        exit( "Unknown architecture" )

    mb = module_builder.module_builder_t(
        [xml_cached_fc],
        include_paths = prj.include_dirs + [get_python_path(), get_gcc_path()],
        gccxml_path = get_gccxml_path(),
        cflags = arch_flag + "-DGCCXML_SKIP_THIS " + prj.special_flags)

    # general rules

    IncludeClasses(mb, prj.include_classes)

    DefineGeneralRules(mb)

    ExcludeConstructorsArgPtr(mb)

    ExcludeMemberFunctionsArgPtr(mb)

    ManageNewReturnPolicy(mb)

    ManageTransferOwnership(mb)

    # execute project-specific rules

    prj.ManualExcludeMemberFunctions(mb)

    prj.ManualClassTunings(mb)

    # default policies for what remained unchanged

    if prj.with_pure_virtual:
        IncludePureVirtualMethods(mb, prj.include_classes)

    DefaultReturnPolicy(mb)

    # disable some warnings

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
        #messages.W1033, # unnamed variables
        #messages.W1018, # expose unnamed classes
        #messages.W1049, # returns reference to local variable
        #messages.W1014, # unsupported '=' operator
    )

    # generate output
    mb.build_code_creator( module_name="PythonInterface", doc_extractor=my_doc_extractor)
    mb.code_creator.license = prj.license

    mb.code_creator.user_defined_directories.append(os.path.abspath('./'))
    mb.split_module(prj.temp_dir)
