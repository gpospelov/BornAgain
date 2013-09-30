cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(UserManual NONE)

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

ADD_LATEX_DOCUMENT(UserManual.tex
	INPUTS Disclaimer.tex Introduction.tex QuickStart.tex Installation.tex SimulationExamples.tex SoftwareArchitecture.tex
	BIBFILES jw7.bib 
	IMAGES ${UM_IMAGES}
	DEFAULT_SAFEPDF
)


