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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW32_Qt-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1522330350/fixed.o \
	${OBJECTDIR}/_ext/1522330350/mat2.o \
	${OBJECTDIR}/_ext/1522330350/mat3.o \
	${OBJECTDIR}/_ext/1522330350/mat4.o \
	${OBJECTDIR}/_ext/1522330350/mat_utils.o \
	${OBJECTDIR}/_ext/1522330350/perlinNoise.o \
	${OBJECTDIR}/_ext/1522330350/quat.o \
	${OBJECTDIR}/_ext/1522330350/quat_utils.o \
	${OBJECTDIR}/_ext/1522330350/scalar_utils.o \
	${OBJECTDIR}/_ext/1522330350/vec2.o \
	${OBJECTDIR}/_ext/1522330350/vec3.o \
	${OBJECTDIR}/_ext/1522330350/vec4.o \
	${OBJECTDIR}/_ext/1522330350/vec_utils.o


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

${OBJECTDIR}/_ext/1522330350/fixed.o: ../lightsky/math/src/fixed.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/fixed.o ../lightsky/math/src/fixed.cpp

${OBJECTDIR}/_ext/1522330350/mat2.o: ../lightsky/math/src/mat2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/mat2.o ../lightsky/math/src/mat2.cpp

${OBJECTDIR}/_ext/1522330350/mat3.o: ../lightsky/math/src/mat3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/mat3.o ../lightsky/math/src/mat3.cpp

${OBJECTDIR}/_ext/1522330350/mat4.o: ../lightsky/math/src/mat4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/mat4.o ../lightsky/math/src/mat4.cpp

${OBJECTDIR}/_ext/1522330350/mat_utils.o: ../lightsky/math/src/mat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/mat_utils.o ../lightsky/math/src/mat_utils.cpp

${OBJECTDIR}/_ext/1522330350/perlinNoise.o: ../lightsky/math/src/perlinNoise.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/perlinNoise.o ../lightsky/math/src/perlinNoise.cpp

${OBJECTDIR}/_ext/1522330350/quat.o: ../lightsky/math/src/quat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/quat.o ../lightsky/math/src/quat.cpp

${OBJECTDIR}/_ext/1522330350/quat_utils.o: ../lightsky/math/src/quat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/quat_utils.o ../lightsky/math/src/quat_utils.cpp

${OBJECTDIR}/_ext/1522330350/scalar_utils.o: ../lightsky/math/src/scalar_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/scalar_utils.o ../lightsky/math/src/scalar_utils.cpp

${OBJECTDIR}/_ext/1522330350/vec2.o: ../lightsky/math/src/vec2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/vec2.o ../lightsky/math/src/vec2.cpp

${OBJECTDIR}/_ext/1522330350/vec3.o: ../lightsky/math/src/vec3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/vec3.o ../lightsky/math/src/vec3.cpp

${OBJECTDIR}/_ext/1522330350/vec4.o: ../lightsky/math/src/vec4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/vec4.o ../lightsky/math/src/vec4.cpp

${OBJECTDIR}/_ext/1522330350/vec_utils.o: ../lightsky/math/src/vec_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522330350
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522330350/vec_utils.o ../lightsky/math/src/vec_utils.cpp

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
