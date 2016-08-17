# SetupCoverage.cmake
#
# description: sets up code coverage custom target
#
# copyright: 2016 scientific computing group, Forshungszentrum Juelich GmbH
#
# license: see LICENSE
#

set(coverage_ignore_dirs "'/usr/*'")
list(APPEND coverage_ignore_dirs "'*/auto/*'")
list(APPEND coverage_ignore_dirs "'*/ThirdParty/*'")
list(APPEND coverage_ignore_dirs "'*/build/*'")
list(APPEND coverage_ignore_dirs "'*/GUI/externals/*'")

add_coverage_target(coverage "${coverage_ignore_dirs}")
