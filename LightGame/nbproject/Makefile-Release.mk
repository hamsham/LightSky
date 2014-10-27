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
	${OBJECTDIR}/_ext/702534908/game.o \
	${OBJECTDIR}/_ext/702534908/gameState.o \
	${OBJECTDIR}/_ext/702534908/manager.o \
	${OBJECTDIR}/_ext/702534908/system.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightgame.a

build/liblightgame.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightgame.a
	${AR} -rv build/liblightgame.a ${OBJECTFILES} 
	$(RANLIB) build/liblightgame.a

${OBJECTDIR}/_ext/702534908/game.o: ../lightsky/game/src/game.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/game.o ../lightsky/game/src/game.cpp

${OBJECTDIR}/_ext/702534908/gameState.o: ../lightsky/game/src/gameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/gameState.o ../lightsky/game/src/gameState.cpp

${OBJECTDIR}/_ext/702534908/manager.o: ../lightsky/game/src/manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/manager.o ../lightsky/game/src/manager.cpp

${OBJECTDIR}/_ext/702534908/system.o: ../lightsky/game/src/system.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/system.o ../lightsky/game/src/system.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightgame.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
