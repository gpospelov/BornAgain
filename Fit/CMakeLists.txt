############################################################################
# CMakeLists.txt file for building libBornAgainFit library
############################################################################

set(LIBRARY_NAME BornAgainFit)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Factory/inc
)

file(GLOB BornAgainFit_SRC
    "Factory/src/*.cpp"
    "Factory/src/*.cxx"
)

if(BORNAGAIN_PYTHON)
    file(GLOB BornAgainFit_PythonAPI "PythonAPI/src/*.cpp")
    list(APPEND BornAgainFit_SRC ${BornAgainFit_PythonAPI})
    include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/PythonAPI/inc
    )
endif()

add_library(
    ${LIBRARY_NAME}
    SHARED
    ${BornAgainFit_SRC}
)
set_Target_properties(${LIBRARY_NAME} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
set(${LIBRARY_NAME}_LIBRARY_TYPE SHARED)

#target_link_libraries(${LIBRARY_NAME} ${FFTW_LIBRARY}) 
#target_link_libraries(${LIBRARY_NAME} ${Boost_LIBRARIES}) 
#target_link_libraries(${LIBRARY_NAME} ${GSL_LIBRARIES}) 
#target_link_libraries(${LIBRARY_NAME} ${PYTHON_LIBRARIES}) 

include_directories(${BornAgainCore_INCLUDE_DIRS})
target_link_libraries(${LIBRARY_NAME} ${BornAgainCore_LIBRARY}) 
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES}) 

