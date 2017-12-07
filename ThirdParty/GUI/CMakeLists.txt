add_subdirectory(qt-manhattan-style)
add_subdirectory(qcustomplot)

set(QtAddOn_INCLUDE_DIRS
    ${ManhattanStyle_INCLUDE_DIRS}
    ${qcustomplot_INCLUDE_DIRS}
    PARENT_SCOPE)

set(QtAddOn_LIBRARIES
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    PARENT_SCOPE)
