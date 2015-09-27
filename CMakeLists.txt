cmake_minimum_required(VERSION 2.8)

set(CMAKE_DISABLE_INS_SOURCE_BUILDS ON)



# -------------------------------------
# Project Setup
# -------------------------------------
project("LightSky Game Development Framework")



# -------------------------------------
# include Paths
# -------------------------------------



# -------------------------------------
# Sub-Projects
# -------------------------------------
add_subdirectory("LightSetup")
include_directories("LightSetup/include")

add_subdirectory("LightUtils")
include_directories("LightUtils/include")

add_subdirectory("LightMath")
include_directories("LightMath/include")
