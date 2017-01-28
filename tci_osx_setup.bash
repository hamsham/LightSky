#!/bin/bash

set -o posix
set -o pipefail
set -ex

brew update
brew upgrade

brew outdated sdl2      || brew unlink sdl2      || brew install sdl2
brew outdated freeimage || brew unlink freeimage || brew install freeimage
brew outdated assimp    || brew unlink assimp    || brew install assimp
brew outdated freetype  || brew unlink freetype  || brew install freetype
brew outdated boost     || brew unlink boost     || brew install boost
brew outdated glm       || brew unlink glm       || brew install glm
