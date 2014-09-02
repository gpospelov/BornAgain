###########################################################################
# Mac-specific installation setup
###########################################################################
#set ( CMAKE_INSTALL_PREFIX "" )
set ( CPACK_PACKAGE_EXECUTABLES BornAgain )
set ( INBUNDLE BornAgain.app )


set(destination_bin ${INBUNDLE}/Contents/MacOs)
set(destination_lib ${INBUNDLE}/Contents/MacOs)
set(destination_include ${INBUNDLE}/Contents/Resources/include)
set(destination_examples ${INBUNDLE}/Contents/SharedSupport/Examples)

#set ( BIN_DIR ${INBUNDLE}/Contents/MacOS )
#set ( LIB_DIR ${INBUNDLE}/Contents/MacOS )
#set ( PLUGINS_DIR ${INBUNDLE}/Contents/PlugIns )
#set ( PVPLUGINS_DIR MantidPlot.app/pvplugins )

#if (OSX_VERSION VERSION_LESS 10.9)
# set ( PYQT4_PYTHONPATH /Library/Python/${PY_VER}/site-packages/PyQt4 )
# set ( SITEPACKAGES /Library/Python/${PY_VER}/site-packages )
#else()
# # Assume we are using homebrew for now
# set ( PYQT4_PYTHONPATH /usr/local/lib/python${PY_VER}/site-packages/PyQt4 )
# set ( SITEPACKAGES /usr/local/lib/python${PY_VER}/site-packages )
#endif()

# Python packages

#install ( PROGRAMS ${SITEPACKAGES}/sip.so DESTINATION ${BIN_DIR} )

# Explicitly specify which PyQt libraries we want because just taking the whole
# directory will swell the install kit unnecessarily.
#install ( FILES ${PYQT4_PYTHONPATH}/Qt.so
#                ${PYQT4_PYTHONPATH}/QtCore.so
#                ${PYQT4_PYTHONPATH}/QtGui.so
#                ${PYQT4_PYTHONPATH}/QtOpenGL.so
#                ${PYQT4_PYTHONPATH}/QtSql.so
#                ${PYQT4_PYTHONPATH}/QtSvg.so
#                ${PYQT4_PYTHONPATH}/QtXml.so
#                ${PYQT4_PYTHONPATH}/__init__.py
#          DESTINATION ${BIN_DIR}/PyQt4 )
# Newer PyQt versions have a new internal library that we need to take
#if ( EXISTS ${PYQT4_PYTHONPATH}/_qt.so )
#  install ( FILES ${PYQT4_PYTHONPATH}/_qt.so
#            DESTINATION ${BIN_DIR}/PyQt4 )
#endif ()

#install ( DIRECTORY ${PYQT4_PYTHONPATH}/uic DESTINATION ${BIN_DIR}/PyQt4 )

# Python packages in Third_Party need copying to build directory and the final package
#file ( GLOB THIRDPARTY_PYTHON_PACKAGES ${CMAKE_LIBRARY_PATH}/Python/* )
#foreach ( PYPACKAGE ${THIRDPARTY_PYTHON_PACKAGES} )
#  if ( IS_DIRECTORY ${PYPACKAGE} )
#    install ( DIRECTORY ${PYPACKAGE} DESTINATION ${BIN_DIR} )
#  endif()
#  file ( COPY ${PYPACKAGE} DESTINATION ${PROJECT_BINARY_DIR}/bin )
#endforeach( PYPACKAGE )

#install ( DIRECTORY ${QT_PLUGINS_DIR}/imageformats DESTINATION ${INBUNDLE}/Contents/Frameworks/plugins )
#install ( DIRECTORY ${QT_PLUGINS_DIR}/sqldrivers DESTINATION ${INBUNDLE}/Contents/Frameworks/plugins )

install ( FILES ${CMAKE_SOURCE_DIR}/Images/BAicon.icns
          DESTINATION ${INBUNDLE}/Contents/Resources/
)

#set ( CPACK_DMG_BACKGROUND_IMAGE ${CMAKE_SOURCE_DIR}/Images/osx-bundle-background.png )
#set ( CPACK_DMG_DS_STORE ${CMAKE_SOURCE_DIR}/Installers/MacInstaller/osx_DS_Store)
set ( MACOSX_BUNDLE_ICON_FILE BAicon.icns )
SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/Images/BAicon.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

#string (REPLACE " " "" CPACK_SYSTEM_NAME ${OSX_CODENAME})

#set ( CPACK_GENERATOR DragNDrop )
