get_filename_component (lib ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file (GLOB_RECURSE files *)
add_library (${lib} STATIC ${files})

target_link_libraries (${lib}
  Qt5::Core Qt5::Widgets Qt5::OpenGL
)

# eof
