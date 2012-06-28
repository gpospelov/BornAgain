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
        files=[
          'IMaterial.h',
          'HomogeneousMaterial.h',
          'ISingleton.h',
          'MaterialManager.h',
          #'ISample.h'
          #'Types.h'
          'LayerRoughness.h',
          'Layer.h',
          'MultiLayer.h',
          'ParameterPool.h'
        ]
        , include_paths=['../../Core/Samples/inc','../../Core/Algorithms/inc','../../Core/Tools/inc']
        , gccxml_path='/opt/local/bin'
        )

        
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

# policy for singletons
mb.member_functions( "instance" ).call_policies = call_policies.return_value_policy( call_policies.reference_existing_object )

#policy for clone methods
mb.member_functions( "clone" ).call_policies = call_policies.return_value_policy( call_policies.manage_new_object )

# disable some warnings
messages.disable( messages.W1035 )

#Generated code will not compile on
mem_funs = mb.calldefs ()
mem_funs.create_with_signature = True

#mb.class_('IMaterial').include(already_exposed=True)

# ---------------------------------------------------------
# class individual properties
# ---------------------------------------------------------
mb.class_( "MaterialManager" ).constructors().exclude()
mb.class_( "MaterialManager" ).member_function( "getMaterial" ).call_policies = call_policies.return_internal_reference( )
mb.class_( "MaterialManager" ).member_function( "addHomogeneousMaterial" ).call_policies = call_policies.return_internal_reference( )
#mb.class_( "MaterialManager" ).member_function( "getMaterial" ).call_policies = call_policies.reference_existing_object( )
#mb.class_( "MaterialManager" ).member_function( "addHomogeneousMaterial" ).call_policies = call_policies.reference_existing_object( )
#mb.class_( "MaterialManager" ).disable_warnings( messages.W1035 )

#mb.class_( "ISample" ).member_function( "getCompositeSample" ).call_policies = call_policies.return_self( )
#mb.class_( "ISample" ).member_function( "createParameterTreeTest" ).exclude()
#mb.class_( "ISample" ).member_function( "getParameterPool" ).call_policies = call_policies.return_internal_reference( )
#mb.class_( "ISample" ).member_function( "createParameterTree" ).call_policies = call_policies.manage_new_object( )
#mb.class_( "ISample" ).member_function( "clone" ).call_policies = call_policies.custom_call_policies("bp::return_value_policy<bp::clone_const_reference>")

mb.class_( "LayerRoughness" ).member_function( "getSpectralFun" ).exclude()
mb.class_( "LayerRoughness" ).member_function( "getCorrFun" ).exclude()

#mb.class_( "ParameterPool" ).member_function( "cloneWithPrefix" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )
mb.class_( "ParameterPool" ).member_function( "cloneWithPrefix" ).call_policies = call_policies.return_value_policy(call_policies.manage_new_object )
mb.class_( "ParameterPool" ).member_function( "begin" ).exclude()
mb.class_( "ParameterPool" ).member_function( "end" ).exclude()
mb.class_( "MaterialManager" ).disable_warnings( messages.W1051 ) # not sure

mb.class_( "Layer" ).member_function( "clone" ).exclude()
mb.class_( "Layer" ).member_function( "setThickness" ).exclude()
mb.class_( "Layer" ).member_function( "getThickness" ).exclude()
mb.class_( "Layer" ).member_function( "getMaterial" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )
mb.class_( "Layer" ).member_function( "getRefractiveIndex" ).exclude()
#mb.class_( "Layer" ).member_function( "getMaterial" ).call_policies = call_policies.return_internal_reference( )
mb.class_( "Layer" ).member_function( "getDWBASimulation" ).exclude()

mb.class_( "MultiLayer" ).member_function( "getLayer" ).exclude();
mb.class_( "MultiLayer" ).member_function( "getLayerBottomZ" ).exclude();
mb.class_( "MultiLayer" ).member_function( "getLayerThickness" ).exclude();
mb.class_( "MultiLayer" ).member_function( "getLayerTopInterface" ).exclude();
mb.class_( "MultiLayer" ).member_function( "getLayerBottomInterface" ).exclude();
mb.class_( "MultiLayer" ).member_function( "clear" ).exclude();
mb.class_( "MultiLayer" ).member_function( "clone" ).exclude()
mb.class_( "MultiLayer" ).member_function( "getCrossCorrSpectralFun" ).exclude();
mb.class_( "MultiLayer" ).member_function( "setLayerThickness" ).exclude();
mb.class_( "MultiLayer").member_function( "getDWBASimulation" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )

#mb.namespace('Units').exclude()
#mb.variables().always_expose_using_scope = True
#mb.classes().always_expose_using_scope = True
 
# ---------------------------------------------------------
# generating output
# ---------------------------------------------------------

#Now it is the time to give a name to our module
mb.build_code_creator( module_name='libScatCore' )

mb.write_module( 'WrapperCode_Samples.cpp' )
#mb.balanced_split_module( 'balanced', 3 )
