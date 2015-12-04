###############################################################################
# Builds BornAgain/GUI main executable
###############################################################################
set(executable_name BornAgain)

# -----------------------------------------------------------------------------
# source files
# -----------------------------------------------------------------------------
include_directories(
    ${BornAgainGUI_INCLUDE_DIRS}
    ${ManhattanStyle_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
)
set(source_files main.cpp appoptions.cpp)
set(include_files appoptions.h)


# -----------------------------------------------------------------------------
# Qt configuration
# -----------------------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


# -----------------------------------------------------------------------------
# executable icons
# -----------------------------------------------------------------------------
if(WIN32)
    set(system_addons bornagain.rc)
    if(NOT win32_console)
        set(executable_options WIN32)
    endif()
endif()

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE BornAgain.icns)
    set_source_files_properties(${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns
        PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    if(BORNAGAIN_APPLE_BUNDLE)
        set(executable_options MACOSX_BUNDLE)
    endif()
endif()


# -----------------------------------------------------------------------------
# executable
# -----------------------------------------------------------------------------
add_executable(${executable_name}
               ${executable_options}
               ${source_files}
               ${include_files}
               ${system_addons})


# -----------------------------------------------------------------------------
# dependencies
# -----------------------------------------------------------------------------
target_link_libraries(${executable_name} ${BornAgainGUI_LIBRARY})


# -----------------------------------------------------------------------------
# extra target properties
# -----------------------------------------------------------------------------
if(WIN32)
    set_target_properties( ${executable_name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup" )
    if(win32_console)
        set_target_properties( ${executable_name} PROPERTIES COMPILE_DEFINITIONS "_CONSOLE" )
    endif()
endif()

if(APPLE)
    set(MACOSX_BUNDLE_IDENTIFIER "org.bornagainproject.BornAgain")
    configure_file("${CMAKE_SOURCE_DIR}/cmake/scripts/MacOSXBundleInfo.plist.in"
        "${destination_runtime_configs}/Info.plist" @ONLY)

    set_target_properties(${executable_name}
        PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${destination_runtime_configs}/Info.plist)

    set(link_flags "-Wl,-rpath,@loader_path/../Frameworks/ -Wl,-rpath,@loader_path/../lib/BornAgain-${BornAgain_VERSION_MAJOR}.${BornAgain_VERSION_MINOR}/")
    set_target_properties(${executable_name} PROPERTIES LINK_FLAGS ${link_flags})
endif()


# -----------------------------------------------------------------------------
# installation section
# -----------------------------------------------------------------------------
if(BORNAGAIN_APPLE_BUNDLE)
    set(executable_destination BUNDLE DESTINATION  ".")
else()
    set(executable_destination DESTINATION ${destination_gui})
endif()
install (TARGETS ${executable_name} ${executable_destination} COMPONENT Applications)

set(image_files
    ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.ico
    ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns
    ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_48x48.png
    ${CMAKE_SOURCE_DIR}/GUI/coregui/images/BornAgain_64x64.png)
install (FILES ${image_files} DESTINATION ${destination_images} COMPONENT Applications)


# -----------------------------------------------------------------------------
# system dependent installation
# -----------------------------------------------------------------------------
if(UNIX)
    if(BORNAGAIN_APPLE_BUNDLE)
        install( FILES ${CMAKE_SOURCE_DIR}/GUI/main/BornAgain.icns
            DESTINATION ${destination_bundle}/Contents/Resources/
        )
        install( FILES ${CMAKE_SOURCE_DIR}/cmake/scripts/qt.conf
            DESTINATION ${destination_bundle}/Contents/Resources/
        )
        configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/FixAppleBundle.cmake.in
                       ${destination_runtime_configs}/FixAppleBundle.cmake @ONLY)
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


