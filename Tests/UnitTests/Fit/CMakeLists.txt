############################################################################
# Fit unit tests
############################################################################

set(test UnitTestFit)
set(libs BornAgainCore BornAgainFit)

ADD_GTEST(${test} "Kernel" "${libs}" 0)

