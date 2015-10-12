cmake_minimum_required(VERSION 2.8)



# -------------------------------------
# Dependency Setup
# -------------------------------------
set(TEST_DEPS
    "${LIBRARY_OUTPUT_PATH}/${LS_STATIC_LIB_PREFIX}lssetup${LS_STATIC_LIB_SUFFIX}"
    "${LIBRARY_OUTPUT_PATH}/${LS_STATIC_LIB_PREFIX}lsutils${LS_STATIC_LIB_SUFFIX}"
    "${LIBRARY_OUTPUT_PATH}/${LS_STATIC_LIB_PREFIX}lsmath${LS_STATIC_LIB_SUFFIX}"
    "${LIBRARY_OUTPUT_PATH}/${LS_SHARED_LIB_PREFIX}lsscript${LS_SHARED_LIB_SUFFIX}"
)



# -------------------------------------
# Compiler Options
# -------------------------------------
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"
    OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"
)
    set(LS_COMPILER_WARNINGS "-Wall -Werror -Wextra -pedantic -pedantic-errors")
    set(LS_COMMON_COMPILER_FLAGS "-fPIC -pthread")
    set(LS_C_COMPILER_FLAGS "-std=c99 ${LS_COMMON_COMPILER_FLAGS} ${LS_COMPILER_WARNINGS}")
    set(LS_CXX_COMPILER_FLAGS "-std=c++11 ${LS_COMMON_COMPILER_FLAGS} ${LS_COMPILER_WARNINGS}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LS_C_COMPILER_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LS_CXX_COMPILER_FLAGS}")
else()
    message(FATAL_ERROR "Your compiler is currently unsupported.")
endif()



# -------------------------------------
# Building and Linking Targets
#
# .....mmmmm....BLT
# -------------------------------------
function(LS_TEST_BLT targetName targetFiles targetDeps)
    add_executable(${targetName} ${targetFiles})
    add_dependencies(${targetName} ${targetDeps})
    target_link_libraries(${targetName} ${TEST_DEPS})
endfunction(LS_TEST_BLT)



# -------------------------------------
# Executable Setup
# -------------------------------------
LS_TEST_BLT(lsutils_tuple_test "lsutils_tuple_test.cpp" "lsutils")

LS_TEST_BLT(lsscript_benchmark "lsscript_benchmark.cpp" "lsscript")
LS_TEST_BLT(lsscript_sequencing "lsscript_sequencing.cpp" "lsscript")
LS_TEST_BLT(lsscript_serializing "lsscript_serializing.cpp" "lsscript")
