cmake_minimum_required(VERSION 2.8)
 
project(CylindersAndPrisms)

add_executable(CylindersAndPrisms CylindersAndPrisms.cpp)

# BornAgain include dir
set (BornAgain_Include_Dir "/usr/include/BornAgain")
set (Eigen3_Include_Dir "/usr/include/eigen3")
set (ROOT_Include_Dir "/usr/include/root")

include_directories (
	${BornAgain_Include_Dir}
	${Eigen3_Include_Dir}
	${ROOT_Include_Dir}
)

# look for the BornAgain library
find_library (BA_LIBRARY
	NAMES BornAgainCore BornAgainFit
	PATHS /usr/lib /usr/local/lib
)

# look for the ROOT library
find_library (ROOT_GPAD_LIBRARY
	NAMES Gpad
	PATHS /usr/lib/i386-linux-gnu/root5.34
)

find_library (ROOT_CORE_LIBRARY
	NAMES Core
	PATHS /usr/lib/i386-linux-gnu/root5.34
)

find_library (ROOT_HIST_LIBRARY
	NAMES Hist
	PATHS /usr/lib/i386-linux-gnu/root5.34
)


if (BA_LIBRARY)
	message ("BornAgain library is found in ${BA_LIBRARY}")
	target_link_libraries (CylindersAndPrisms ${BA_LIBRARY})
endif()

target_link_libraries (CylindersAndPrisms ${ROOT_CORE_LIBRARY}  ${ROOT_HIST_LIBRARY} ${ROOT_GPAD_LIBRARY})

