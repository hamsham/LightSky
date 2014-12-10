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
	${OBJECTDIR}/_ext/53083909/factory.o \
	${OBJECTDIR}/_ext/53083909/functor.o \
	${OBJECTDIR}/_ext/53083909/scriptable.o \
	${OBJECTDIR}/_ext/53083909/setup.o \
	${OBJECTDIR}/_ext/53083909/variable.o


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

${OBJECTDIR}/_ext/53083909/factory.o: ../src/script/factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/factory.o ../src/script/factory.cpp

${OBJECTDIR}/_ext/53083909/functor.o: ../src/script/functor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/functor.o ../src/script/functor.cpp

${OBJECTDIR}/_ext/53083909/scriptable.o: ../src/script/scriptable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/scriptable.o ../src/script/scriptable.cpp

${OBJECTDIR}/_ext/53083909/setup.o: ../src/script/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/setup.o ../src/script/setup.cpp

${OBJECTDIR}/_ext/53083909/variable.o: ../src/script/variable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/variable.o ../src/script/variable.cpp

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
