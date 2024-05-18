# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ImgVidTools_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ImgVidTools_autogen.dir\\ParseCache.txt"
  "ImgVidTools_autogen"
  )
endif()
