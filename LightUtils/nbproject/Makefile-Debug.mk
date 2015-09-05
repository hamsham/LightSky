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
CC=gcc-5
CCC=g++-5
CXX=g++-5
FC=gfortran-5
AS=as

# Macros
CND_PLATFORM=GCC_5-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1519963337/assertions.o \
	${OBJECTDIR}/_ext/1519963337/dataResource.o \
	${OBJECTDIR}/_ext/1519963337/pointer.o \
	${OBJECTDIR}/_ext/1519963337/randomNum.o \
	${OBJECTDIR}/_ext/1519963337/resource.o \
	${OBJECTDIR}/_ext/1519963337/string_utils.o \
	${OBJECTDIR}/_ext/1519963337/tuple.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/pointer_test_debug

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightutils_d.a

build/liblightutils_d.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightutils_d.a
	${AR} -rv build/liblightutils_d.a ${OBJECTFILES} 
	$(RANLIB) build/liblightutils_d.a

${OBJECTDIR}/_ext/1519963337/assertions.o: ../src/utils/assertions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/assertions.o ../src/utils/assertions.cpp

${OBJECTDIR}/_ext/1519963337/dataResource.o: ../src/utils/dataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/dataResource.o ../src/utils/dataResource.cpp

${OBJECTDIR}/_ext/1519963337/pointer.o: ../src/utils/pointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/pointer.o ../src/utils/pointer.cpp

${OBJECTDIR}/_ext/1519963337/randomNum.o: ../src/utils/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/randomNum.o ../src/utils/randomNum.cpp

${OBJECTDIR}/_ext/1519963337/resource.o: ../src/utils/resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/resource.o ../src/utils/resource.cpp

${OBJECTDIR}/_ext/1519963337/string_utils.o: ../src/utils/string_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/string_utils.o ../src/utils/string_utils.cpp

${OBJECTDIR}/_ext/1519963337/tuple.o: ../src/utils/tuple.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/tuple.o ../src/utils/tuple.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/pointer_test_debug: ${TESTDIR}/tests/pointer_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/pointer_test_debug $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/pointer_test.o: tests/pointer_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/pointer_test.o tests/pointer_test.cpp


${OBJECTDIR}/_ext/1519963337/assertions_nomain.o: ${OBJECTDIR}/_ext/1519963337/assertions.o ../src/utils/assertions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/assertions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/assertions_nomain.o ../src/utils/assertions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/assertions.o ${OBJECTDIR}/_ext/1519963337/assertions_nomain.o;\
	fi

${OBJECTDIR}/_ext/1519963337/dataResource_nomain.o: ${OBJECTDIR}/_ext/1519963337/dataResource.o ../src/utils/dataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/dataResource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/dataResource_nomain.o ../src/utils/dataResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/dataResource.o ${OBJECTDIR}/_ext/1519963337/dataResource_nomain.o;\
	fi

${OBJECTDIR}/_ext/1519963337/pointer_nomain.o: ${OBJECTDIR}/_ext/1519963337/pointer.o ../src/utils/pointer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/pointer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/pointer_nomain.o ../src/utils/pointer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/pointer.o ${OBJECTDIR}/_ext/1519963337/pointer_nomain.o;\
	fi

${OBJECTDIR}/_ext/1519963337/randomNum_nomain.o: ${OBJECTDIR}/_ext/1519963337/randomNum.o ../src/utils/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/randomNum.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/randomNum_nomain.o ../src/utils/randomNum.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/randomNum.o ${OBJECTDIR}/_ext/1519963337/randomNum_nomain.o;\
	fi

${OBJECTDIR}/_ext/1519963337/resource_nomain.o: ${OBJECTDIR}/_ext/1519963337/resource.o ../src/utils/resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/resource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/resource_nomain.o ../src/utils/resource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/resource.o ${OBJECTDIR}/_ext/1519963337/resource_nomain.o;\
	fi

${OBJECTDIR}/_ext/1519963337/string_utils_nomain.o: ${OBJECTDIR}/_ext/1519963337/string_utils.o ../src/utils/string_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/string_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/string_utils_nomain.o ../src/utils/string_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/string_utils.o ${OBJECTDIR}/_ext/1519963337/string_utils_nomain.o;\
	fi

${OBJECTDIR}/_ext/1519963337/tuple_nomain.o: ${OBJECTDIR}/_ext/1519963337/tuple.o ../src/utils/tuple.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/tuple.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -DLS_DEBUG -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/tuple_nomain.o ../src/utils/tuple.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/tuple.o ${OBJECTDIR}/_ext/1519963337/tuple_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/pointer_test_debug || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightutils_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
