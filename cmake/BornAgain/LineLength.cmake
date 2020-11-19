set(SRC_LEN_LIM 100) # maximum line length of code written by MLZ-SCG
set(WEB_LEN_LIM 85) # maximum line length of code for display in web docs

if(NOT MSVC)

    set(LINECOUNT
        ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/devtools/line-count/check-line-length.py)

    foreach(dir ${AllComponents})
        file(GLOB_RECURSE src1 ${dir}/*.cpp)
        file(GLOB_RECURSE src2 ${dir}/*.h)
        add_test(NAME "LineLength.Cpp.${dir}"
            COMMAND ${LINECOUNT} ${SRC_LEN_LIM} ${src1} ${src2})
    endforeach()

    foreach(dir ${AllComponents})
        file(GLOB_RECURSE src1 ${dir}/*CMakeLists.txt)
        add_test(NAME "LineLength.CMake.${dir}"
            COMMAND ${LINECOUNT} ${SRC_LEN_LIM} ${src1})
    endforeach()

    file(GLOB sources "${PY_EXAMPLES_DIR}/*/ex*/*.py")
    add_test(NAME "LineLength.PyExamples"
        COMMAND ${LINECOUNT} ${WEB_LEN_LIM} ${sources})

endif()
