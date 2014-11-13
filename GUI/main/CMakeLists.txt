cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()
if(POLICY CMP0028)
    cmake_policy(SET CMP0028 NEW)
endif()

set(executable_name BornAgain)

include_directories(
    ${BornAgainGUI_INCLUDE_DIRS}
    ${ManhattanStyle_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
)

set(source_files
    main.cpp
)

set(include_files)

# Application icon
if(WIN32)
    set(RC_FILE bornagain.rc)
   if ( CONSOLE )
     set ( WIN_CONSOLE )
   else ()
     set( WIN_CONSOLE WIN32 )
   endif( CONSOLE )
endif()


if(APPLE AND CREATE_BUNDLE)
#  set(CMAKE_MACOSX_RPATH 0)
  add_executable(${executable_name} MACOSX_BUNDLE ${source_files} ${include_files})
#  get_filename_component(PYTHON_REAL_LIBRARY "${PYTHON_LIBRARY}" REALPATH)
#  add_library(Python SHARED IMPORTED)
#  set_property(TARGET Python PROPERTY IMPORTED_LOCATION ${PYTHON_REAL_LIBRARY})

  target_link_libraries(${executable_name}
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    ${PYTHON_LIBRARY}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${BornAgainGUI_LIBRARY}
#    Python
  )
else()
  add_executable(${executable_name} ${WIN_CONSOLE} ${source_files} ${include_files} ${RC_FILE})
#  qt5_use_modules(${executable_name} Widgets Core Gui Script Designer PrintSupport)

  target_link_libraries(${executable_name}
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    ${PYTHON_LIBRARY}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${BornAgainGUI_LIBRARY}
  )
endif(APPLE AND CREATE_BUNDLE)


# Entry point flag for Windows to ensure we always link to standard main
if( WIN32 )
    set_target_properties( ${executable_name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup" )
    if ( CONSOLE )
        set_target_properties( ${executable_name} PROPERTIES COMPILE_DEFINITIONS "_CONSOLE" )
    endif ( CONSOLE )
endif( WIN32 )

#target_link_libraries(${executable_name}
#    ${ManhattanStyle_LIBRARY}
#    ${qcustomplot_LIBRARY}
#    ${qtpropertybrowser_LIBRARY}
#    ${PYTHON_LIBRARY}
#    ${Boost_LIBRARIES}
#    ${BornAgainCore_LIBRARY}
#    ${BornAgainFit_LIBRARY}
#    ${BornAgainGUI_LIBRARY}
#)

# --- Installation ---
IF(APPLE AND CREATE_BUNDLE)

    set(link_flags "-Wl,-rpath,@loader_path/../")
    set_target_properties(${executable_name}
        PROPERTIES
#        INSTALL_RPATH "@loader_path/.."
        LINK_FLAGS ${link_flags}
    )

#    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
#    set(CMAKE_INSTALL_RPATH "@loader_path/..")

  set(plugin_dest_dir ${INBUNDLE}/Contents/PlugIns)
  set(qtconf_dest_dir ${INBUNDLE}/Contents/Resources)
  set(APPS "\${CMAKE_INSTALL_PREFIX}/${INBUNDLE}")

#  message("PYTHON_LIBRARY: ${PYTHON_LIBRARY}")

  get_filename_component(ManhattanStyle_LIBRARY_DIR "${ManhattanStyle_LIBRARY}" REALPATH)
  get_filename_component(qcustomplot_LIBRARY_DIR "${qcustomplot_LIBRARY}" REALPATH)
  get_filename_component(qtpropertybrowser_LIBRARY_DIR "${qtpropertybrowser_LIBRARY}" REALPATH)
  get_filename_component(Boost_Real_LIBRARY_DIR "${Boost_LIBRARY_DIR}" REALPATH)
#  get_filename_component(PYTHON_LIBRARY_DIR "${PYTHON_LIBRARIES}" REALPATH)
  get_filename_component(PYTHON_REAL_LIBRARY_DIR "${PYTHON_LIBRARY}" REALPATH)

  message("OOO PYTHON_LIBRARY_DIR: ${PYTHON_LIBRARY_DIR}  PYTHON_LIBRARY:${PYTHON_LIBRARY}  PYTHON_LIBRARIES:${PYTHON_LIBRARIES}")
  message("OOO2 PYTHON_REAL_LIBRARY_DIR:${PYTHON_REAL_LIBRARY_DIR}")
  message("OOO3 CMAKE_LIBRARY_OUTPUT_DIRECTORY:${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CMAKE_LIBRARY_PATH:${CMAKE_LIBRARY_PATH}")

  set(DIRS
#    ${ManhattanStyle_LIBRARY_DIR}
#    ${qcustomplot_LIBRARY_DIR}
#    ${qtpropertybrowser_LIBRARY_DIR}
    ${PYTHON_REAL_LIBRARY_DIR}
    ${Boost_Real_LIBRARY_DIR}
    "${CMAKE_BINARY_DIR}/lib"
    "$ENV{QTDIR}"
    "$ENV{QTDIR}/plugins"
  )


  install (TARGETS ${executable_name}
    BUNDLE DESTINATION  . COMPONENT Applications
    RUNTIME DESTINATION ${destination_bin} COMPONENT Runtime)

#    set_target_properties(${executable_name} PROPERTIES INSTALL_RPATH "@loader_path/../" MACOSX_RPATH 1)

  message("WWWWWWW ${plugin_dest_dir}")
  install(DIRECTORY "$ENV{QTDIR}/plugins/platforms" DESTINATION ${plugin_dest_dir} COMPONENT Runtime)

#  set(qtconf_text "
#[Paths]
#Plugins = PlugIns
#  ")

#  install(CODE "
#    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"${qtconf_text}\")
#    " COMPONENT Runtime)

#  install(CODE "
#    file(GLOB_RECURSE QTPLUGINS
#      \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
#    set(BU_CHMOD_BUNDLE_ITEMS True)
#    set(BU_COPY_FULL_FRAMEWORK_CONTENTS False)
#    include(${CMAKE_MODULE_PATH}/BABundleUtilities.cmake)
#    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
#    " COMPONENT Runtime)

#    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/bundle.cmake.in ${CMAKE_BINARY_DIR}/bundle.cmake @ONLY)
#    install(SCRIPT ${CMAKE_BINARY_DIR}/bundle.cmake COMPONENT Runtime)

    set(fixup_path @rpath)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/FixBundle.cmake.in ${CMAKE_BINARY_DIR}/FixBundle.cmake @ONLY)
    install(SCRIPT ${CMAKE_BINARY_DIR}/FixBundle.cmake COMPONENT Runtime)


else()
  install (TARGETS ${executable_name} DESTINATION ${destination_bin} COMPONENT Applications)

    set(image_files ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.ico ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_48x48.png  ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_64x64.png)
    install (FILES ${image_files} DESTINATION ${destination_images} COMPONENT Applications)

endif(APPLE AND CREATE_BUNDLE)

