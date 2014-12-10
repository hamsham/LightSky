#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1019118654/fixed.o \
	${OBJECTDIR}/_ext/1019118654/mat2.o \
	${OBJECTDIR}/_ext/1019118654/mat3.o \
	${OBJECTDIR}/_ext/1019118654/mat4.o \
	${OBJECTDIR}/_ext/1019118654/mat_utils.o \
	${OBJECTDIR}/_ext/1019118654/perlinNoise.o \
	${OBJECTDIR}/_ext/1019118654/quat.o \
	${OBJECTDIR}/_ext/1019118654/quat_utils.o \
	${OBJECTDIR}/_ext/1019118654/scalar_utils.o \
	${OBJECTDIR}/_ext/1019118654/vec2.o \
	${OBJECTDIR}/_ext/1019118654/vec3.o \
	${OBJECTDIR}/_ext/1019118654/vec4.o \
	${OBJECTDIR}/_ext/1019118654/vec_utils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -mfpmath=sse -ggdb -O2
CXXFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -mfpmath=sse -ggdb -O2

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightmath_d.a

build/liblightmath_d.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightmath_d.a
	${AR} -rv build/liblightmath_d.a ${OBJECTFILES} 
	$(RANLIB) build/liblightmath_d.a

${OBJECTDIR}/_ext/1019118654/fixed.o: ../src/math/fixed.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/fixed.o ../src/math/fixed.cpp

${OBJECTDIR}/_ext/1019118654/mat2.o: ../src/math/mat2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat2.o ../src/math/mat2.cpp

${OBJECTDIR}/_ext/1019118654/mat3.o: ../src/math/mat3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat3.o ../src/math/mat3.cpp

${OBJECTDIR}/_ext/1019118654/mat4.o: ../src/math/mat4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat4.o ../src/math/mat4.cpp

${OBJECTDIR}/_ext/1019118654/mat_utils.o: ../src/math/mat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat_utils.o ../src/math/mat_utils.cpp

${OBJECTDIR}/_ext/1019118654/perlinNoise.o: ../src/math/perlinNoise.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/perlinNoise.o ../src/math/perlinNoise.cpp

${OBJECTDIR}/_ext/1019118654/quat.o: ../src/math/quat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/quat.o ../src/math/quat.cpp

${OBJECTDIR}/_ext/1019118654/quat_utils.o: ../src/math/quat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/quat_utils.o ../src/math/quat_utils.cpp

${OBJECTDIR}/_ext/1019118654/scalar_utils.o: ../src/math/scalar_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/scalar_utils.o ../src/math/scalar_utils.cpp

${OBJECTDIR}/_ext/1019118654/vec2.o: ../src/math/vec2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec2.o ../src/math/vec2.cpp

${OBJECTDIR}/_ext/1019118654/vec3.o: ../src/math/vec3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec3.o ../src/math/vec3.cpp

${OBJECTDIR}/_ext/1019118654/vec4.o: ../src/math/vec4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec4.o ../src/math/vec4.cpp

${OBJECTDIR}/_ext/1019118654/vec_utils.o: ../src/math/vec_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec_utils.o ../src/math/vec_utils.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightmath_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
