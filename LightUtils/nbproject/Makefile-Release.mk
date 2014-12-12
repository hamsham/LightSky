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
CND_CONF=Release
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
	${OBJECTDIR}/_ext/1519963337/randomNum.o \
	${OBJECTDIR}/_ext/1519963337/resource.o \
	${OBJECTDIR}/_ext/1519963337/string_utils.o \
	${OBJECTDIR}/_ext/1519963337/tuple.o

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

${OBJECTDIR}/_ext/1519963337/assertions.o: ../src/utils/assertions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/assertions.o ../src/utils/assertions.cpp

${OBJECTDIR}/_ext/1519963337/dataResource.o: ../src/utils/dataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/dataResource.o ../src/utils/dataResource.cpp

${OBJECTDIR}/_ext/1519963337/randomNum.o: ../src/utils/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/randomNum.o ../src/utils/randomNum.cpp

${OBJECTDIR}/_ext/1519963337/resource.o: ../src/utils/resource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/resource.o ../src/utils/resource.cpp

${OBJECTDIR}/_ext/1519963337/string_utils.o: ../src/utils/string_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/string_utils.o ../src/utils/string_utils.cpp

${OBJECTDIR}/_ext/1519963337/tuple.o: ../src/utils/tuple.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/tuple.o ../src/utils/tuple.cpp

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
	$(COMPILE.cc) -O3 -I../include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/pointer_test.o tests/pointer_test.cpp


${OBJECTDIR}/_ext/1519963337/assertions_nomain.o: ${OBJECTDIR}/_ext/1519963337/assertions.o ../src/utils/assertions.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/assertions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/assertions_nomain.o ../src/utils/assertions.cpp;\
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
	    $(COMPILE.cc) -O3 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/dataResource_nomain.o ../src/utils/dataResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/dataResource.o ${OBJECTDIR}/_ext/1519963337/dataResource_nomain.o;\
	fi

${OBJECTDIR}/_ext/1519963337/randomNum_nomain.o: ${OBJECTDIR}/_ext/1519963337/randomNum.o ../src/utils/randomNum.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519963337
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1519963337/randomNum.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/randomNum_nomain.o ../src/utils/randomNum.cpp;\
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
	    $(COMPILE.cc) -O3 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/resource_nomain.o ../src/utils/resource.cpp;\
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
	    $(COMPILE.cc) -O3 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/string_utils_nomain.o ../src/utils/string_utils.cpp;\
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
	    $(COMPILE.cc) -O3 -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1519963337/tuple_nomain.o ../src/utils/tuple.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1519963337/tuple.o ${OBJECTDIR}/_ext/1519963337/tuple_nomain.o;\
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
