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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1019371010/atlas.o \
	${OBJECTDIR}/_ext/1019371010/blendObject.o \
	${OBJECTDIR}/_ext/1019371010/boundingBox.o \
	${OBJECTDIR}/_ext/1019371010/camera.o \
	${OBJECTDIR}/_ext/1019371010/color.o \
	${OBJECTDIR}/_ext/1019371010/defaultRenderStage.o \
	${OBJECTDIR}/_ext/1019371010/depthObject.o \
	${OBJECTDIR}/_ext/1019371010/drawCommand.o \
	${OBJECTDIR}/_ext/1019371010/fontResource.o \
	${OBJECTDIR}/_ext/1019371010/framebuffer.o \
	${OBJECTDIR}/_ext/1019371010/geometry.o \
	${OBJECTDIR}/_ext/1019371010/geometry_utils.o \
	${OBJECTDIR}/_ext/1019371010/imageResource.o \
	${OBJECTDIR}/_ext/1019371010/matrixStack.o \
	${OBJECTDIR}/_ext/1019371010/pickingBuffer.o \
	${OBJECTDIR}/_ext/1019371010/renderStage.o \
	${OBJECTDIR}/_ext/1019371010/renderbuffer.o \
	${OBJECTDIR}/_ext/1019371010/sceneGraph.o \
	${OBJECTDIR}/_ext/1019371010/sceneMesh.o \
	${OBJECTDIR}/_ext/1019371010/sceneNode.o \
	${OBJECTDIR}/_ext/1019371010/sceneResource.o \
	${OBJECTDIR}/_ext/1019371010/setup.o \
	${OBJECTDIR}/_ext/1019371010/shaderObject.o \
	${OBJECTDIR}/_ext/1019371010/shaderProgram.o \
	${OBJECTDIR}/_ext/1019371010/textRenderStage.o \
	${OBJECTDIR}/_ext/1019371010/texture.o \
	${OBJECTDIR}/_ext/1019371010/transform.o \
	${OBJECTDIR}/_ext/1019371010/vertexArray.o \
	${OBJECTDIR}/_ext/1019371010/vertexBuffer.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/liblightdraw_d.a

build/liblightdraw_d.a: ${OBJECTFILES}
	${MKDIR} -p build
	${RM} build/liblightdraw_d.a
	${AR} -rv build/liblightdraw_d.a ${OBJECTFILES} 
	$(RANLIB) build/liblightdraw_d.a

${OBJECTDIR}/_ext/1019371010/atlas.o: ../src/draw/atlas.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/atlas.o ../src/draw/atlas.cpp

${OBJECTDIR}/_ext/1019371010/blendObject.o: ../src/draw/blendObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/blendObject.o ../src/draw/blendObject.cpp

${OBJECTDIR}/_ext/1019371010/boundingBox.o: ../src/draw/boundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/boundingBox.o ../src/draw/boundingBox.cpp

${OBJECTDIR}/_ext/1019371010/camera.o: ../src/draw/camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/camera.o ../src/draw/camera.cpp

${OBJECTDIR}/_ext/1019371010/color.o: ../src/draw/color.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/color.o ../src/draw/color.cpp

${OBJECTDIR}/_ext/1019371010/defaultRenderStage.o: ../src/draw/defaultRenderStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/defaultRenderStage.o ../src/draw/defaultRenderStage.cpp

${OBJECTDIR}/_ext/1019371010/depthObject.o: ../src/draw/depthObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/depthObject.o ../src/draw/depthObject.cpp

${OBJECTDIR}/_ext/1019371010/drawCommand.o: ../src/draw/drawCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/drawCommand.o ../src/draw/drawCommand.cpp

${OBJECTDIR}/_ext/1019371010/fontResource.o: ../src/draw/fontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/fontResource.o ../src/draw/fontResource.cpp

${OBJECTDIR}/_ext/1019371010/framebuffer.o: ../src/draw/framebuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/framebuffer.o ../src/draw/framebuffer.cpp

${OBJECTDIR}/_ext/1019371010/geometry.o: ../src/draw/geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/geometry.o ../src/draw/geometry.cpp

${OBJECTDIR}/_ext/1019371010/geometry_utils.o: ../src/draw/geometry_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/geometry_utils.o ../src/draw/geometry_utils.cpp

${OBJECTDIR}/_ext/1019371010/imageResource.o: ../src/draw/imageResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/imageResource.o ../src/draw/imageResource.cpp

${OBJECTDIR}/_ext/1019371010/matrixStack.o: ../src/draw/matrixStack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/matrixStack.o ../src/draw/matrixStack.cpp

${OBJECTDIR}/_ext/1019371010/pickingBuffer.o: ../src/draw/pickingBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/pickingBuffer.o ../src/draw/pickingBuffer.cpp

${OBJECTDIR}/_ext/1019371010/renderStage.o: ../src/draw/renderStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/renderStage.o ../src/draw/renderStage.cpp

${OBJECTDIR}/_ext/1019371010/renderbuffer.o: ../src/draw/renderbuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/renderbuffer.o ../src/draw/renderbuffer.cpp

${OBJECTDIR}/_ext/1019371010/sceneGraph.o: ../src/draw/sceneGraph.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/sceneGraph.o ../src/draw/sceneGraph.cpp

${OBJECTDIR}/_ext/1019371010/sceneMesh.o: ../src/draw/sceneMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/sceneMesh.o ../src/draw/sceneMesh.cpp

${OBJECTDIR}/_ext/1019371010/sceneNode.o: ../src/draw/sceneNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/sceneNode.o ../src/draw/sceneNode.cpp

${OBJECTDIR}/_ext/1019371010/sceneResource.o: ../src/draw/sceneResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/sceneResource.o ../src/draw/sceneResource.cpp

${OBJECTDIR}/_ext/1019371010/setup.o: ../src/draw/setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/setup.o ../src/draw/setup.cpp

${OBJECTDIR}/_ext/1019371010/shaderObject.o: ../src/draw/shaderObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/shaderObject.o ../src/draw/shaderObject.cpp

${OBJECTDIR}/_ext/1019371010/shaderProgram.o: ../src/draw/shaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/shaderProgram.o ../src/draw/shaderProgram.cpp

${OBJECTDIR}/_ext/1019371010/textRenderStage.o: ../src/draw/textRenderStage.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/textRenderStage.o ../src/draw/textRenderStage.cpp

${OBJECTDIR}/_ext/1019371010/texture.o: ../src/draw/texture.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/texture.o ../src/draw/texture.cpp

${OBJECTDIR}/_ext/1019371010/transform.o: ../src/draw/transform.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/transform.o ../src/draw/transform.cpp

${OBJECTDIR}/_ext/1019371010/vertexArray.o: ../src/draw/vertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/vertexArray.o ../src/draw/vertexArray.cpp

${OBJECTDIR}/_ext/1019371010/vertexBuffer.o: ../src/draw/vertexBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1019371010
	${RM} "$@.d"
	$(COMPILE.cc) -g -DLS_DEBUG -I../include -I/usr/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1019371010/vertexBuffer.o ../src/draw/vertexBuffer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/liblightdraw_d.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
