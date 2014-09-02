###########################################################################
# Mac-specific installation setup
###########################################################################
#set ( CMAKE_INSTALL_PREFIX "" )
set ( CPACK_PACKAGE_EXECUTABLES BornAgain )
set ( INBUNDLE BornAgain.app )


set(destination_bin ${INBUNDLE}/Contents/MacOs)
set(destination_lib ${INBUNDLE}/Contents/MacOs)
set(destination_include ${INBUNDLE}/Contents/Resources/Headers)
set(destination_examples ${INBUNDLE}/Contents/SharedSupport/Examples)

install ( FILES ${CMAKE_SOURCE_DIR}/Images/BAicon.icns
          DESTINATION ${INBUNDLE}/Contents/Resources/
)

#set ( CPACK_DMG_BACKGROUND_IMAGE ${CMAKE_SOURCE_DIR}/Images/osx-bundle-background.png )
#set ( CPACK_DMG_DS_STORE ${CMAKE_SOURCE_DIR}/Installers/MacInstaller/osx_DS_Store)
set ( MACOSX_BUNDLE_ICON_FILE BAicon.icns )
SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/Images/BAicon.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
