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
CND_PLATFORM=MinGW-Windows
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
	${OBJECTDIR}/src/lightSky.o \
	${OBJECTDIR}/src/lsAtlas.o \
	${OBJECTDIR}/src/lsBlendObject.o \
	${OBJECTDIR}/src/lsBoundingBox.o \
	${OBJECTDIR}/src/lsBufferObject.o \
	${OBJECTDIR}/src/lsColor.o \
	${OBJECTDIR}/src/lsContext.o \
	${OBJECTDIR}/src/lsDataResource.o \
	${OBJECTDIR}/src/lsDepthObject.o \
	${OBJECTDIR}/src/lsDisplay.o \
	${OBJECTDIR}/src/lsDrawModel.o \
	${OBJECTDIR}/src/lsFontResource.o \
	${OBJECTDIR}/src/lsFramebuffer.o \
	${OBJECTDIR}/src/lsGameState.o \
	${OBJECTDIR}/src/lsGeometry.o \
	${OBJECTDIR}/src/lsImageResource.o \
	${OBJECTDIR}/src/lsManager.o \
	${OBJECTDIR}/src/lsMatrixStack.o \
	${OBJECTDIR}/src/lsMesh.o \
	${OBJECTDIR}/src/lsMeshResource.o \
	${OBJECTDIR}/src/lsPerlinNoise.o \
	${OBJECTDIR}/src/lsRandom.o \
	${OBJECTDIR}/src/lsRenderer.o \
	${OBJECTDIR}/src/lsResource.o \
	${OBJECTDIR}/src/lsSceneManager.o \
	${OBJECTDIR}/src/lsSetup.o \
	${OBJECTDIR}/src/lsShaderObject.o \
	${OBJECTDIR}/src/lsShaderProgram.o \
	${OBJECTDIR}/src/lsSystem.o \
	${OBJECTDIR}/src/lsTexture.o \
	${OBJECTDIR}/src/lsUtil.o \
	${OBJECTDIR}/src/lsVertex.o \
	${OBJECTDIR}/src/lsVertexArray.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	tests/Framebuffer_Test/fbTest

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32 -Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -flto -O3 -mwindows -static-libgcc -static-libstdc++
CXXFLAGS=-m32 -Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -flto -O3 -mwindows -static-libgcc -static-libstdc++

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/liblightsky.a

bin/liblightsky.a: ${OBJECTFILES}
	${MKDIR} -p bin
	${RM} bin/liblightsky.a
	${AR} -rv bin/liblightsky.a ${OBJECTFILES} 
	$(RANLIB) bin/liblightsky.a

${OBJECTDIR}/src/lightSky.o: src/lightSky.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lightSky.o src/lightSky.cpp

${OBJECTDIR}/src/lsAtlas.o: src/lsAtlas.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsAtlas.o src/lsAtlas.cpp

${OBJECTDIR}/src/lsBlendObject.o: src/lsBlendObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBlendObject.o src/lsBlendObject.cpp

${OBJECTDIR}/src/lsBoundingBox.o: src/lsBoundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBoundingBox.o src/lsBoundingBox.cpp

${OBJECTDIR}/src/lsBufferObject.o: src/lsBufferObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBufferObject.o src/lsBufferObject.cpp

${OBJECTDIR}/src/lsColor.o: src/lsColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsColor.o src/lsColor.cpp

${OBJECTDIR}/src/lsContext.o: src/lsContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsContext.o src/lsContext.cpp

${OBJECTDIR}/src/lsDataResource.o: src/lsDataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDataResource.o src/lsDataResource.cpp

${OBJECTDIR}/src/lsDepthObject.o: src/lsDepthObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDepthObject.o src/lsDepthObject.cpp

${OBJECTDIR}/src/lsDisplay.o: src/lsDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDisplay.o src/lsDisplay.cpp

${OBJECTDIR}/src/lsDrawModel.o: src/lsDrawModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDrawModel.o src/lsDrawModel.cpp

${OBJECTDIR}/src/lsFontResource.o: src/lsFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsFontResource.o src/lsFontResource.cpp

${OBJECTDIR}/src/lsFramebuffer.o: src/lsFramebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsFramebuffer.o src/lsFramebuffer.cpp

${OBJECTDIR}/src/lsGameState.o: src/lsGameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsGameState.o src/lsGameState.cpp

${OBJECTDIR}/src/lsGeometry.o: src/lsGeometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsGeometry.o src/lsGeometry.cpp

${OBJECTDIR}/src/lsImageResource.o: src/lsImageResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsImageResource.o src/lsImageResource.cpp

${OBJECTDIR}/src/lsManager.o: src/lsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsManager.o src/lsManager.cpp

${OBJECTDIR}/src/lsMatrixStack.o: src/lsMatrixStack.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMatrixStack.o src/lsMatrixStack.cpp

