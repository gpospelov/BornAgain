############################################################################
# CMakeLists.txt file for building libtiff library
############################################################################
if(POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
endif()

set(library_name tiff)

find_library(M_LIBRARY m)

set(libtiff_source_dir libtiff-4.0.6)



#configure_file(${libtiff_source_dir}/tif_config.h.cmake.in
#               ${CMAKE_CURRENT_BINARY_DIR}/tif_config.h
#               @ONLY)
#configure_file(${libtiff_source_dir}/tiffconf.h.cmake.in
#               ${CMAKE_CURRENT_BINARY_DIR}/tiffconf.h
#               @ONLY)


set(source_files
    ${libtiff_source_dir}/tif_aux.c
    ${libtiff_source_dir}/tif_close.c
    ${libtiff_source_dir}/tif_codec.c
    ${libtiff_source_dir}/tif_color.c
    ${libtiff_source_dir}/tif_compress.c
    ${libtiff_source_dir}/tif_dir.c
    ${libtiff_source_dir}/tif_dirinfo.c
    ${libtiff_source_dir}/tif_dirread.c
    ${libtiff_source_dir}/tif_dirwrite.c
    ${libtiff_source_dir}/tif_dumpmode.c
    ${libtiff_source_dir}/tif_error.c
    ${libtiff_source_dir}/tif_extension.c
    ${libtiff_source_dir}/tif_fax3.c
    ${libtiff_source_dir}/tif_fax3sm.c
    ${libtiff_source_dir}/tif_flush.c
    ${libtiff_source_dir}/tif_getimage.c
    ${libtiff_source_dir}/tif_luv.c
    ${libtiff_source_dir}/tif_lzw.c
    ${libtiff_source_dir}/tif_next.c
    ${libtiff_source_dir}/tif_open.c
    ${libtiff_source_dir}/tif_packbits.c
    ${libtiff_source_dir}/tif_pixarlog.c
    ${libtiff_source_dir}/tif_predict.c
    ${libtiff_source_dir}/tif_print.c
    ${libtiff_source_dir}/tif_read.c
    ${libtiff_source_dir}/tif_strip.c
    ${libtiff_source_dir}/tif_swab.c
    ${libtiff_source_dir}/tif_thunder.c
    ${libtiff_source_dir}/tif_tile.c
    ${libtiff_source_dir}/tif_version.c
    ${libtiff_source_dir}/tif_warning.c
    ${libtiff_source_dir}/tif_write.c
    ${libtiff_source_dir}/tif_zip.c
    ${libtiff_source_dir}/tif_stream.cxx
)

set(include_files
    tif_config.h
    tiffconf.h
)

if(WIN32)
    list(APPEND source_files ${libtiff_source_dir}/tif_win32.c)
else()
    list(APPEND source_files ${libtiff_source_dir}/tif_unix.c)
endif()


#set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${libtiff_source_dir})
set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${include_dirs})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_POINTER_SIZE=${CMAKE_SIZEOF_VOID_P}")
if(MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_CC_MSVC")
endif()
if(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBA_OS_MAC")
endif()


# creating library
add_library(
    ${library_name}
    SHARED
    ${source_files} ${include_files}
)
set_Target_properties(${library_name} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${library_name}_LIBRARY_TYPE SHARED)

# exposing paths for library users
#set(${library_name}_INCLUDE_DIRS ${include_dirs} PARENT_SCOPE)
#set(${library_name}_LIBRARY ${library_name} PARENT_SCOPE)
set(TIFF_INCLUDE_DIR ${include_dirs} CACHE INTERNAL "")
set(TIFF_LIBRARIES ${library_name} CACHE INTERNAL "")

if(NOT MSVC)
target_link_libraries(${library_name} ${M_LIBRARY})
endif()


