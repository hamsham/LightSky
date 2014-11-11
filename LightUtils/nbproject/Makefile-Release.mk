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

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/pointer_test

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

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/pointer_test: ${TESTDIR}/tests/pointer_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/pointer_test -s $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/pointer_test.o: tests/pointer_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/pointer_test.o tests/pointer_test.cpp


${OBJECTDIR}/_ext/528976753/assert_nomain.o: ${OBJECTDIR}/_ext/528976753/assert.o ../lightsky/utils/src/assert.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/528976753/assert.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/assert_nomain.o ../lightsky/utils/src/assert.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/528976753/assert.o ${OBJECTDIR}/_ext/528976753/assert_nomain.o;\
	fi

${OBJECTDIR}/_ext/528976753/dataResource_nomain.o: ${OBJECTDIR}/_ext/528976753/dataResource.o ../lightsky/utils/src/dataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/528976753/dataResource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/dataResource_nomain.o ../lightsky/utils/src/dataResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/528976753/dataResource.o ${OBJECTDIR}/_ext/528976753/dataResource_nomain.o;\
	fi

${OBJECTDIR}/_ext/528976753/randomNum_nomain.o: ${OBJECTDIR}/_ext/528976753/randomNum.o ../lightsky/utils/src/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/528976753/randomNum.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/randomNum_nomain.o ../lightsky/utils/src/randomNum.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/528976753/randomNum.o ${OBJECTDIR}/_ext/528976753/randomNum_nomain.o;\
	fi

${OBJECTDIR}/_ext/528976753/resource_nomain.o: ${OBJECTDIR}/_ext/528976753/resource.o ../lightsky/utils/src/resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/528976753/resource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/resource_nomain.o ../lightsky/utils/src/resource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/528976753/resource.o ${OBJECTDIR}/_ext/528976753/resource_nomain.o;\
	fi

${OBJECTDIR}/_ext/528976753/string_utils_nomain.o: ${OBJECTDIR}/_ext/528976753/string_utils.o ../lightsky/utils/src/string_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/528976753/string_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/string_utils_nomain.o ../lightsky/utils/src/string_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/528976753/string_utils.o ${OBJECTDIR}/_ext/528976753/string_utils_nomain.o;\
	fi

${OBJECTDIR}/_ext/528976753/tuple_nomain.o: ${OBJECTDIR}/_ext/528976753/tuple.o ../lightsky/utils/src/tuple.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/528976753
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/528976753/tuple.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I.. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/528976753/tuple_nomain.o ../lightsky/utils/src/tuple.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/528976753/tuple.o ${OBJECTDIR}/_ext/528976753/tuple_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/pointer_test || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightutils.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
