
# -----------------------------------------------------------------------------
# BORNAGAIN_EXECUTABLE( executable LOCATION location LIBRARIES libraries )
# -----------------------------------------------------------------------------
function(BORNAGAIN_EXECUTABLE executable)
    cmake_parse_arguments(ARG "" "LOCATION" "LIBRARIES" "" ${ARGN})
    file(GLOB source_files ${ARG_LOCATION}/*.cpp)
    add_executable(${executable} ${source_files})
    target_link_libraries(${executable} ${ARG_LIBRARIES})
endfunction()
