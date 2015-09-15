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
CND_PLATFORM=MinGW_W64-Windows
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
	${OBJECTDIR}/_ext/1522246397/setup.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightsetup_d.a

build/liblightsetup_d.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightsetup_d.a
	${AR} -rv build/liblightsetup_d.a ${OBJECTFILES} 
	$(RANLIB) build/liblightsetup_d.a

${OBJECTDIR}/_ext/1522246397/setup.o: ../src/setup/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1522246397
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1522246397/setup.o ../src/setup/setup.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightsetup_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
