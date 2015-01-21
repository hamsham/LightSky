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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
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
	${OBJECTDIR}/_ext/53083909/scriptMath.o \
	${OBJECTDIR}/_ext/53083909/scriptable.o \
	${OBJECTDIR}/_ext/53083909/setup.o \
	${OBJECTDIR}/_ext/53083909/variable.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	benchTest

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightscript.a

build/liblightscript.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightscript.a
	${AR} -rv build/liblightscript.a ${OBJECTFILES} 
	$(RANLIB) build/liblightscript.a

${OBJECTDIR}/_ext/53083909/factory.o: ../src/script/factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/factory.o ../src/script/factory.cpp

${OBJECTDIR}/_ext/53083909/functor.o: ../src/script/functor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/functor.o ../src/script/functor.cpp

${OBJECTDIR}/_ext/53083909/scriptMath.o: ../src/script/scriptMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/scriptMath.o ../src/script/scriptMath.cpp

${OBJECTDIR}/_ext/53083909/scriptable.o: ../src/script/scriptable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/scriptable.o ../src/script/scriptable.cpp

${OBJECTDIR}/_ext/53083909/setup.o: ../src/script/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/setup.o ../src/script/setup.cpp

${OBJECTDIR}/_ext/53083909/variable.o: ../src/script/variable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/variable.o ../src/script/variable.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
benchTest: ${TESTDIR}/tests/benchTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p null
	${LINK.cc}   -o benchTest $^ ${LDLIBSOPTIONS} ../LightUtils/build/liblightutils.a build/liblightscript.a 


${TESTDIR}/tests/benchTest.o: tests/benchTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/benchTest.o tests/benchTest.cpp


${OBJECTDIR}/_ext/53083909/factory_nomain.o: ${OBJECTDIR}/_ext/53083909/factory.o ../src/script/factory.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/53083909/factory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/factory_nomain.o ../src/script/factory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/53083909/factory.o ${OBJECTDIR}/_ext/53083909/factory_nomain.o;\
	fi

${OBJECTDIR}/_ext/53083909/functor_nomain.o: ${OBJECTDIR}/_ext/53083909/functor.o ../src/script/functor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/53083909/functor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/functor_nomain.o ../src/script/functor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/53083909/functor.o ${OBJECTDIR}/_ext/53083909/functor_nomain.o;\
	fi

${OBJECTDIR}/_ext/53083909/scriptMath_nomain.o: ${OBJECTDIR}/_ext/53083909/scriptMath.o ../src/script/scriptMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/53083909/scriptMath.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/scriptMath_nomain.o ../src/script/scriptMath.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/53083909/scriptMath.o ${OBJECTDIR}/_ext/53083909/scriptMath_nomain.o;\
	fi

${OBJECTDIR}/_ext/53083909/scriptable_nomain.o: ${OBJECTDIR}/_ext/53083909/scriptable.o ../src/script/scriptable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/53083909/scriptable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/scriptable_nomain.o ../src/script/scriptable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/53083909/scriptable.o ${OBJECTDIR}/_ext/53083909/scriptable_nomain.o;\
	fi

${OBJECTDIR}/_ext/53083909/setup_nomain.o: ${OBJECTDIR}/_ext/53083909/setup.o ../src/script/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/53083909/setup.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/setup_nomain.o ../src/script/setup.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/53083909/setup.o ${OBJECTDIR}/_ext/53083909/setup_nomain.o;\
	fi

${OBJECTDIR}/_ext/53083909/variable_nomain.o: ${OBJECTDIR}/_ext/53083909/variable.o ../src/script/variable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/53083909
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/53083909/variable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/53083909/variable_nomain.o ../src/script/variable.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/53083909/variable.o ${OBJECTDIR}/_ext/53083909/variable_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    benchTest || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightscript.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
