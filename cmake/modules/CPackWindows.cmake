# BornAgain Windows packaging 

set(CPACK_GENERATOR "NSIS")  

#set(CPACK_NSIS_MODIFY_PATH ON)
set( CPACK_NSIS_INSTALL_ROOT "C:")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

set (CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
  Push \\\"PATH\\\" 
  Push \\\"A\\\" 
  Push \\\"HKCU\\\" 
  Push \\\"$INSTDIR\\\\bin\\\" 
  Call EnvVarUpdate
  Pop  \\\$0

  Push \\\"PYTHONPATH\\\" 
  Push \\\"A\\\" 
  Push \\\"HKCU\\\" 
  Push \\\"$INSTDIR\\\\bin\\\" 
  Call EnvVarUpdate
  Pop  \\\$0

  CreateShortCut \\\"$DESKTOP\\\\BornAgain.lnk\\\" \\\"$INSTDIR\\\\bin\\\\BornAgain.exe\\\"
")
        
set (CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
  Push \\\"PATH\\\"
  Push \\\"R\\\"
  Push \\\"HKCU\\\"
  Push \\\"$INSTDIR\\\\bin\\\"
  Call un.EnvVarUpdate
  Pop  \\\$0

  Push \\\"PYTHONPATH\\\"
  Push \\\"R\\\"
  Push \\\"HKCU\\\"
  Push \\\"$INSTDIR\\\\bin\\\"
  Call un.EnvVarUpdate
  Pop  \\\$0

  Delete \\\"$DESKTOP\\\\BornAgain.lnk\\\"

")

