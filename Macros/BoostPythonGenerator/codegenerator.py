# c++ wrapper generator for accessing libScatCore from python
#
# Usage: 'python codegenerator.py make'  - to generate python-boost C++ wrappers
# Usage: 'python codegenerator.py install'  - to copy files into GISASFW/Core/PythonAPI directory
#
# requires boost, python27, py27-pyplusplus-devel, py-pygccxml-devel, gccxml-devel
#

import os
import sys
import glob
from pyplusplus import module_builder
from pyplusplus.module_builder import call_policies
from pyplusplus import messages
from pyplusplus import file_writers
from pygccxml.declarations.matchers import access_type_matcher_t


ModuleName = 'PythonInterface'
nOutputFiles = 3 # generated code for classes will be splitted in
InstallDir = '../../Core/PythonAPI'
OutputDir='output'


#-------------------------------------------------------------
# GenerateCode()
#-------------------------------------------------------------
def GenerateCode():
  from pyplusplus.file_writers.balanced_files import balanced_files_t
  balanced_files_t.HEADER_EXT='.h'
  balanced_files_t.SOURCE_EXT='.cpp'
  #from pyplusplus.file_writers.multiple_files import multiple_files_t
  #multiple_files_t.HEADER_EXT='.h'
  #multiple_files_t.SOURCE_EXT='.cpp'

  mb = module_builder.module_builder_t(
          files=[
            'Types.h',
            'PythonPlusplusHelper.h',
            'Units.h',
            'IMaterial.h',
            'HomogeneousMaterial.h',
            'ISingleton.h',
            'MaterialManager.h',
            #'ISample.h'
            #'Types.h'
            'LayerRoughness.h',
            'Layer.h',
            'MultiLayer.h',
            'ParameterPool.h',
            'OpticalFresnel.h'
          ]
          , include_paths=['../../Core/Samples/inc','../../Core/Algorithms/inc','../../Core/Tools/inc','../../Core/PythonAPI/inc']
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
  #mb.class_( "ParameterPool" ).member_function( "begin" ).exclude()
  #mb.class_( "ParameterPool" ).member_function( "end" ).exclude()
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
  #mb.class_( "MultiLayer").member_function( "getDWBASimulation" ).call_policies = call_policies.return_value_policy(call_policies.reference_existing_object )
  mb.class_( "MultiLayer" ).member_function( "getDWBASimulation" ).exclude()

  #mb.namespace('Units').exclude()
  #mb.variables().always_expose_using_scope = True
  #mb.classes().always_expose_using_scope = True

  # OpticalFresnel
  #mb.class_('KVector<double>').already_exposed=True
  #mb.class_('MultiLayer').already_exposed=True
  #mb.class_('PyHelperKVector').exclude()

  # from PythonPlusplusHelper.h - we do not need these classes visbile in python
  mb.class_('PythonPlusplusKVector').exclude()

  # ---------------------------------------------------------
  # generating output
  # ---------------------------------------------------------
  mb.build_code_creator( module_name=ModuleName)
  mb.code_creator.user_defined_directories.append( os.path.abspath('./') )
  mb.balanced_split_module( OutputDir, nOutputFiles)
  
  

#-------------------------------------------------------------
# InstallCode()
#-------------------------------------------------------------
def InstallCode():
  #headers=glob.glob(OutputDir+"/*.h");
  #sources=glob.glob(OutputDir+"/*.cpp");
  files=glob.glob(OutputDir+"/*.h");
  files+= glob.glob(OutputDir+"/*.cpp");

  copycommand='cp '

  # copying files
  overwriteAnswer=''
  for f in files:
    fileName = os.path.basename(f)

    # we are skipping files like PythonInterface.main.cpp
    if 'main' in f:
      continue

    # different output directory for source and headers
    outputName=''
    if '.cpp' in fileName:
      outputName=InstallDir+"/src/"+fileName
    elif '.h' in fileName:
      outputName=InstallDir+"/inc/"+fileName

    # check file existance
    if os.path.exists(outputName) and overwriteAnswer != 'a':
      prompt="File '"+outputName+"' exists, Overwrite? [y/a/n] "
      overwriteAnswer=raw_input(prompt)
    if overwriteAnswer == 'y' or overwriteAnswer=='a':
      command = copycommand + f + " " + outputName
      print command
      os.system(command)

    else:
      continue

    
#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
def main():
  if len(sys.argv)!=2:
    print "Usage: 'python codegenerator.py make' - generates python boost wrapping code in ./output subdirectory"
    print "Usage: 'python codegenerator.py install' - installs generated code to GISASFW/PythonAPI"
    print " "

  else:
    if sys.argv[1] == 'make':
      GenerateCode()
    elif sys.argv[1] == 'install':
      InstallCode()
    else:
      print "Nothing to do, run 'python codegenerator.py' to get help"


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
  main()



  