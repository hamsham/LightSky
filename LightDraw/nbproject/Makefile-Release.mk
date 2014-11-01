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
	${OBJECTDIR}/_ext/1644805454/atlas.o \
	${OBJECTDIR}/_ext/1644805454/blendObject.o \
	${OBJECTDIR}/_ext/1644805454/boundingBox.o \
	${OBJECTDIR}/_ext/1644805454/context.o \
	${OBJECTDIR}/_ext/1644805454/depthObject.o \
	${OBJECTDIR}/_ext/1644805454/display.o \
	${OBJECTDIR}/_ext/1644805454/fontResource.o \
	${OBJECTDIR}/_ext/1644805454/framebuffer.o \
	${OBJECTDIR}/_ext/1644805454/geometry.o \
	${OBJECTDIR}/_ext/1644805454/imageResource.o \
	${OBJECTDIR}/_ext/1644805454/matrixStack.o \
	${OBJECTDIR}/_ext/1644805454/mesh.o \
	${OBJECTDIR}/_ext/1644805454/meshModel.o \
	${OBJECTDIR}/_ext/1644805454/meshResource.o \
	${OBJECTDIR}/_ext/1644805454/sceneManager.o \
	${OBJECTDIR}/_ext/1644805454/setup.o \
	${OBJECTDIR}/_ext/1644805454/shaderObject.o \
	${OBJECTDIR}/_ext/1644805454/shaderProgram.o \
	${OBJECTDIR}/_ext/1644805454/texture.o \
	${OBJECTDIR}/_ext/1644805454/vertexArray.o \
	${OBJECTDIR}/_ext/1644805454/vertexBuffer.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightdraw.a

build/liblightdraw.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightdraw.a
	${AR} -rv build/liblightdraw.a ${OBJECTFILES} 
	$(RANLIB) build/liblightdraw.a

${OBJECTDIR}/_ext/1644805454/atlas.o: ../lightsky/draw/src/atlas.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/atlas.o ../lightsky/draw/src/atlas.cpp

${OBJECTDIR}/_ext/1644805454/blendObject.o: ../lightsky/draw/src/blendObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/blendObject.o ../lightsky/draw/src/blendObject.cpp

${OBJECTDIR}/_ext/1644805454/boundingBox.o: ../lightsky/draw/src/boundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/boundingBox.o ../lightsky/draw/src/boundingBox.cpp

${OBJECTDIR}/_ext/1644805454/context.o: ../lightsky/draw/src/context.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/context.o ../lightsky/draw/src/context.cpp

${OBJECTDIR}/_ext/1644805454/depthObject.o: ../lightsky/draw/src/depthObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/depthObject.o ../lightsky/draw/src/depthObject.cpp

${OBJECTDIR}/_ext/1644805454/display.o: ../lightsky/draw/src/display.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/display.o ../lightsky/draw/src/display.cpp

${OBJECTDIR}/_ext/1644805454/fontResource.o: ../lightsky/draw/src/fontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/fontResource.o ../lightsky/draw/src/fontResource.cpp

${OBJECTDIR}/_ext/1644805454/framebuffer.o: ../lightsky/draw/src/framebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/framebuffer.o ../lightsky/draw/src/framebuffer.cpp

${OBJECTDIR}/_ext/1644805454/geometry.o: ../lightsky/draw/src/geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/geometry.o ../lightsky/draw/src/geometry.cpp

${OBJECTDIR}/_ext/1644805454/imageResource.o: ../lightsky/draw/src/imageResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/imageResource.o ../lightsky/draw/src/imageResource.cpp

${OBJECTDIR}/_ext/1644805454/matrixStack.o: ../lightsky/draw/src/matrixStack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/matrixStack.o ../lightsky/draw/src/matrixStack.cpp

${OBJECTDIR}/_ext/1644805454/mesh.o: ../lightsky/draw/src/mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/mesh.o ../lightsky/draw/src/mesh.cpp

${OBJECTDIR}/_ext/1644805454/meshModel.o: ../lightsky/draw/src/meshModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/meshModel.o ../lightsky/draw/src/meshModel.cpp

${OBJECTDIR}/_ext/1644805454/meshResource.o: ../lightsky/draw/src/meshResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/meshResource.o ../lightsky/draw/src/meshResource.cpp

${OBJECTDIR}/_ext/1644805454/sceneManager.o: ../lightsky/draw/src/sceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/sceneManager.o ../lightsky/draw/src/sceneManager.cpp

${OBJECTDIR}/_ext/1644805454/setup.o: ../lightsky/draw/src/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/setup.o ../lightsky/draw/src/setup.cpp

${OBJECTDIR}/_ext/1644805454/shaderObject.o: ../lightsky/draw/src/shaderObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/shaderObject.o ../lightsky/draw/src/shaderObject.cpp

${OBJECTDIR}/_ext/1644805454/shaderProgram.o: ../lightsky/draw/src/shaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/shaderProgram.o ../lightsky/draw/src/shaderProgram.cpp

${OBJECTDIR}/_ext/1644805454/texture.o: ../lightsky/draw/src/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/texture.o ../lightsky/draw/src/texture.cpp

${OBJECTDIR}/_ext/1644805454/vertexArray.o: ../lightsky/draw/src/vertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/vertexArray.o ../lightsky/draw/src/vertexArray.cpp

${OBJECTDIR}/_ext/1644805454/vertexBuffer.o: ../lightsky/draw/src/vertexBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1644805454
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -I.. -I../../../../../../Qt/Tools/mingw482_32/i686-w64-mingw32/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1644805454/vertexBuffer.o ../lightsky/draw/src/vertexBuffer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightdraw.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
