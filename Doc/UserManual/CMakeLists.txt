cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

project(UserManual NONE)

# Please define the UserManual Version here only. 
# It will automatically propagate to the latex file.
set(UM_VERSION_MAJOR 0)
set(UM_VERSION_MINOR 1)
set(UM_VERSION_PATCH 1)

# --- configure a header file to pass CMake settings to the source code
configure_file(
  "${CMAKE_SOURCE_DIR}/Doc/UserManual/UserManual.tex.in"
  "${CMAKE_SOURCE_DIR}/Doc/UserManual/UserManual-${UM_VERSION_MAJOR}.${UM_VERSION_MINOR}.${UM_VERSION_PATCH}.tex"
)


set(LATEX_COMPILER_FLAGS
"-interaction=nonstopmode --enable-write18"
CACHE STRING "Flags passed to latex."
)

include(${CMAKE_MODULE_PATH}/UseLATEX.cmake)

# 
# Find LaTeX
#
#find_package(LATEX)

#find_program(PDFLATEX COMPILER pdflatex)
#find_program(BIBTEX_COMPILER bibtex)

set(UM_IMAGES
	Figures/basic_architecture.eps
	Figures/Manual_ex1.eps
	Figures/multilayer3d2.eps
	Figures/multilayer3d3.eps
	Figures/multilayer3d.eps
	Figures/results2_2.png
)

ADD_LATEX_DOCUMENT(UserManual-${UM_VERSION_MAJOR}.${UM_VERSION_MINOR}.${UM_VERSION_PATCH}.tex
	INPUTS Disclaimer.tex Introduction.tex QuickStart.tex Installation.tex SimulationExamples.tex SoftwareArchitecture.tex
	BIBFILES jw7.bib 
	IMAGES ${UM_IMAGES}
	DEFAULT_SAFEPDF
)


