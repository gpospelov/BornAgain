# Executable: darefl
set(executable_name darefl)

add_subdirectory(darefl)

add_executable(${executable_name} main.cpp)
target_link_libraries(${executable_name} PRIVATE dareflcore)
