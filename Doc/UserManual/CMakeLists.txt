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
    Figures/AnistropicPyramid3d.png
    Figures/Box2dxy.eps
    Figures/Box2dxz.eps
    Figures/Box3d.png
    Figures/Cone2dxy.eps		
    Figures/Cone2dxz.eps		
    Figures/Cone3d.png
    Figures/Sphere2dxy.eps
    Figures/Sphere2dxz.eps
    Figures/Sphere3d.png
    Figures/Spheroid2dxy.eps
    Figures/Spheroid2dxz.eps
    Figures/Spheroid3d.png		
    Figures/Cone62dxy.eps
    Figures/Cone62dxz.eps
    Figures/Cone63d.png
    Figures/Cuboctahedron2dxy.eps
    Figures/Cuboctahedron2dxz.eps
    Figures/Cuboctahedron3d.png
    Figures/Cylinder2dxy.eps
    Figures/Cylinder2dxz.eps
    Figures/Cylinder3d.png			
    Figures/EllipsoidalCylinder2dxy.eps	
    Figures/EllipsoidalCylinder2dxz.eps	
    Figures/EllipsoidalCylinder3d.png
    Figures/FullSphere2dxy.eps		    
    Figures/FullSphere2dxz.eps
    Figures/FullSphere3d.png	
    Figures/FullSpheroid2dxy.eps
    Figures/FullSpheroid2dxz.eps		
    Figures/FullSpheroid3d.png		
    Figures/HemiEllipsoid2dxy.eps		
    Figures/HemiEllipsoid2dxz.eps		
    Figures/HemiEllipsoid3d.png				            
    Figures/Prism32dxy.eps		
    Figures/Prism32dxz.eps		
    Figures/Prism33d.png		
    Figures/Prism62dxy.eps	
    Figures/Prism62dxz.eps
    Figures/Prism63d.png
    Figures/Pyramid2dxy.eps
    Figures/Pyramid2dxz.eps
    Figures/Pyramid3d.png		
    Figures/Ripple12dxy.eps
    Figures/Ripple12dyz.eps	
    Figures/Ripple13d.png
    Figures/Ripple22dxy.eps
    Figures/Ripple22dyz.eps
    Figures/Ripple23d.png
    Figures/Tetrahedron2dxz.eps
    Figures/Tetrahedron2dxy.eps
    Figures/Tetrahedron3d.png
    Figures/figffanisopyramid.pdf
    Figures/figffbox.pdf
    Figures/figffcone.pdf
    Figures/figffcone6.pdf
    Figures/figffcylinder.pdf
    Figures/figffcuboctah.pdf
    Figures/figffellipscylinder.pdf
    Figures/figffhemiellips.pdf
    Figures/figfffsphere.pdf
    Figures/figfffspheroid.pdf
    Figures/figffpyramid.pdf
    Figures/figffprism3.pdf
    Figures/figffprism6.pdf
    Figures/figffripple1.pdf
    Figures/figffripple2.pdf
    Figures/figffsphere.pdf
    Figures/figffspheroid.pdf
    Figures/figfftetrahedron.pdf
    Figures/drawingDWBA.eps
    Figures/drawingDWBAburied.eps
    Figures/ffspheroidBA.pdf
    Figures/ffspheroidDWBA.pdf
    Figures/drawingDepthParticle.eps
    Figures/figIntBuriedPart.pdf
    Figures/CoreShellParallPyr.pdf
    Figures/CoreShellParallPyrxy.eps
    Figures/CoreShellParallPyrxz.eps
    Figures/HSphere_NoInterf.pdf
    Figures/HSphere_1DDL.pdf
    Figures/1DGrating.eps
    Figures/2Dlattice.eps
    Figures/1Dparacrystal.eps
    Figures/HSphere_2Dlattice.pdf
    Figures/HSphere_2DDL.pdf
)


file(GLOB tex_inputs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.tex)

ADD_LATEX_DOCUMENT(UserManual.tex
    INPUTS ${tex_inputs}
    BIBFILES jw7.bib 
    IMAGES ${UM_IMAGES}
    DEFAULT_SAFEPDF
)


