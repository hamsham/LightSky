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
	${OBJECTDIR}/_ext/1019118654/fixed.o \
	${OBJECTDIR}/_ext/1019118654/mat2.o \
	${OBJECTDIR}/_ext/1019118654/mat3.o \
	${OBJECTDIR}/_ext/1019118654/mat4.o \
	${OBJECTDIR}/_ext/1019118654/mat_utils.o \
	${OBJECTDIR}/_ext/1019118654/perlinNoise.o \
	${OBJECTDIR}/_ext/1019118654/quat.o \
	${OBJECTDIR}/_ext/1019118654/quat_utils.o \
	${OBJECTDIR}/_ext/1019118654/scalar_utils.o \
	${OBJECTDIR}/_ext/1019118654/vec2.o \
	${OBJECTDIR}/_ext/1019118654/vec3.o \
	${OBJECTDIR}/_ext/1019118654/vec4.o \
	${OBJECTDIR}/_ext/1019118654/vec_utils.o

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

${OBJECTDIR}/_ext/1019118654/fixed.o: ../src/math/fixed.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/fixed.o ../src/math/fixed.cpp

${OBJECTDIR}/_ext/1019118654/mat2.o: ../src/math/mat2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat2.o ../src/math/mat2.cpp

${OBJECTDIR}/_ext/1019118654/mat3.o: ../src/math/mat3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat3.o ../src/math/mat3.cpp

${OBJECTDIR}/_ext/1019118654/mat4.o: ../src/math/mat4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat4.o ../src/math/mat4.cpp

${OBJECTDIR}/_ext/1019118654/mat_utils.o: ../src/math/mat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat_utils.o ../src/math/mat_utils.cpp

${OBJECTDIR}/_ext/1019118654/perlinNoise.o: ../src/math/perlinNoise.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/perlinNoise.o ../src/math/perlinNoise.cpp

${OBJECTDIR}/_ext/1019118654/quat.o: ../src/math/quat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/quat.o ../src/math/quat.cpp

${OBJECTDIR}/_ext/1019118654/quat_utils.o: ../src/math/quat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/quat_utils.o ../src/math/quat_utils.cpp

${OBJECTDIR}/_ext/1019118654/scalar_utils.o: ../src/math/scalar_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/scalar_utils.o ../src/math/scalar_utils.cpp

${OBJECTDIR}/_ext/1019118654/vec2.o: ../src/math/vec2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec2.o ../src/math/vec2.cpp

${OBJECTDIR}/_ext/1019118654/vec3.o: ../src/math/vec3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec3.o ../src/math/vec3.cpp

${OBJECTDIR}/_ext/1019118654/vec4.o: ../src/math/vec4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec4.o ../src/math/vec4.cpp

${OBJECTDIR}/_ext/1019118654/vec_utils.o: ../src/math/vec_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec_utils.o ../src/math/vec_utils.cpp

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
	$(COMPILE.cc) -O3 -s -I../include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/event_test.o tests/event_test.cpp


${OBJECTDIR}/_ext/1019118654/fixed_nomain.o: ${OBJECTDIR}/_ext/1019118654/fixed.o ../src/math/fixed.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/fixed.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/fixed_nomain.o ../src/math/fixed.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/fixed.o ${OBJECTDIR}/_ext/1019118654/fixed_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/mat2_nomain.o: ${OBJECTDIR}/_ext/1019118654/mat2.o ../src/math/mat2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/mat2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat2_nomain.o ../src/math/mat2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/mat2.o ${OBJECTDIR}/_ext/1019118654/mat2_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/mat3_nomain.o: ${OBJECTDIR}/_ext/1019118654/mat3.o ../src/math/mat3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/mat3.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat3_nomain.o ../src/math/mat3.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/mat3.o ${OBJECTDIR}/_ext/1019118654/mat3_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/mat4_nomain.o: ${OBJECTDIR}/_ext/1019118654/mat4.o ../src/math/mat4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/mat4.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat4_nomain.o ../src/math/mat4.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/mat4.o ${OBJECTDIR}/_ext/1019118654/mat4_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/mat_utils_nomain.o: ${OBJECTDIR}/_ext/1019118654/mat_utils.o ../src/math/mat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/mat_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/mat_utils_nomain.o ../src/math/mat_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/mat_utils.o ${OBJECTDIR}/_ext/1019118654/mat_utils_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/perlinNoise_nomain.o: ${OBJECTDIR}/_ext/1019118654/perlinNoise.o ../src/math/perlinNoise.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/perlinNoise.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/perlinNoise_nomain.o ../src/math/perlinNoise.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/perlinNoise.o ${OBJECTDIR}/_ext/1019118654/perlinNoise_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/quat_nomain.o: ${OBJECTDIR}/_ext/1019118654/quat.o ../src/math/quat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/quat.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/quat_nomain.o ../src/math/quat.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/quat.o ${OBJECTDIR}/_ext/1019118654/quat_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/quat_utils_nomain.o: ${OBJECTDIR}/_ext/1019118654/quat_utils.o ../src/math/quat_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/quat_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/quat_utils_nomain.o ../src/math/quat_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/quat_utils.o ${OBJECTDIR}/_ext/1019118654/quat_utils_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/scalar_utils_nomain.o: ${OBJECTDIR}/_ext/1019118654/scalar_utils.o ../src/math/scalar_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/scalar_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/scalar_utils_nomain.o ../src/math/scalar_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/scalar_utils.o ${OBJECTDIR}/_ext/1019118654/scalar_utils_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/vec2_nomain.o: ${OBJECTDIR}/_ext/1019118654/vec2.o ../src/math/vec2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/vec2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec2_nomain.o ../src/math/vec2.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/vec2.o ${OBJECTDIR}/_ext/1019118654/vec2_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/vec3_nomain.o: ${OBJECTDIR}/_ext/1019118654/vec3.o ../src/math/vec3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/vec3.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec3_nomain.o ../src/math/vec3.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/vec3.o ${OBJECTDIR}/_ext/1019118654/vec3_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/vec4_nomain.o: ${OBJECTDIR}/_ext/1019118654/vec4.o ../src/math/vec4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/vec4.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec4_nomain.o ../src/math/vec4.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/vec4.o ${OBJECTDIR}/_ext/1019118654/vec4_nomain.o;\
	fi

${OBJECTDIR}/_ext/1019118654/vec_utils_nomain.o: ${OBJECTDIR}/_ext/1019118654/vec_utils.o ../src/math/vec_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019118654
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/1019118654/vec_utils.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -I../include -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019118654/vec_utils_nomain.o ../src/math/vec_utils.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/1019118654/vec_utils.o ${OBJECTDIR}/_ext/1019118654/vec_utils_nomain.o;\
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
