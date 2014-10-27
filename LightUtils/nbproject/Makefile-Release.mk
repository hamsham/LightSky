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
	${OBJECTDIR}/_ext/528976753/assert.o \
	${OBJECTDIR}/_ext/528976753/dataResource.o \
	${OBJECTDIR}/_ext/528976753/randomNum.o \
	${OBJECTDIR}/_ext/528976753/resource.o \
	${OBJECTDIR}/_ext/528976753/string_utils.o \
	${OBJECTDIR}/_ext/528976753/tuple.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightutils.a

build/liblightutils.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightutils.a
	${AR} -rv build/liblightutils.a ${OBJECTFILES} 
	$(RANLIB) build/liblightutils.a

${OBJECTDIR}/_ext/528976753/assert.o: ../lightsky/utils/src/assert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/assert.o ../lightsky/utils/src/assert.cpp

${OBJECTDIR}/_ext/528976753/dataResource.o: ../lightsky/utils/src/dataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/dataResource.o ../lightsky/utils/src/dataResource.cpp

${OBJECTDIR}/_ext/528976753/randomNum.o: ../lightsky/utils/src/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/randomNum.o ../lightsky/utils/src/randomNum.cpp

${OBJECTDIR}/_ext/528976753/resource.o: ../lightsky/utils/src/resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/resource.o ../lightsky/utils/src/resource.cpp

${OBJECTDIR}/_ext/528976753/string_utils.o: ../lightsky/utils/src/string_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/string_utils.o ../lightsky/utils/src/string_utils.cpp

${OBJECTDIR}/_ext/528976753/tuple.o: ../lightsky/utils/src/tuple.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/tuple.o ../lightsky/utils/src/tuple.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightutils.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
