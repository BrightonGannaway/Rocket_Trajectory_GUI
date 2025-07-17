# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Rocket_Trajecotory_GUI_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Rocket_Trajecotory_GUI_autogen.dir/ParseCache.txt"
  "Rocket_Trajecotory_GUI_autogen"
  )
endif()
