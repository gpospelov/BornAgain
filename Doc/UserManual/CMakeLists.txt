project(BornAgainManual NONE)

# version is read from main directory,
# and written to cmake/scripts/UserManualVersion.tex.in
include( ../../VERSION.cmake )

if(POLICY CMP0046)
cmake_policy(SET CMP0046 NEW)
endif()

set(PDFLATEX_COMPILER xelatex)

set(LATEX_COMPILER_FLAGS "-interaction=errorstopmode" CACHE STRING "Flags passed to latex." )

if(BORNAGAIN_USERMANUAL)
    # --- configure a header file to pass CMake settings to the source code
    configure_file(
        "${CMAKE_SOURCE_DIR}/cmake/scripts/UserManualVersion.tex.in"
        "${CMAKE_SOURCE_DIR}/Doc/UserManual/UserManualVersion.tex"
    )
    include(${CMAKE_MODULE_PATH}/UseLATEX.cmake)

else()
    # to compile in standalone mode
    configure_file(
        "${CMAKE_SOURCE_DIR}/../../cmake/scripts/UserManualVersion.tex.in"
        "${CMAKE_SOURCE_DIR}/../../Doc/UserManual/UserManualVersion.tex"
    )
    include(../../cmake/modules/UseLATEX.cmake)

endif()

file(GLOB tex_inputs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tex)
file(GLOB fig_inputs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} fig/[a-z]*/*)

ADD_LATEX_DOCUMENT(BornAgainManual.tex
    INPUTS ${tex_inputs} ${fig_inputs}
    BIBFILES jw7.bib
    USE_INDEX
    USE_NOMENCL
    DEFAULT_PDF
)
