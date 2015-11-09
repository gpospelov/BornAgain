if(POLICY CMP0020)
cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
cmake_policy(SET CMP0043 NEW)
endif()
if(POLICY CMP0028)
cmake_policy(SET CMP0028 OLD)
endif()

set(executable_name crashhandler)


file(GLOB source_files
    "*.cpp"
)

file(GLOB include_files
    "*.h"
)

#set(ui_files
#    crashhandlerdialog.ui
#)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#qt5_wrap_ui(UI_HDRS ${ui_files})


add_executable(${executable_name} ${source_files} ${include_files} ${UI_HDRS})

qt5_use_modules(${executable_name} Widgets Core Gui Script Designer PrintSupport)



