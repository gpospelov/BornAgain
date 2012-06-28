# c++ wrapper generator for accessing libScatCore from python
# Usage: python codegenerator.py
#
# Produces WrapperCode.cpp on disk which has to be then manualy inserted into
# Core/Samples/src/PythonSamplesInterface.cpp
# Core/Tools/src/PythonToolsInterface.cpp
# Core/Algorithms/src/PythonToolsInterface.cpp
#
# requires boost, python27, py27-pyplusplus-devel, py-pygccxml-devel, gccxml-devel
#

import os
import sys
from pyplusplus import module_builder
from pyplusplus.module_builder import call_policies
from pyplusplus import messages
from pygccxml.declarations.matchers import access_type_matcher_t

mb = module_builder.module_builder_t(
        files=[ 'Types.h', 'Units.h']
        , include_paths=['../../Core/Samples/inc','../../Core/Algorithms/inc','../../Core/Tools/inc'], gccxml_path='/opt/local/bin')


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

#Generated code will not compile on
mem_funs = mb.calldefs ()
mem_funs.create_with_signature = True

# ---------------------------------------------------------
# class individual properties
# ---------------------------------------------------------
mb.class_('PyHelperKVector').exclude()

# ---------------------------------------------------------
# generating output
# ---------------------------------------------------------

#Now it is the time to give a name to our module
mb.build_code_creator( module_name='libScatCore' )

mb.write_module( 'WrapperCode_Tools.cpp' )
