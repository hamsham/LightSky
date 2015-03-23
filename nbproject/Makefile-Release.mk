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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/lightsky.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -mfpmath=sse
CXXFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -mfpmath=sse

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightsky.a

build/liblightsky.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightsky.a
	${AR} -rv build/liblightsky.a ${OBJECTFILES} 
	$(RANLIB) build/liblightsky.a

${OBJECTDIR}/src/lightsky.o: src/lightsky.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lightsky.o src/lightsky.cpp

# Subprojects
.build-subprojects:
	cd LightSetup && ${MAKE}  -f Makefile CONF=Release
	cd LightUtils && ${MAKE}  -f Makefile CONF=Release
	cd LightMath && ${MAKE}  -f Makefile CONF=Release
	cd LightScript && ${MAKE}  -f Makefile CONF=Release
	cd LightDraw && ${MAKE}  -f Makefile CONF=Release
	cd LightGame && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightsky.a

# Subprojects
.clean-subprojects:
	cd LightSetup && ${MAKE}  -f Makefile CONF=Release clean
	cd LightUtils && ${MAKE}  -f Makefile CONF=Release clean
	cd LightMath && ${MAKE}  -f Makefile CONF=Release clean
	cd LightScript && ${MAKE}  -f Makefile CONF=Release clean
	cd LightDraw && ${MAKE}  -f Makefile CONF=Release clean
	cd LightGame && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
