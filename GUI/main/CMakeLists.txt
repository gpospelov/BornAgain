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
    main.cpp appoptions.cpp
)

set(include_files appoptions.h)

# --- Qt configuration ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


# --- system dependent exe options ---------
if(WIN32)
    #set(win32_console 1)
    if(NOT win32_console)
        set(executable_options WIN32)
    endif()

elseif(APPLE AND BORNAGAIN_APPLE_BUNDLE)
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
#    ${ManhattanStyle_LIBRARY}
#    ${qcustomplot_LIBRARY}
#    ${qtpropertybrowser_LIBRARY}
#    ${PYTHON_LIBRARIES}
#    ${Boost_LIBRARIES}
#    ${BornAgainCore_LIBRARY}
#    ${BornAgainFit_LIBRARY}
    ${BornAgainGUI_LIBRARY}
)

#target_link_libraries(${executable_name}
#    Qt5::Widgets
#    Qt5::Core
#    Qt5::Gui
##     Qt5::Script
#    Qt5::Designer
#    Qt5::PrintSupport
#)


# --- extra target properties ---------
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

    set(link_flags "-Wl,-rpath,@loader_path/../ -Wl,-rpath,@loader_path/../lib/LibPython/")
    set_target_properties(${executable_name}
        PROPERTIES
        LINK_FLAGS ${link_flags}
    )

endif()


# --- installation section ---------
if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
    set(executable_destination BUNDLE DESTINATION  ".")
else()
    set(executable_destination DESTINATION ${destination_gui})
endif()
install (TARGETS ${executable_name} ${executable_destination} COMPONENT Applications)
set(image_files ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.ico ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_48x48.png  ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_64x64.png)
install (FILES ${image_files} DESTINATION ${destination_images} COMPONENT Applications)

#if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
#    install (TARGETS ${executable_name} BUNDLE DESTINATION . COMPONENT Applications)
#else()
#    install (TARGETS ${executable_name} DESTINATION ${destination_gui} COMPONENT Applications)
#endif()





# --- system dependent installation ---------
if(UNIX)
    if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
        install( FILES ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns
            DESTINATION ${destination_bundle}/Contents/Resources/
        )

        set(plugin_dest_dir ${destination_bundle}/Contents/PlugIns)
        install(DIRECTORY "$ENV{QTDIR}/plugins/platforms" DESTINATION ${plugin_dest_dir} COMPONENT Runtime)

        set(fixup_path @rpath)

        # handling the case when cmake prefix path contains more than one entry
        list(LENGTH "${CMAKE_PREFIX_PATH}" len)
        list(GET "${CMAKE_PREFIX_PATH}" 0 cmake_prefix_path1)
        if(len EQUAL 2)
        list(GET "${CMAKE_PREFIX_PATH}" 1 cmake_prefix_path2)
        endif()

        configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/FixAppleBundle.cmake.in ${destination_runtime_configs}/FixAppleBundle.cmake @ONLY)
        install(SCRIPT ${destination_runtime_configs}/FixAppleBundle.cmake COMPONENT Runtime)
    elseif(NOT BUILD_DEBIAN)
        # creating link to BornAgain gui in bin directory
        install(CODE "
        execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink
        \"../libexec/${destination_suffix}/BornAgain\" \"bornagain\"
        WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
        " COMPONENT Runtime)

    endif()
endif()


