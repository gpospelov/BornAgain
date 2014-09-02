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

if(APPLE)
  add_executable(${executable_name} MACOSX_BUNDLE main.cpp)
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
  add_executable(${executable_name} main.cpp)

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
endif(APPLE)

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
IF(APPLE)
  set(plugin_dest_dir ${INBUNDLE}/Contents/MacOS/plugins)
  set(qtconf_dest_dir ${INBUNDLE}/Contents/Resources)
  set(APPS "\${CMAKE_INSTALL_PREFIX}/${INBUNDLE}")

  message("PYTHON_LIBRARY: ${PYTHON_LIBRARY}")

  get_filename_component(ManhattanStyle_LIBRARY_DIR "${ManhattanStyle_LIBRARY}" REALPATH)
  get_filename_component(qcustomplot_LIBRARY_DIR "${qcustomplot_LIBRARY}" REALPATH)
  get_filename_component(qtpropertybrowser_LIBRARY_DIR "${qtpropertybrowser_LIBRARY}" REALPATH)
  get_filename_component(Boost_Real_LIBRARY_DIR "${Boost_LIBRARY_DIR}" REALPATH)
  get_filename_component(PYTHON_LIBRARY_DIR "${PYTHON_REAL_LIBRARY}" PATH)

  message("PYTHON_LIBRARY_DIR: ${PYTHON_LIBRARY_DIR}")

#  set(DEPLIBS
#    ${ManhattanStyle_LIBRARY}
#    ${qcustomplot_LIBRARY}
#    ${qtpropertybrowser_LIBRARY}
#    ${PYTHON_LIBRARY}
#    ${PYTHON_REAL_LIBRARY}
#    ${Boost_LIBRARIES}
#    ${BornAgainCore_LIBRARY}
#    ${BornAgainFit_LIBRARY}
#    ${BornAgainGUI_LIBRARY}
#  )


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
Plugins = MacOS/plugins
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
endif(APPLE)

