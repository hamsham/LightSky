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
	${OBJECTDIR}/bufferObject.o \
	${OBJECTDIR}/color.o \
	${OBJECTDIR}/dataResource.o \
	${OBJECTDIR}/display.o \
	${OBJECTDIR}/fontResource.o \
	${OBJECTDIR}/gameState.o \
	${OBJECTDIR}/geometry.o \
	${OBJECTDIR}/imageResource.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/manager.o \
	${OBJECTDIR}/matrixStack.o \
	${OBJECTDIR}/mesh.o \
	${OBJECTDIR}/meshResource.o \
	${OBJECTDIR}/renderer.o \
	${OBJECTDIR}/resource.o \
	${OBJECTDIR}/sceneManager.o \
	${OBJECTDIR}/shaderObject.o \
	${OBJECTDIR}/shaderProgram.o \
	${OBJECTDIR}/system.o \
	${OBJECTDIR}/testState.o \
	${OBJECTDIR}/text.o \
	${OBJECTDIR}/texture.o \
	${OBJECTDIR}/textureAtlas.o \
	${OBJECTDIR}/util.o \
	${OBJECTDIR}/vertex.o \
	${OBJECTDIR}/vertexArray.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32 -Wall -Werror -Wextra -pedantic -pedantic-errors -flto
CXXFLAGS=-m32 -Wall -Werror -Wextra -pedantic -pedantic-errors -flto

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
	${LINK.cc} -o bin/lightsky ${OBJECTFILES} ${LDLIBSOPTIONS} -s

${OBJECTDIR}/bufferObject.o: bufferObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bufferObject.o bufferObject.cpp

${OBJECTDIR}/color.o: color.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/color.o color.cpp

${OBJECTDIR}/dataResource.o: dataResource.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dataResource.o dataResource.cpp

${OBJECTDIR}/display.o: display.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/display.o display.cpp

${OBJECTDIR}/fontResource.o: fontResource.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fontResource.o fontResource.cpp

${OBJECTDIR}/gameState.o: gameState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gameState.o gameState.cpp

${OBJECTDIR}/geometry.o: geometry.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/geometry.o geometry.cpp

${OBJECTDIR}/imageResource.o: imageResource.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/imageResource.o imageResource.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/manager.o: manager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/manager.o manager.cpp

${OBJECTDIR}/matrixStack.o: matrixStack.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/matrixStack.o matrixStack.cpp

${OBJECTDIR}/mesh.o: mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mesh.o mesh.cpp

${OBJECTDIR}/meshResource.o: meshResource.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/meshResource.o meshResource.cpp

${OBJECTDIR}/renderer.o: renderer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renderer.o renderer.cpp

${OBJECTDIR}/resource.o: resource.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/resource.o resource.cpp

${OBJECTDIR}/sceneManager.o: sceneManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sceneManager.o sceneManager.cpp

${OBJECTDIR}/shaderObject.o: shaderObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/shaderObject.o shaderObject.cpp

${OBJECTDIR}/shaderProgram.o: shaderProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/shaderProgram.o shaderProgram.cpp

${OBJECTDIR}/system.o: system.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system.o system.cpp

${OBJECTDIR}/testState.o: testState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/testState.o testState.cpp

${OBJECTDIR}/text.o: text.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/text.o text.cpp

${OBJECTDIR}/texture.o: texture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/texture.o texture.cpp

${OBJECTDIR}/textureAtlas.o: textureAtlas.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/textureAtlas.o textureAtlas.cpp

${OBJECTDIR}/util.o: util.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util.o util.cpp

${OBJECTDIR}/vertex.o: vertex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vertex.o vertex.cpp

${OBJECTDIR}/vertexArray.o: vertexArray.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Wall -s -I../hamlibs/include -I/C/mingw/include/freetype2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vertexArray.o vertexArray.cpp

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
