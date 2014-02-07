cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

project(UserManual NONE)

# user manual version number will be automatically propagated into tes
set(UM_VERSION_MAJOR 0)
set(UM_VERSION_MINOR 2)
set(UM_VERSION_PATCH 2)


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
    Figures/AnisoPyramid2dxy.eps
    Figures/AnisoPyramid2dxz.eps
    Figures/AnistropicPyramid3d.eps
    Figures/Box2dxy.eps
    Figures/Box2dxz.eps
    Figures/Box3d.eps
    Figures/Cone2dxy.eps		
    Figures/Cone2dxz.eps		
    Figures/Cone3d.eps
    Figures/Sphere2dxy.eps
    Figures/Sphere2dxz.eps
    Figures/Sphere3d.eps
    Figures/Spheroid2dxy.eps
    Figures/Spheroid2dxz.eps
    Figures/Spheroid3d.eps		
    Figures/Cone62dxy.eps
    Figures/Cone62dxz.eps
    Figures/Cone63d.eps
    Figures/Cuboctahedron2dxy.eps
    Figures/Cuboctahedron2dxz.eps
    Figures/Cuboctahedron3d.eps
    Figures/Cylinder2dxy.eps
    Figures/Cylinder2dxz.eps
    Figures/Cylinder3d.eps			
    Figures/EllipsoidalCylinder2dxy.eps	
    Figures/EllipsoidalCylinder2dxz.eps	
    Figures/EllipsoidalCylinder3d.eps
    Figures/FullSphere2dxy.eps		    
    Figures/FullSphere2dxz.eps		
    Figures/figffparallel.eps
    Figures/FullSphere3d.eps		
    Figures/figffprism3.eps
    Figures/FullSpheroid2dxy.eps
    Figures/FullSpheroid2dxz.eps		
    Figures/figffpyramid.eps
    Figures/FullSpheroid3d.eps		
    Figures/figffripple1.eps
    Figures/HemiEllipsoid2dxy.eps		
    Figures/figffripple2.eps
    Figures/HemiEllipsoid2dxz.eps		
    Figures/figffsphere.eps
    Figures/HemiEllipsoid3d.eps				            
    Figures/Parallelepiped2dxy.eps	
    Figures/Parallelepiped2dxz.eps	
    Figures/Parallelepiped3d.eps	
    Figures/Prism32dxy.eps		
    Figures/Prism32dxz.eps		
    Figures/Prism33d.eps		
    Figures/Prism62dxy.eps	
    Figures/Prism62dxz.eps
    Figures/Prism63d.eps
    Figures/Pyramid2dxy.eps
    Figures/Pyramid2dxz.eps
    Figures/Pyramid3d.eps		
    Figures/Ripple12dxy.eps
    Figures/Ripple12dyz.eps	
    Figures/Ripple13d.eps
    Figures/Ripple22dxy.eps
    Figures/Ripple22dyz.eps
    Figures/Ripple23d.eps
    Figures/figffcone6.eps
    Figures/Tetrahedron2dxz.eps
    Figures/Tetrahedron2dxy.eps
    Figures/Tetrahedron3d.eps
    Figures/figffanisopyramid.eps
    Figures/figffbox.eps
    Figures/figffhemiellips.eps
    Figures/figfftetrahedron.eps
    Figures/figffcone.eps
    Figures/figffcuboctah.eps
    Figures/figffcylinder.eps
    Figures/figffellipscylinder.eps
    Figures/figfffsphere.eps
    Figures/figfffspheroid.eps
    Figures/figfffullsphere.eps
    Figures/figffspheroid.eps
    Figures/figffprism6.eps
)


file(GLOB tex_inputs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tex)

ADD_LATEX_DOCUMENT(UserManual.tex
    INPUTS ${tex_inputs}
    BIBFILES jw7.bib 
    IMAGES ${UM_IMAGES}
    DEFAULT_SAFEPDF
)


