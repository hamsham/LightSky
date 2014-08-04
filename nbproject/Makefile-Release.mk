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
	${OBJECTDIR}/fbState.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/lightSky.o \
	${OBJECTDIR}/src/lsAtlas.o \
	${OBJECTDIR}/src/lsBlender.o \
	${OBJECTDIR}/src/lsBoundingBox.o \
	${OBJECTDIR}/src/lsBufferObject.o \
	${OBJECTDIR}/src/lsColor.o \
	${OBJECTDIR}/src/lsContext.o \
	${OBJECTDIR}/src/lsDataResource.o \
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


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32 -Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -lSDL2main -flto -O3 -mwindows
CXXFLAGS=-m32 -Wall -Werror -Wextra -pedantic -pedantic-errors -msse -msse2 -lSDL2main -flto -O3 -mwindows

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglew32 -lopengl32 -lFreeImage -lfreetype -lSDL2 -lSDL2main ../hamlibs/HamLibs_NetBeans/../bin/WIN32/libhamlibs.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/lightsky.exe

bin/lightsky.exe: ../hamlibs/HamLibs_NetBeans/../bin/WIN32/libhamlibs.a

bin/lightsky.exe: ${OBJECTFILES}
	${MKDIR} -p bin
	${LINK.cc} -o bin/lightsky.exe ${OBJECTFILES} ${LDLIBSOPTIONS} -s

${OBJECTDIR}/fbState.o: fbState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fbState.o fbState.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/lightSky.o: src/lightSky.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lightSky.o src/lightSky.cpp

${OBJECTDIR}/src/lsAtlas.o: src/lsAtlas.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsAtlas.o src/lsAtlas.cpp

${OBJECTDIR}/src/lsBlender.o: src/lsBlender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBlender.o src/lsBlender.cpp

${OBJECTDIR}/src/lsBoundingBox.o: src/lsBoundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBoundingBox.o src/lsBoundingBox.cpp

${OBJECTDIR}/src/lsBufferObject.o: src/lsBufferObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsBufferObject.o src/lsBufferObject.cpp

${OBJECTDIR}/src/lsColor.o: src/lsColor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsColor.o src/lsColor.cpp

${OBJECTDIR}/src/lsContext.o: src/lsContext.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsContext.o src/lsContext.cpp

${OBJECTDIR}/src/lsDataResource.o: src/lsDataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDataResource.o src/lsDataResource.cpp

${OBJECTDIR}/src/lsDisplay.o: src/lsDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDisplay.o src/lsDisplay.cpp

${OBJECTDIR}/src/lsDrawModel.o: src/lsDrawModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsDrawModel.o src/lsDrawModel.cpp

${OBJECTDIR}/src/lsFontResource.o: src/lsFontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsFontResource.o src/lsFontResource.cpp

${OBJECTDIR}/src/lsFramebuffer.o: src/lsFramebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsFramebuffer.o src/lsFramebuffer.cpp

${OBJECTDIR}/src/lsGameState.o: src/lsGameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsGameState.o src/lsGameState.cpp

${OBJECTDIR}/src/lsGeometry.o: src/lsGeometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsGeometry.o src/lsGeometry.cpp

${OBJECTDIR}/src/lsImageResource.o: src/lsImageResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsImageResource.o src/lsImageResource.cpp

${OBJECTDIR}/src/lsManager.o: src/lsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsManager.o src/lsManager.cpp

${OBJECTDIR}/src/lsMatrixStack.o: src/lsMatrixStack.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMatrixStack.o src/lsMatrixStack.cpp

${OBJECTDIR}/src/lsMesh.o: src/lsMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMesh.o src/lsMesh.cpp

${OBJECTDIR}/src/lsMeshResource.o: src/lsMeshResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsMeshResource.o src/lsMeshResource.cpp

${OBJECTDIR}/src/lsRandom.o: src/lsRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsRandom.o src/lsRandom.cpp

${OBJECTDIR}/src/lsRenderer.o: src/lsRenderer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsRenderer.o src/lsRenderer.cpp

${OBJECTDIR}/src/lsResource.o: src/lsResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsResource.o src/lsResource.cpp

${OBJECTDIR}/src/lsSceneManager.o: src/lsSceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSceneManager.o src/lsSceneManager.cpp

${OBJECTDIR}/src/lsSetup.o: src/lsSetup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSetup.o src/lsSetup.cpp

${OBJECTDIR}/src/lsShaderObject.o: src/lsShaderObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsShaderObject.o src/lsShaderObject.cpp

${OBJECTDIR}/src/lsShaderProgram.o: src/lsShaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsShaderProgram.o src/lsShaderProgram.cpp

${OBJECTDIR}/src/lsSystem.o: src/lsSystem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsSystem.o src/lsSystem.cpp

${OBJECTDIR}/src/lsTexture.o: src/lsTexture.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsTexture.o src/lsTexture.cpp

${OBJECTDIR}/src/lsUtil.o: src/lsUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsUtil.o src/lsUtil.cpp

${OBJECTDIR}/src/lsVertex.o: src/lsVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsVertex.o src/lsVertex.cpp

${OBJECTDIR}/src/lsVertexArray.o: src/lsVertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -DSDL_MAIN_HANDLED -I../hamlibs/include -Iinclude -I../../../../../MinGW32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/lsVertexArray.o src/lsVertexArray.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/lightsky.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
