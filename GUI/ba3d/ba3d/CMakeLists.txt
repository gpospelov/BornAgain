get_filename_component (lib ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# --- source, include and resource files ---
file (GLOB_RECURSE source_files *.cpp)
file (GLOB_RECURSE include_files *.h)

set(resource_files
    "shaders.qrc"
    )
qt5_add_resources(RC_SHADERS ${resource_files})

add_library (${lib} STATIC ${source_files} ${RC_SHADERS})

target_link_libraries (${lib}
  Qt5::Core Qt5::Widgets Qt5::OpenGL
)
