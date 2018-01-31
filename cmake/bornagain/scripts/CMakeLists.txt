# to show directory in Qt creator project tree
FILE(GLOB_RECURSE ScriptFiles "*.*")
list(REMOVE_ITEM ScriptFiles "$CMakeLists.txt")
add_custom_target(scripts SOURCES ${ScriptFiles})
