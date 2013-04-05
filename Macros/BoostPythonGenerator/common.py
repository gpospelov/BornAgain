# common rules and utilities for boost python code generation
import os
import sys
import glob
from pygccxml.declarations.matchers import access_type_matcher_t
from pygccxml.declarations.matchers import virtuality_type_matcher_t
from pygccxml import declarations


license =  "// BornAgain: simulate and fit scattering at grazing incidence \n" \
           "//! @brief automatically generated boost::python code for PythonCoreAPI  \n"

# excluding constructors which have pointers in argument list
def ExcludeConstructorsArgPtr(mb):
    for cl in mb.classes():
        for ctor in cl.constructors(allow_empty=True):
            for arg in ctor.arguments:
                if declarations.type_traits.is_pointer(arg.type): ctor.exclude()


# excluding member functions if they have pointers in argument list
def ExcludeMemberFunctionsArgPtr(mb):
    for cl in mb.classes():
        for fun in cl.member_functions(allow_empty=True):
            has_pointers = False
            for arg in fun.arguments:
                if declarations.type_traits.is_pointer(arg.type): has_pointers = True
            if has_pointers: fun.exclude();