${OBJECTDIR}/src/lsMesh.o: src/lsMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMesh.o src/lsMesh.cpp

${OBJECTDIR}/src/lsMeshResource.o: src/lsMeshResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMeshResource.o src/lsMeshResource.cpp

${OBJECTDIR}/src/lsPerlinNoise.o: src/lsPerlinNoise.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsPerlinNoise.o src/lsPerlinNoise.cpp

${OBJECTDIR}/src/lsRandom.o: src/lsRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsRandom.o src/lsRandom.cpp

${OBJECTDIR}/src/lsRenderer.o: src/lsRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsRenderer.o src/lsRenderer.cpp

${OBJECTDIR}/src/lsResource.o: src/lsResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsResource.o src/lsResource.cpp

${OBJECTDIR}/src/lsSceneManager.o: src/lsSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSceneManager.o src/lsSceneManager.cpp

${OBJECTDIR}/src/lsSetup.o: src/lsSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSetup.o src/lsSetup.cpp

${OBJECTDIR}/src/lsShaderObject.o: src/lsShaderObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsShaderObject.o src/lsShaderObject.cpp

${OBJECTDIR}/src/lsShaderProgram.o: src/lsShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsShaderProgram.o src/lsShaderProgram.cpp

${OBJECTDIR}/src/lsSystem.o: src/lsSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSystem.o src/lsSystem.cpp

${OBJECTDIR}/src/lsTexture.o: src/lsTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsTexture.o src/lsTexture.cpp

${OBJECTDIR}/src/lsUtil.o: src/lsUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsUtil.o src/lsUtil.cpp

${OBJECTDIR}/src/lsVertex.o: src/lsVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsVertex.o src/lsVertex.cpp

${OBJECTDIR}/src/lsVertexArray.o: src/lsVertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsVertexArray.o src/lsVertexArray.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
tests/Framebuffer_Test/fbTest: ${TESTDIR}/tests/Framebuffer_Test/controlState.o ${TESTDIR}/tests/Framebuffer_Test/fbState.o ${TESTDIR}/tests/Framebuffer_Test/main.o ${TESTDIR}/tests/Framebuffer_Test/uiState.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p tests/Framebuffer_Test
	${LINK.cc}   -o tests/Framebuffer_Test/fbTest -s $^ ${LDLIBSOPTIONS} ../HamLibs/./bin/libhamlibs.a -lglew32 -lopengl32 -lSDL2 -lSDL2main -lFreeImage -lfreetype 


${TESTDIR}/tests/Framebuffer_Test/controlState.o: tests/Framebuffer_Test/controlState.cpp 
	${MKDIR} -p ${TESTDIR}/tests/Framebuffer_Test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -I. -I. -std=c++11 -lpthread -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Framebuffer_Test/controlState.o tests/Framebuffer_Test/controlState.cpp


${TESTDIR}/tests/Framebuffer_Test/fbState.o: tests/Framebuffer_Test/fbState.cpp 
	${MKDIR} -p ${TESTDIR}/tests/Framebuffer_Test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -I. -I. -std=c++11 -lpthread -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Framebuffer_Test/fbState.o tests/Framebuffer_Test/fbState.cpp


${TESTDIR}/tests/Framebuffer_Test/main.o: tests/Framebuffer_Test/main.cpp 
	${MKDIR} -p ${TESTDIR}/tests/Framebuffer_Test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -I. -I. -std=c++11 -lpthread -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Framebuffer_Test/main.o tests/Framebuffer_Test/main.cpp


${TESTDIR}/tests/Framebuffer_Test/uiState.o: tests/Framebuffer_Test/uiState.cpp 
	${MKDIR} -p ${TESTDIR}/tests/Framebuffer_Test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -I. -I. -std=c++11 -lpthread -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Framebuffer_Test/uiState.o tests/Framebuffer_Test/uiState.cpp


${OBJECTDIR}/src/lightSky_nomain.o: ${OBJECTDIR}/src/lightSky.o src/lightSky.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lightSky.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lightSky_nomain.o src/lightSky.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lightSky.o ${OBJECTDIR}/src/lightSky_nomain.o;\
	fi

${OBJECTDIR}/src/lsAtlas_nomain.o: ${OBJECTDIR}/src/lsAtlas.o src/lsAtlas.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsAtlas.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsAtlas_nomain.o src/lsAtlas.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsAtlas.o ${OBJECTDIR}/src/lsAtlas_nomain.o;\
	fi

${OBJECTDIR}/src/lsBlendObject_nomain.o: ${OBJECTDIR}/src/lsBlendObject.o src/lsBlendObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsBlendObject.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBlendObject_nomain.o src/lsBlendObject.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsBlendObject.o ${OBJECTDIR}/src/lsBlendObject_nomain.o;\
	fi

