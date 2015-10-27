# Compilation of ThirdParty dependencies

if(BORNAGAIN_TIFF_SUPPORT)
    if(NOT TIFF_FOUND)
        message(INFO "aaa adding tiff")
        add_subdirectory(libtiff)
    endif()
endif()

add_subdirectory(gtest)
add_subdirectory(RootMinimizers)
