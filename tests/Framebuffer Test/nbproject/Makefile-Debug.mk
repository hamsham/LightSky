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
	${OBJECTDIR}/controlState.o \
	${OBJECTDIR}/fbState.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/uiState.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -Wextra -Werror -pedantic-errors -static-libgcc -static-libstdc++
CXXFLAGS=-Wall -Wextra -Werror -pedantic-errors -static-libgcc -static-libstdc++

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../LightGame/build/liblightgame_d.a ../../LightDraw/build/liblightdraw_d.a ../../LightUtils/build/liblightutils_d.a ../../LightMath/build/liblightmath_d.a -lglew32 -lopengl32 -lFreeImage -lfreetype -lSDL2.dll -lSDL2main

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk fb_test_debug.exe

fb_test_debug.exe: ../../LightGame/build/liblightgame_d.a

fb_test_debug.exe: ../../LightDraw/build/liblightdraw_d.a

fb_test_debug.exe: ../../LightUtils/build/liblightutils_d.a

fb_test_debug.exe: ../../LightMath/build/liblightmath_d.a

fb_test_debug.exe: ${OBJECTFILES}
	${LINK.cc} -o fb_test_debug ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/controlState.o: controlState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controlState.o controlState.cpp

${OBJECTDIR}/fbState.o: fbState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fbState.o fbState.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/uiState.o: uiState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/uiState.o uiState.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} fb_test_debug.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
