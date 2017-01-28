#!/bin/bash

set -o posix
set -o pipefail
set -ex

brew update
brew upgrade

brew outdated sdl2      || brew unlink sdl2      || 0; brew install sdl2
brew outdated freeimage || brew unlink freeimage || 0; brew install freeimage
brew outdated assimp    || brew unlink assimp    || 0; brew install assimp
brew outdated freetype  || brew unlink freetype  || 0; brew install freetype
brew outdated boost     || brew unlink boost     || 0; brew install boost
brew outdated glm       || brew unlink glm       || 0; brew install glm
