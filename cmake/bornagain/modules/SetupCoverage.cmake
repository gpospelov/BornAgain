# SetupCoverage.cmake
#
# description: sets up code coverage custom target
#
# copyright: 2016 Scientific Computing Group, Forschungszentrum Juelich GmbH
#
# license: see LICENSE

set(coverage_ignore_dirs "'/usr/*'")
list(APPEND coverage_ignore_dirs "'*/auto/*'")
list(APPEND coverage_ignore_dirs "'*/Tests/*'")
list(APPEND coverage_ignore_dirs "'*/ThirdParty/*'")
list(APPEND coverage_ignore_dirs "'*/build/*'")

set(html_dir ${CMAKE_CURRENT_BINARY_DIR}/coverage)
file(MAKE_DIRECTORY ${html_dir})

add_coverage_target(coverage "${coverage_ignore_dirs}" ${html_dir})
