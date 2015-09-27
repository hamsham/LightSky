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
add_subdirectory("ls_setup")
include_directories("ls_setup/include")

add_subdirectory("ls_utils")
include_directories("ls_utils/include")

add_subdirectory("ls_math")
include_directories("ls_math/include")
