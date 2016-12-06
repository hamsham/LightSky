# LightSky

[![Build Status](https://travis-ci.org/hamsham/LightSky.svg?branch=master)](https://travis-ci.org/hamsham/LightSky)

A portable game development framework using OpenGL 3.3 and OpenGLES 3.0. LightSky includes the following submodules:
 * LightSetup - Compiler macros and compile-time platform definitions.
 * LightUtils - Commonly shared classes and functions used throughout LS.
 * LightMath - A basic linear algebra library with compile-time math operations.
 * LightDraw - The OpenGL abstraction layer for supporting both Desktop & Mobile GL.
 * LightGame - LightSky's game development framework for implementing common application-level subroutines.

This is the top-level project from whcih all other related libs should be built through. All LightSky submodules should be cloned using "--recurse-submodules".
