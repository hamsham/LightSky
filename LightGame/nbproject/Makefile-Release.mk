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
	${OBJECTDIR}/_ext/702534908/dispatcher.o \
	${OBJECTDIR}/_ext/702534908/game.o \
	${OBJECTDIR}/_ext/702534908/gameState.o \
	${OBJECTDIR}/_ext/702534908/manager.o \
	${OBJECTDIR}/_ext/702534908/subscriber.o \
	${OBJECTDIR}/_ext/702534908/system.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/event_test

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

${OBJECTDIR}/_ext/702534908/dispatcher.o: ../lightsky/game/src/dispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/dispatcher.o ../lightsky/game/src/dispatcher.cpp

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

${OBJECTDIR}/_ext/702534908/subscriber.o: ../lightsky/game/src/subscriber.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/subscriber.o ../lightsky/game/src/subscriber.cpp

${OBJECTDIR}/_ext/702534908/system.o: ../lightsky/game/src/system.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/system.o ../lightsky/game/src/system.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/event_test: ${TESTDIR}/tests/event_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}
	${LINK.cc}   -o ${TESTDIR}/event_test -s $^ ${LDLIBSOPTIONS} ../LightSetup/build/liblightsetup.a ../LightUtils/build/liblightutils.a ../LightDraw/build/liblightdraw.a 


${TESTDIR}/tests/event_test.o: tests/event_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/event_test.o tests/event_test.cpp


${OBJECTDIR}/_ext/702534908/dispatcher_nomain.o: ${OBJECTDIR}/_ext/702534908/dispatcher.o ../lightsky/game/src/dispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/702534908/dispatcher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/dispatcher_nomain.o ../lightsky/game/src/dispatcher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/702534908/dispatcher.o ${OBJECTDIR}/_ext/702534908/dispatcher_nomain.o;\
	fi

${OBJECTDIR}/_ext/702534908/game_nomain.o: ${OBJECTDIR}/_ext/702534908/game.o ../lightsky/game/src/game.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/702534908/game.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/game_nomain.o ../lightsky/game/src/game.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/702534908/game.o ${OBJECTDIR}/_ext/702534908/game_nomain.o;\
	fi

${OBJECTDIR}/_ext/702534908/gameState_nomain.o: ${OBJECTDIR}/_ext/702534908/gameState.o ../lightsky/game/src/gameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/702534908/gameState.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/gameState_nomain.o ../lightsky/game/src/gameState.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/702534908/gameState.o ${OBJECTDIR}/_ext/702534908/gameState_nomain.o;\
	fi

${OBJECTDIR}/_ext/702534908/manager_nomain.o: ${OBJECTDIR}/_ext/702534908/manager.o ../lightsky/game/src/manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/702534908/manager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/manager_nomain.o ../lightsky/game/src/manager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/702534908/manager.o ${OBJECTDIR}/_ext/702534908/manager_nomain.o;\
	fi

${OBJECTDIR}/_ext/702534908/subscriber_nomain.o: ${OBJECTDIR}/_ext/702534908/subscriber.o ../lightsky/game/src/subscriber.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/702534908/subscriber.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/subscriber_nomain.o ../lightsky/game/src/subscriber.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/702534908/subscriber.o ${OBJECTDIR}/_ext/702534908/subscriber_nomain.o;\
	fi

${OBJECTDIR}/_ext/702534908/system_nomain.o: ${OBJECTDIR}/_ext/702534908/system.o ../lightsky/game/src/system.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/702534908
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/702534908/system.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/702534908/system_nomain.o ../lightsky/game/src/system.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/702534908/system.o ${OBJECTDIR}/_ext/702534908/system_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/event_test || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightgame.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
