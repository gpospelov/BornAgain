# This CMakeLists.txt is not actively maintained;
# we usually do not use CMake to build the manual.

project(BornAgainManual NONE)

if(POLICY CMP0046)
cmake_policy(SET CMP0046 NEW)
endif()

set(PDFLATEX_COMPILER xelatex)

set(LATEX_COMPILER_FLAGS "-interaction=errorstopmode" CACHE STRING "Flags passed to latex." )

if(BORNAGAIN_USERMANUAL)
    include(UseLATEX)

else()
    # to compile in standalone mode
    include("../../cmake/modules/UseLATEX.cmake")

endif()

file(GLOB tex_inputs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tex)
file(GLOB fig_inputs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} fig/[a-z]*/*)

ADD_LATEX_DOCUMENT(
    BornAgainManual.tex
    INPUTS ${tex_inputs} ${fig_inputs}
    BIBFILES jw7.bib
    USE_INDEX
    USE_NOMENCL
    DEFAULT_PDF
)
