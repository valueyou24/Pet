# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Pet_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Pet_autogen.dir\\ParseCache.txt"
  "Pet_autogen"
  )
endif()
