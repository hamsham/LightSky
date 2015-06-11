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
	${OBJECTDIR}/_ext/1019297620/dispatcher.o \
	${OBJECTDIR}/_ext/1019297620/gameState.o \
	${OBJECTDIR}/_ext/1019297620/gameSystem.o \
	${OBJECTDIR}/_ext/1019297620/manager.o \
	${OBJECTDIR}/_ext/1019297620/subscriber.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/event_test_debug

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightgame_d.a

build/liblightgame_d.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightgame_d.a
	${AR} -rv build/liblightgame_d.a ${OBJECTFILES} 
	$(RANLIB) build/liblightgame_d.a

${OBJECTDIR}/_ext/1019297620/dispatcher.o: ../src/game/dispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/dispatcher.o ../src/game/dispatcher.cpp

${OBJECTDIR}/_ext/1019297620/gameState.o: ../src/game/gameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/gameState.o ../src/game/gameState.cpp

${OBJECTDIR}/_ext/1019297620/gameSystem.o: ../src/game/gameSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/gameSystem.o ../src/game/gameSystem.cpp

${OBJECTDIR}/_ext/1019297620/manager.o: ../src/game/manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/manager.o ../src/game/manager.cpp

${OBJECTDIR}/_ext/1019297620/subscriber.o: ../src/game/subscriber.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/subscriber.o ../src/game/subscriber.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/event_test_debug: ${TESTDIR}/tests/event_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}
	${LINK.cc}   -o ${TESTDIR}/event_test_debug $^ ${LDLIBSOPTIONS} ../LightSetup/build/liblightsetup_d.a ../LightUtils/build/liblightutils_d.a ../LightDraw/build/liblightdraw_d.a 


${TESTDIR}/tests/event_test.o: tests/event_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/event_test.o tests/event_test.cpp


${OBJECTDIR}/_ext/1019297620/dispatcher_nomain.o: ${OBJECTDIR}/_ext/1019297620/dispatcher.o ../src/game/dispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019297620/dispatcher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/dispatcher_nomain.o ../src/game/dispatcher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019297620/dispatcher.o ${OBJECTDIR}/_ext/1019297620/dispatcher_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019297620/gameState_nomain.o: ${OBJECTDIR}/_ext/1019297620/gameState.o ../src/game/gameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019297620/gameState.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/gameState_nomain.o ../src/game/gameState.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019297620/gameState.o ${OBJECTDIR}/_ext/1019297620/gameState_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019297620/gameSystem_nomain.o: ${OBJECTDIR}/_ext/1019297620/gameSystem.o ../src/game/gameSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019297620/gameSystem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/gameSystem_nomain.o ../src/game/gameSystem.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019297620/gameSystem.o ${OBJECTDIR}/_ext/1019297620/gameSystem_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019297620/manager_nomain.o: ${OBJECTDIR}/_ext/1019297620/manager.o ../src/game/manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019297620/manager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/manager_nomain.o ../src/game/manager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019297620/manager.o ${OBJECTDIR}/_ext/1019297620/manager_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019297620/subscriber_nomain.o: ${OBJECTDIR}/_ext/1019297620/subscriber.o ../src/game/subscriber.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019297620
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019297620/subscriber.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019297620/subscriber_nomain.o ../src/game/subscriber.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019297620/subscriber.o ${OBJECTDIR}/_ext/1019297620/subscriber_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/event_test_debug || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightgame_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
