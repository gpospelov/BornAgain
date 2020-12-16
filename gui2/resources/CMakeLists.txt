set(CMAKE_AUTORCC ON)

target_sources(${library_name} PRIVATE
    icons.qrc
    resources.h
)

target_include_directories(${library_name} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
