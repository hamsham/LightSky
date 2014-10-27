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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/904064829/setup.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightsetup.a

build/liblightsetup.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightsetup.a
	${AR} -rv build/liblightsetup.a ${OBJECTFILES} 
	$(RANLIB) build/liblightsetup.a

${OBJECTDIR}/_ext/904064829/setup.o: ../lightsky/setup/src/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/904064829
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/904064829/setup.o ../lightsky/setup/src/setup.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightsetup.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc