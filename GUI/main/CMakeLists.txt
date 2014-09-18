cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)
if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
cmake_policy(SET CMP0043 NEW)
endif()
if(POLICY CMP0028)
cmake_policy(SET CMP0028 OLD)
endif()

set(executable_name BornAgain)

include_directories(
    ${BornAgainGUI_INCLUDE_DIRS}
    ${ManhattanStyle_INCLUDE_DIRS}
    ${GSL_INCLUDE_DIR}
)

set(source_files
    main.cpp
    crashhandlersetup.cpp
    stacktracesetup.cpp
)

if(BORNAGAIN_CRASHHANDLER)
#    list(APPEND source_files crashhandlersetup.cpp stacktracesetup.cpp)
#    list(APPEND include_files crashhandlersetup.h stacktracesetup.h)
    list(APPEND source_files stacktracesetup.cpp)
    list(APPEND include_files stacktracesetup.h)
endif()


if(APPLE AND CREATE_BUNDLE)
  add_executable(${executable_name} MACOSX_BUNDLE ${source_files} ${include_files})
  get_filename_component(PYTHON_REAL_LIBRARY "${PYTHON_LIBRARY}" REALPATH)
  add_library(Python SHARED IMPORTED)
  set_property(TARGET Python PROPERTY IMPORTED_LOCATION ${PYTHON_REAL_LIBRARY})

  target_link_libraries(${executable_name}
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    ${PYTHON_LIBRARY}
    ${Boost_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    ${BornAgainFit_LIBRARY}
    ${BornAgainGUI_LIBRARY}
    Python
  )
else()
  add_executable(${executable_name} ${source_files} ${include_files})

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
  set(plugin_dest_dir ${INBUNDLE}/Contents/PlugIns)
  set(qtconf_dest_dir ${INBUNDLE}/Contents/Resources)
  set(APPS "\${CMAKE_INSTALL_PREFIX}/${INBUNDLE}")

#  message("PYTHON_LIBRARY: ${PYTHON_LIBRARY}")

  get_filename_component(ManhattanStyle_LIBRARY_DIR "${ManhattanStyle_LIBRARY}" REALPATH)
  get_filename_component(qcustomplot_LIBRARY_DIR "${qcustomplot_LIBRARY}" REALPATH)
  get_filename_component(qtpropertybrowser_LIBRARY_DIR "${qtpropertybrowser_LIBRARY}" REALPATH)
  get_filename_component(Boost_Real_LIBRARY_DIR "${Boost_LIBRARY_DIR}" REALPATH)
  get_filename_component(PYTHON_LIBRARY_DIR "${PYTHON_REAL_LIBRARY}" PATH)

#  message("PYTHON_LIBRARY_DIR: ${PYTHON_LIBRARY_DIR}")

  set(DIRS
    ${ManhattanStyle_LIBRARY_DIR}
    ${qcustomplot_LIBRARY_DIR}
    ${qtpropertybrowser_LIBRARY_DIR}
    ${PYTHON_LIBRARY_DIR}
    ${Boost_Real_LIBRARY_DIR}
    "${CMAKE_BINARY_DIR}/lib"
    "$ENV{QTDIR}"
    "$ENV{QTDIR}/plugins"
  )


  install (TARGETS ${executable_name}
    BUNDLE DESTINATION  . COMPONENT Applications
    RUNTIME DESTINATION ${destination_bin} COMPONENT Runtime)

  install(DIRECTORY "$ENV{QTDIR}/plugins/platforms" DESTINATION ${plugin_dest_dir} COMPONENT Runtime)

  set(qtconf_text "
[Paths]
Plugins = PlugIns
  ")

  install(CODE "
    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"${qtconf_text}\")
    " COMPONENT Runtime)

  install(CODE "
    file(GLOB_RECURSE QTPLUGINS
      \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
    set(BU_CHMOD_BUNDLE_ITEMS True)
    set(BU_COPY_FULL_FRAMEWORK_CONTENTS False)
    include(${CMAKE_MODULE_PATH}/BABundleUtilities.cmake)
    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
    " COMPONENT Runtime)

else()
  install (TARGETS ${executable_name} DESTINATION ${destination_bin} COMPONENT Applications)
endif(APPLE AND CREATE_BUNDLE)

