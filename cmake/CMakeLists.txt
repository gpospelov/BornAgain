# this script is a trick to print the message at the end of installation

if(NOT WIN32)
set(after_install_text "
Installation done. Please read below.
-------------------------------------------------------------------------------
To be able to use BornAgain you have to add BornAgain installation directory, 
namely ${CMAKE_INSTALL_PREFIX}/lib 
into your LD_LIBRARY_PATH and PYTHONPATH.
You can do it by running the command 'source ${CMAKE_INSTALL_PREFIX}/bin/thisbornagain.sh'
Just add this command into your .bashrc or .bash_profile file.
-------------------------------------------------------------------------------
")

install(CODE "MESSAGE(\"${after_install_text}\")")

endif()
