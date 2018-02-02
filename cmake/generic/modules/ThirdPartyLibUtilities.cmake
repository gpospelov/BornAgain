# Utilities for treating certain third-party libraries/headers
# as system ones.
# include_as_system_directory mutes all warnings from particular
# directory which arise during compilation

function(include_as_system_directory DIR)
    if(NOT DIR)
        message(FATAL_ERROR
                "include_as_system_directory:
                directory is undefined"
               )
    endif(NOT DIR)
    include_directories(SYSTEM "${DIR}")
endfunction(include_as_system_directory)
