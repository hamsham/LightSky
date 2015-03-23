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
	${OBJECTDIR}/context.o \
	${OBJECTDIR}/controlState.o \
	${OBJECTDIR}/display.o \
	${OBJECTDIR}/fbState.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/uiState.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -Wextra -Werror -pedantic-errors -ggdb -pthread -static-libstdc++ -static-libgcc -flto
CXXFLAGS=-Wall -Wextra -Werror -pedantic-errors -ggdb -pthread -static-libstdc++ -static-libgcc -flto

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../LightScript/build/liblightscript_d.a ../../LightGame/build/liblightgame_d.a ../../LightDraw/build/liblightdraw_d.a ../../LightMath/build/liblightmath_d.a ../../LightUtils/build/liblightutils_d.a ../../LightSetup/build/liblightsetup_d.a -lGL -lassimp -lSDL2 -lSDL2main -lfreeimage -lfreetype

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk fb_test_debug

fb_test_debug: ../../LightScript/build/liblightscript_d.a

fb_test_debug: ../../LightGame/build/liblightgame_d.a

fb_test_debug: ../../LightDraw/build/liblightdraw_d.a

fb_test_debug: ../../LightMath/build/liblightmath_d.a

fb_test_debug: ../../LightUtils/build/liblightutils_d.a

fb_test_debug: ../../LightSetup/build/liblightsetup_d.a

fb_test_debug: ${OBJECTFILES}
	${LINK.cc} -o fb_test_debug ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/context.o: context.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/context.o context.cpp

${OBJECTDIR}/controlState.o: controlState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/controlState.o controlState.cpp

${OBJECTDIR}/display.o: display.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/display.o display.cpp

${OBJECTDIR}/fbState.o: fbState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fbState.o fbState.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/uiState.o: uiState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -O2 -w -DLS_DEBUG -DSDL_MAIN_HANDLED -I../../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/uiState.o uiState.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} fb_test_debug

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
