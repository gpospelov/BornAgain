add_subdirectory(qt-manhattan-style)
add_subdirectory(qcustomplot)
add_subdirectory(qtpropertybrowser)

set(QtAddOn_INCLUDE_DIRS
    ${ManhattanStyle_INCLUDE_DIRS}
    ${qcustomplot_INCLUDE_DIRS}
    ${qtpropertybrowser_INCLUDE_DIRS}
    PARENT_SCOPE)

set(QtAddOn_LIBRARIES
    ${ManhattanStyle_LIBRARY}
    ${qcustomplot_LIBRARY}
    ${qtpropertybrowser_LIBRARY}
    PARENT_SCOPE)
