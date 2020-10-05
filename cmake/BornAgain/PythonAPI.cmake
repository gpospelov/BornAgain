# Configure and install the Swig runtime, the BornAgain Python module, and more





# Install bornagain/__init__.py and utilites
install(DIRECTORY "${CMAKE_BINARY_DIR}/lib/bornagain/"
        DESTINATION "${destination_libexec}/bornagain"
        COMPONENT Libraries
        FILES_MATCHING PATTERN "*.py"
        PATTERN "__pycache__" EXCLUDE)
