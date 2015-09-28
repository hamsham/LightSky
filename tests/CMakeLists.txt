cmake_minimum_required(VERSION 2.8)



# -------------------------------------
# Dependency Setup
# -------------------------------------
set(TEST_DEPS
    "${LIBRARY_OUTPUT_PATH}/${LS_STATIC_LIB_PREFIX}lssetup${LS_STATIC_LIB_SUFFIX}"
    "${LIBRARY_OUTPUT_PATH}/${LS_STATIC_LIB_PREFIX}lsutils${LS_STATIC_LIB_SUFFIX}"
    "${LIBRARY_OUTPUT_PATH}/${LS_STATIC_LIB_PREFIX}lsmath${LS_STATIC_LIB_SUFFIX}"
    "${LIBRARY_OUTPUT_PATH}/${LS_STATIC_LIB_PREFIX}lsscript${LS_STATIC_LIB_SUFFIX}"
)



# -------------------------------------
# Library Setup
# -------------------------------------
add_executable(lsscript_benchmark lsscript_benchmark.cpp)
add_executable(lsscript_sequencing lsscript_sequencing.cpp)
add_executable(lsscript_serializing lsscript_serializing.cpp)



# -------------------------------------
# Library Setup
# -------------------------------------
target_link_libraries(lsscript_benchmark ${TEST_DEPS})
target_link_libraries(lsscript_sequencing ${TEST_DEPS})
target_link_libraries(lsscript_serializing ${TEST_DEPS})
