set(lib ba3d)

file (GLOB_RECURSE source_files *.cpp)

set(CMAKE_AUTORCC ON)
qt5_add_resources(RC_SHADERS "shaders.qrc")

add_library (${lib} STATIC ${source_files} ${RC_SHADERS})

target_link_libraries (${lib} Qt5::Core Qt5::Widgets Qt5::OpenGL)