${OBJECTDIR}/src/lsBoundingBox_nomain.o: ${OBJECTDIR}/src/lsBoundingBox.o src/lsBoundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsBoundingBox.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBoundingBox_nomain.o src/lsBoundingBox.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsBoundingBox.o ${OBJECTDIR}/src/lsBoundingBox_nomain.o;\
	fi

${OBJECTDIR}/src/lsBufferObject_nomain.o: ${OBJECTDIR}/src/lsBufferObject.o src/lsBufferObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsBufferObject.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBufferObject_nomain.o src/lsBufferObject.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsBufferObject.o ${OBJECTDIR}/src/lsBufferObject_nomain.o;\
	fi

${OBJECTDIR}/src/lsColor_nomain.o: ${OBJECTDIR}/src/lsColor.o src/lsColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsColor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsColor_nomain.o src/lsColor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsColor.o ${OBJECTDIR}/src/lsColor_nomain.o;\
	fi

${OBJECTDIR}/src/lsContext_nomain.o: ${OBJECTDIR}/src/lsContext.o src/lsContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsContext.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsContext_nomain.o src/lsContext.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsContext.o ${OBJECTDIR}/src/lsContext_nomain.o;\
	fi

${OBJECTDIR}/src/lsDataResource_nomain.o: ${OBJECTDIR}/src/lsDataResource.o src/lsDataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsDataResource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDataResource_nomain.o src/lsDataResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsDataResource.o ${OBJECTDIR}/src/lsDataResource_nomain.o;\
	fi

${OBJECTDIR}/src/lsDepthObject_nomain.o: ${OBJECTDIR}/src/lsDepthObject.o src/lsDepthObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsDepthObject.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDepthObject_nomain.o src/lsDepthObject.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsDepthObject.o ${OBJECTDIR}/src/lsDepthObject_nomain.o;\
	fi

${OBJECTDIR}/src/lsDisplay_nomain.o: ${OBJECTDIR}/src/lsDisplay.o src/lsDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsDisplay.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDisplay_nomain.o src/lsDisplay.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsDisplay.o ${OBJECTDIR}/src/lsDisplay_nomain.o;\
	fi

${OBJECTDIR}/src/lsDrawModel_nomain.o: ${OBJECTDIR}/src/lsDrawModel.o src/lsDrawModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsDrawModel.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDrawModel_nomain.o src/lsDrawModel.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsDrawModel.o ${OBJECTDIR}/src/lsDrawModel_nomain.o;\
	fi

${OBJECTDIR}/src/lsFontResource_nomain.o: ${OBJECTDIR}/src/lsFontResource.o src/lsFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsFontResource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsFontResource_nomain.o src/lsFontResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsFontResource.o ${OBJECTDIR}/src/lsFontResource_nomain.o;\
	fi

${OBJECTDIR}/src/lsFramebuffer_nomain.o: ${OBJECTDIR}/src/lsFramebuffer.o src/lsFramebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsFramebuffer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsFramebuffer_nomain.o src/lsFramebuffer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsFramebuffer.o ${OBJECTDIR}/src/lsFramebuffer_nomain.o;\
	fi

${OBJECTDIR}/src/lsGameState_nomain.o: ${OBJECTDIR}/src/lsGameState.o src/lsGameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsGameState.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsGameState_nomain.o src/lsGameState.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsGameState.o ${OBJECTDIR}/src/lsGameState_nomain.o;\
	fi

${OBJECTDIR}/src/lsGeometry_nomain.o: ${OBJECTDIR}/src/lsGeometry.o src/lsGeometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsGeometry.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsGeometry_nomain.o src/lsGeometry.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsGeometry.o ${OBJECTDIR}/src/lsGeometry_nomain.o;\
	fi

${OBJECTDIR}/src/lsImageResource_nomain.o: ${OBJECTDIR}/src/lsImageResource.o src/lsImageResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsImageResource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsImageResource_nomain.o src/lsImageResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsImageResource.o ${OBJECTDIR}/src/lsImageResource_nomain.o;\
	fi

${OBJECTDIR}/src/lsManager_nomain.o: ${OBJECTDIR}/src/lsManager.o src/lsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsManager_nomain.o src/lsManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsManager.o ${OBJECTDIR}/src/lsManager_nomain.o;\
	fi

${OBJECTDIR}/src/lsMatrixStack_nomain.o: ${OBJECTDIR}/src/lsMatrixStack.o src/lsMatrixStack.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsMatrixStack.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMatrixStack_nomain.o src/lsMatrixStack.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsMatrixStack.o ${OBJECTDIR}/src/lsMatrixStack_nomain.o;\
	fi

