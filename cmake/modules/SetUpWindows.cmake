set(BORNAGAIN_ARCHITECTURE win32)
set(BORNAGAIN_PLATFORM win32)

add_definitions(-DEIGEN_DONT_ALIGN_STATICALLY=1)
message(STATUS "Disabling static align for Eigen")

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nologo /EHsc -I${CMAKE_SOURCE_DIR}/Core/Tools/inc -FIw32pragma.h")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mincoming-stack-boundary=2 -Wno-unused-local-typedefs -Wno-attributes")
endif()

