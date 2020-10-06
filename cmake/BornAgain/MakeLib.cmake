function(MakeLib name lib tmpdir)

    if(BORNAGAIN_PYTHON)
        list(APPEND source_files "${AUTO_DIR}/lib${lib}_wrap.cpp")
    endif()
    add_library(${lib} SHARED ${source_files})
    set_target_properties(${lib} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
    set(${lib}_LIBRARY_TYPE SHARED)

    if(BORNAGAIN_PYTHON)
        SwigLib(${name} ${lib} ${tmpdir})
    endif(BORNAGAIN_PYTHON)

endfunction()
