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
	${OBJECTDIR}/_ext/387083285/factory.o \
	${OBJECTDIR}/_ext/387083285/functor.o \
	${OBJECTDIR}/_ext/387083285/scriptable.o \
	${OBJECTDIR}/_ext/387083285/setup.o \
	${OBJECTDIR}/_ext/387083285/variable.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightscript_d.a

build/liblightscript_d.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightscript_d.a
	${AR} -rv build/liblightscript_d.a ${OBJECTFILES} 
	$(RANLIB) build/liblightscript_d.a

${OBJECTDIR}/_ext/387083285/factory.o: ../lightsky/script/src/factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/387083285
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/387083285/factory.o ../lightsky/script/src/factory.cpp

${OBJECTDIR}/_ext/387083285/functor.o: ../lightsky/script/src/functor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/387083285
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/387083285/functor.o ../lightsky/script/src/functor.cpp

${OBJECTDIR}/_ext/387083285/scriptable.o: ../lightsky/script/src/scriptable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/387083285
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/387083285/scriptable.o ../lightsky/script/src/scriptable.cpp

${OBJECTDIR}/_ext/387083285/setup.o: ../lightsky/script/src/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/387083285
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/387083285/setup.o ../lightsky/script/src/setup.cpp

${OBJECTDIR}/_ext/387083285/variable.o: ../lightsky/script/src/variable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/387083285
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/387083285/variable.o ../lightsky/script/src/variable.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightscript_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
