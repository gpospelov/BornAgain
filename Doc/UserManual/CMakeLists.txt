cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

project(UserManual NONE)

# user manual version number will be automatically propagated into tes
set(UM_VERSION_MAJOR 0)
set(UM_VERSION_MINOR 2)
set(UM_VERSION_PATCH 1)


set(LATEX_COMPILER_FLAGS
"-interaction=nonstopmode --enable-write18"
CACHE STRING "Flags passed to latex."
)

if(BORNAGAIN_MAN)
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


set(UM_IMAGES
    Figures/toyfit_expdata.eps
    Figures/toyfit_simdata.eps
    Figures/toyfit_chi2_p12.eps
    Figures/toyfit_chi2_p23.eps
    Figures/minimization_workflow.eps
    Figures/Manual_ex1.eps
    Figures/multilayer3d3.eps
    Figures/basic_architecture.eps
)


file(GLOB tex_inputs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tex)

ADD_LATEX_DOCUMENT(UserManual.tex
    INPUTS ${tex_inputs}
    BIBFILES jw7.bib 
    IMAGES ${UM_IMAGES}
    DEFAULT_SAFEPDF
)