${OBJECTDIR}/src/lsMesh_nomain.o: ${OBJECTDIR}/src/lsMesh.o src/lsMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsMesh.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMesh_nomain.o src/lsMesh.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsMesh.o ${OBJECTDIR}/src/lsMesh_nomain.o;\
	fi

${OBJECTDIR}/src/lsMeshResource_nomain.o: ${OBJECTDIR}/src/lsMeshResource.o src/lsMeshResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsMeshResource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMeshResource_nomain.o src/lsMeshResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsMeshResource.o ${OBJECTDIR}/src/lsMeshResource_nomain.o;\
	fi

${OBJECTDIR}/src/lsPerlinNoise_nomain.o: ${OBJECTDIR}/src/lsPerlinNoise.o src/lsPerlinNoise.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsPerlinNoise.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsPerlinNoise_nomain.o src/lsPerlinNoise.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsPerlinNoise.o ${OBJECTDIR}/src/lsPerlinNoise_nomain.o;\
	fi

${OBJECTDIR}/src/lsRandom_nomain.o: ${OBJECTDIR}/src/lsRandom.o src/lsRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsRandom.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsRandom_nomain.o src/lsRandom.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsRandom.o ${OBJECTDIR}/src/lsRandom_nomain.o;\
	fi

${OBJECTDIR}/src/lsRenderer_nomain.o: ${OBJECTDIR}/src/lsRenderer.o src/lsRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsRenderer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsRenderer_nomain.o src/lsRenderer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsRenderer.o ${OBJECTDIR}/src/lsRenderer_nomain.o;\
	fi

${OBJECTDIR}/src/lsResource_nomain.o: ${OBJECTDIR}/src/lsResource.o src/lsResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsResource.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsResource_nomain.o src/lsResource.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsResource.o ${OBJECTDIR}/src/lsResource_nomain.o;\
	fi

${OBJECTDIR}/src/lsSceneManager_nomain.o: ${OBJECTDIR}/src/lsSceneManager.o src/lsSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsSceneManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSceneManager_nomain.o src/lsSceneManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsSceneManager.o ${OBJECTDIR}/src/lsSceneManager_nomain.o;\
	fi

${OBJECTDIR}/src/lsSetup_nomain.o: ${OBJECTDIR}/src/lsSetup.o src/lsSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsSetup.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSetup_nomain.o src/lsSetup.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsSetup.o ${OBJECTDIR}/src/lsSetup_nomain.o;\
	fi

${OBJECTDIR}/src/lsShaderObject_nomain.o: ${OBJECTDIR}/src/lsShaderObject.o src/lsShaderObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsShaderObject.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsShaderObject_nomain.o src/lsShaderObject.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsShaderObject.o ${OBJECTDIR}/src/lsShaderObject_nomain.o;\
	fi

${OBJECTDIR}/src/lsShaderProgram_nomain.o: ${OBJECTDIR}/src/lsShaderProgram.o src/lsShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsShaderProgram.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsShaderProgram_nomain.o src/lsShaderProgram.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsShaderProgram.o ${OBJECTDIR}/src/lsShaderProgram_nomain.o;\
	fi

${OBJECTDIR}/src/lsSystem_nomain.o: ${OBJECTDIR}/src/lsSystem.o src/lsSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsSystem.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSystem_nomain.o src/lsSystem.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsSystem.o ${OBJECTDIR}/src/lsSystem_nomain.o;\
	fi

${OBJECTDIR}/src/lsTexture_nomain.o: ${OBJECTDIR}/src/lsTexture.o src/lsTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsTexture.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsTexture_nomain.o src/lsTexture.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsTexture.o ${OBJECTDIR}/src/lsTexture_nomain.o;\
	fi

${OBJECTDIR}/src/lsUtil_nomain.o: ${OBJECTDIR}/src/lsUtil.o src/lsUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsUtil.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsUtil_nomain.o src/lsUtil.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsUtil.o ${OBJECTDIR}/src/lsUtil_nomain.o;\
	fi

${OBJECTDIR}/src/lsVertex_nomain.o: ${OBJECTDIR}/src/lsVertex.o src/lsVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsVertex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsVertex_nomain.o src/lsVertex.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsVertex.o ${OBJECTDIR}/src/lsVertex_nomain.o;\
	fi

${OBJECTDIR}/src/lsVertexArray_nomain.o: ${OBJECTDIR}/src/lsVertexArray.o src/lsVertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/lsVertexArray.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -Iinclude -I../HamLibs/include -I../../../../../MinGW32/include/freetype2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsVertexArray_nomain.o src/lsVertexArray.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/lsVertexArray.o ${OBJECTDIR}/src/lsVertexArray_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    tests/Framebuffer_Test/fbTest || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/liblightsky.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
