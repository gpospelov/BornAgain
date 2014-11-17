############################################################################
# CMakeLists.txt file for building BornAgain/GUI executable
############################################################################
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


# --- source files ---------
include_directories(
    ${BornAgainGUI_INCLUDE_DIRS}
    ${ManhattanStyle_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
)

set(source_files
    main.cpp
)

set(include_files)

# --- Qt configuration ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


# --- system dependent exe options ---------
if(WIN32)
    #set(win32_console 1)
    if(NOT win32_console)
        set(executable_options WIN32)
    endif()

elseif(APPLE)
    set(executable_options MACOSX_BUNDLE)
endif()


# --- system dependent files ---------
if(WIN32)
    set(system_addons bornagain.rc)
endif()


# --- executable ---------
add_executable(${executable_name} ${executable_options} ${source_files} ${include_files} ${system_addons})


# --- dependencies ---------
target_link_libraries(${executable_name}
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    ${PYTHON_LIBRARIES}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${BornAgainGUI_LIBRARY}
)

target_link_libraries(${executable_name}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Script
    Qt5::Designer
    Qt5::PrintSupport
)


# --- extra properties ---------
if(WIN32)
    set_target_properties( ${executable_name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup" )
    if(win32_console)
        set_target_properties( ${executable_name} PROPERTIES COMPILE_DEFINITIONS "_CONSOLE" )
    endif()

elseif(APPLE)
    set (MACOSX_BUNDLE_ICON_FILE BornAgain.icns)
    set(MACOSX_BUNDLE_IDENTIFIER "org.bornagainproject.BornAgain")
    SET_SOURCE_FILES_PROPERTIES(${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/MacOSXBundleInfo.plist.in" "${destination_runtime_configs}/Info.plist" @ONLY)

    set_target_properties( ${executable_name}
        PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${destination_runtime_configs}/Info.plist
    )

#    set(link_flags "-Wl,-rpath,@loader_path/../")
#    set(link_flags "-Wl,-rpath,@loader_path/../\;@loader_path/../lib/LibPython/")
    set(link_flags "-Wl,-rpath,@loader_path/../ -Wl,-rpath,@loader_path/../lib/LibPython/")
    set_target_properties(${executable_name}
        PROPERTIES
        LINK_FLAGS ${link_flags}
    )

endif()

# --- installation ---------
#install (TARGETS ${executable_name} DESTINATION ${destination_gui} COMPONENT Applications)
install (TARGETS ${executable_name} BUNDLE DESTINATION . COMPONENT Applications)

#  install (TARGETS ${executable_name}
#    BUNDLE DESTINATION  . COMPONENT Applications
#    RUNTIME DESTINATION ${destination_bin} COMPONENT Runtime)


set(image_files ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.ico ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_48x48.png  ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_64x64.png)
install (FILES ${image_files} DESTINATION ${destination_images} COMPONENT Applications)


# --- system dependent installation ---------
if(WIN32)

elseif(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    install( FILES ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns
          DESTINATION ${destination_bundle}/Contents/Resources/
    )

    set(plugin_dest_dir ${destination_bundle}/Contents/PlugIns)
    install(DIRECTORY "$ENV{QTDIR}/plugins/platforms" DESTINATION ${plugin_dest_dir} COMPONENT Runtime)

    set(fixup_path @rpath)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/FixAppleBundle.cmake.in ${destination_runtime_configs}/FixAppleBundle.cmake @ONLY)
    install(SCRIPT ${destination_runtime_configs}/FixAppleBundle.cmake COMPONENT Runtime)

#  get_filename_component(PYTHON_REAL_LIBRARY "${PYTHON_LIBRARY}" REALPATH)
#  add_library(Python SHARED IMPORTED)
#  set_property(TARGET Python PROPERTY IMPORTED_LOCATION ${PYTHON_LIBRARY})
#    message("XXXXXX PYTHON_LIBRARY:${PYTHON_LIBRARY} PYTHON_REAL_LIBRARY:${PYTHON_REAL_LIBRARY}  PYTHON_LIBRARIES:${PYTHON_LIBRARIES}")


endif()


#if(APPLE AND CREATE_BUNDLE)
##  set(CMAKE_MACOSX_RPATH 0)
#  add_executable(${executable_name} MACOSX_BUNDLE ${source_files} ${include_files})
##  get_filename_component(PYTHON_REAL_LIBRARY "${PYTHON_LIBRARY}" REALPATH)
##  add_library(Python SHARED IMPORTED)
##  set_property(TARGET Python PROPERTY IMPORTED_LOCATION ${PYTHON_REAL_LIBRARY})

#  target_link_libraries(${executable_name}
#    ${ManhattanStyle_LIBRARY}
#    ${qcustomplot_LIBRARY}
#    ${qtpropertybrowser_LIBRARY}
#    ${PYTHON_LIBRARY}
#    ${Boost_LIBRARIES}
#    ${BornAgainCore_LIBRARY}
#    ${BornAgainFit_LIBRARY}
#    ${BornAgainGUI_LIBRARY}
##    Python
#  )
#else()
#  add_executable(${executable_name} ${WIN_CONSOLE} ${source_files} ${include_files} ${RC_FILE})
##  qt5_use_modules(${executable_name} Widgets Core Gui Script Designer PrintSupport)

#  target_link_libraries(${executable_name}
#    ${ManhattanStyle_LIBRARY}
#    ${qcustomplot_LIBRARY}
#    ${qtpropertybrowser_LIBRARY}
#    ${PYTHON_LIBRARY}
#    ${Boost_LIBRARIES}
#    ${BornAgainCore_LIBRARY}
#    ${BornAgainFit_LIBRARY}
#    ${BornAgainGUI_LIBRARY}
#  )
#endif(APPLE AND CREATE_BUNDLE)


## Entry point flag for Windows to ensure we always link to standard main
#if( WIN32 )
#    set_target_properties( ${executable_name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup" )
#    if ( CONSOLE )
#        set_target_properties( ${executable_name} PROPERTIES COMPILE_DEFINITIONS "_CONSOLE" )
#    endif ( CONSOLE )
#endif( WIN32 )

##target_link_libraries(${executable_name}
##    ${ManhattanStyle_LIBRARY}
##    ${qcustomplot_LIBRARY}
##    ${qtpropertybrowser_LIBRARY}
##    ${PYTHON_LIBRARY}
##    ${Boost_LIBRARIES}
##    ${BornAgainCore_LIBRARY}
##    ${BornAgainFit_LIBRARY}
##    ${BornAgainGUI_LIBRARY}
##)

## --- Installation ---
#IF(APPLE AND CREATE_BUNDLE)

#    set(link_flags "-Wl,-rpath,@loader_path/../")
#    set_target_properties(${executable_name}
#        PROPERTIES
##        INSTALL_RPATH "@loader_path/.."
#        LINK_FLAGS ${link_flags}
#    )

##    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
##    set(CMAKE_INSTALL_RPATH "@loader_path/..")

#  set(plugin_dest_dir ${INBUNDLE}/Contents/PlugIns)
#  set(qtconf_dest_dir ${INBUNDLE}/Contents/Resources)
#  set(APPS "\${CMAKE_INSTALL_PREFIX}/${INBUNDLE}")

##  message("PYTHON_LIBRARY: ${PYTHON_LIBRARY}")

#  get_filename_component(ManhattanStyle_LIBRARY_DIR "${ManhattanStyle_LIBRARY}" REALPATH)
#  get_filename_component(qcustomplot_LIBRARY_DIR "${qcustomplot_LIBRARY}" REALPATH)
#  get_filename_component(qtpropertybrowser_LIBRARY_DIR "${qtpropertybrowser_LIBRARY}" REALPATH)
#  get_filename_component(Boost_Real_LIBRARY_DIR "${Boost_LIBRARY_DIR}" REALPATH)
##  get_filename_component(PYTHON_LIBRARY_DIR "${PYTHON_LIBRARIES}" REALPATH)
#  get_filename_component(PYTHON_REAL_LIBRARY_DIR "${PYTHON_LIBRARY}" REALPATH)

#  message("OOO PYTHON_LIBRARY_DIR: ${PYTHON_LIBRARY_DIR}  PYTHON_LIBRARY:${PYTHON_LIBRARY}  PYTHON_LIBRARIES:${PYTHON_LIBRARIES}")
#  message("OOO2 PYTHON_REAL_LIBRARY_DIR:${PYTHON_REAL_LIBRARY_DIR}")
#  message("OOO3 CMAKE_LIBRARY_OUTPUT_DIRECTORY:${CMAKE_LIBRARY_OUTPUT_DIRECTORY} CMAKE_LIBRARY_PATH:${CMAKE_LIBRARY_PATH}")

#  set(DIRS
##    ${ManhattanStyle_LIBRARY_DIR}
##    ${qcustomplot_LIBRARY_DIR}
##    ${qtpropertybrowser_LIBRARY_DIR}
#    ${PYTHON_REAL_LIBRARY_DIR}
#    ${Boost_Real_LIBRARY_DIR}
#    "${CMAKE_BINARY_DIR}/lib"
#    "$ENV{QTDIR}"
#    "$ENV{QTDIR}/plugins"
#  )


#  install (TARGETS ${executable_name}
#    BUNDLE DESTINATION  . COMPONENT Applications
#    RUNTIME DESTINATION ${destination_bin} COMPONENT Runtime)

##    set_target_properties(${executable_name} PROPERTIES INSTALL_RPATH "@loader_path/../" MACOSX_RPATH 1)

#  message("WWWWWWW ${plugin_dest_dir}")
#  install(DIRECTORY "$ENV{QTDIR}/plugins/platforms" DESTINATION ${plugin_dest_dir} COMPONENT Runtime)

##  set(qtconf_text "
##[Paths]
##Plugins = PlugIns
##  ")

##  install(CODE "
##    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"${qtconf_text}\")
##    " COMPONENT Runtime)

##  install(CODE "
##    file(GLOB_RECURSE QTPLUGINS
##      \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
##    set(BU_CHMOD_BUNDLE_ITEMS True)
##    set(BU_COPY_FULL_FRAMEWORK_CONTENTS False)
##    include(${CMAKE_MODULE_PATH}/BABundleUtilities.cmake)
##    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
##    " COMPONENT Runtime)

##    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/bundle.cmake.in ${CMAKE_BINARY_DIR}/bundle.cmake @ONLY)
##    install(SCRIPT ${CMAKE_BINARY_DIR}/bundle.cmake COMPONENT Runtime)

#    set(fixup_path @rpath)
#    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/FixBundle.cmake.in ${CMAKE_BINARY_DIR}/FixBundle.cmake @ONLY)
#    install(SCRIPT ${CMAKE_BINARY_DIR}/FixBundle.cmake COMPONENT Runtime)


#else()
#  install (TARGETS ${executable_name} DESTINATION ${destination_bin} COMPONENT Applications)

#    set(image_files ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.ico ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_48x48.png  ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_64x64.png)
#    install (FILES ${image_files} DESTINATION ${destination_images} COMPONENT Applications)

#endif(APPLE AND CREATE_BUNDLE)

