# common rules and utilities for boost python code generation
import os
import sys
import glob
import subprocess
from pyplusplus import module_builder
from pyplusplus.module_builder import call_policies
from pyplusplus import messages
from pyplusplus import file_writers
from pygccxml.declarations.matchers import access_type_matcher_t
from pygccxml.declarations.matchers import virtuality_type_matcher_t
from pygccxml import declarations
from pyplusplus import function_transformers as FT
from pygccxml import parser
from pyplusplus.function_transformers import transformers
from pyplusplus.file_writers.balanced_files import balanced_files_t
from pyplusplus.file_writers.multiple_files import multiple_files_t


license = "// BornAgain: simulate and fit scattering at grazing incidence \n" \
           "//! @brief automatically generated boost::python code for PythonCoreAPI  \n"

ModuleName = 'PythonInterface'

balanced_files_t.HEADER_EXT = '.h'
balanced_files_t.SOURCE_EXT = '.cpp'
multiple_files_t.HEADER_EXT = '.pypp.h'
multiple_files_t.SOURCE_EXT = '.pypp.cpp'


def ExcludeConstructorsArgPtr(mb):
    '''Excludes constructors which have pointers in argument list.'''
    for cl in mb.classes():
        for ctor in cl.constructors(allow_empty=True):
            for arg in ctor.arguments:
                if declarations.type_traits.is_pointer(arg.type): ctor.exclude()


def ExcludeMemberFunctionsArgPtr(mb):
    '''Excludes member functions if they have pointers in argument list.'''
    for cl in mb.classes():
        for fun in cl.member_functions(allow_empty=True):
            has_pointers = False
            for arg in fun.arguments:
                if declarations.type_traits.is_pointer(arg.type):
                    has_pointers = True
            if has_pointers: 
                #print "XXX",cl.name, fun.name
                fun.exclude();


def IncludePureVirtualMethods(mb, include_classes):
    '''Includes pure virtual methods.'''
    for cl in mb.classes():
        itsOurClass = False
        for name in include_classes:
            if name == cl.name or name == cl.alias:
                itsOurClass=True
        if not itsOurClass:
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
        isFound = False
        for cl in mb.classes():
            if name == cl.name or name == cl.alias: isFound = True
        if not isFound: not_found_classes.append(name)
    if len(not_found_classes): 
        print "Error! Can't find classes with requested names ", not_found_classes
        exit()
    mb.classes( lambda cls: cls.name in include_classes ).include()


def ExcludeMemberFunctionsForClasses(mb, method_names, class_names):
    '''If class name in 'class_names' then exclude 'method_names'.'''
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
    query = declarations.access_type_matcher_t( 'private' ) & ~declarations.virtuality_type_matcher_t(
        declarations.VIRTUALITY_TYPES.PURE_VIRTUAL )
    mb.global_ns.calldefs( query, allow_empty=True ).exclude()
    query = declarations.access_type_matcher_t( 'protected' ) & ~declarations.virtuality_type_matcher_t(
        declarations.VIRTUALITY_TYPES.PURE_VIRTUAL )
    mb.global_ns.calldefs( query, allow_empty=True ).exclude()
    # excluding generation of methods for implicit conversion
    mb.constructors().allow_implicit_conversion = False


def ManageNewReturnPolicy(mb):
    '''Returns policy for singletons, clone and create methods.'''
    for cl in mb.classes():
        cl.member_functions('instance', allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )
        cl.member_functions('clone', allow_empty=True).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )
        cl.member_functions( lambda x: x.name.startswith('create'), allow_empty=True ).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )


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
            mem_fun.call_policies = call_policies.return_value_policy(
                call_policies.reference_existing_object )


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
                              ( function, self.arg_ref.name, arg.type) )

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
    proc = subprocess.Popen(["which gccxml"],
                            stdout=subprocess.PIPE, shell=True)
    (out, err) = proc.communicate()
    path = out.strip()
    if not path.endswith("/gccxml"):
        exit("No gccxml!")
    return path[:-7]
