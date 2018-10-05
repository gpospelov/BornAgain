############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

# testing fitting via FitSuite
add_subdirectory(FitSuite)

# testing fitting via FitObjective
add_subdirectory(FitObjective)

# testing standalone fitting of arbitrary objective functions
add_subdirectory(Minimizer)

