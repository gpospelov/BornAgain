set(library_name BornAgainQtAddOn PARENT_SCOPE)

add_subdirectory(qt-manhattan-style)
add_subdirectory(qcustomplot)
add_subdirectory(qtpropertybrowser)

message(DEBUG " 1 ---> QtAddOn_INC_DIR: ${BornAgainQtAddOn_INCLUDE_DIRS}.")
set(${library_name}_INCLUDE_DIRS ${${library_name}_INCLUDE_DIRS} PARENT_SCOPE)
set(${library_name}_LIBRARY ${${library_name}_LIBRARY} PARENT_SCOPE)
