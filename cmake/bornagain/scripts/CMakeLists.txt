# to show directory in Qt creator project tree
FILE(GLOB_RECURSE ScriptFiles "*.*")
add_custom_target(scripts SOURCES ${ScriptFiles})
