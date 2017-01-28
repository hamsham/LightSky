#!/bin/bash

set -o posix
set -o pipefail
set -ex

brew update
brew upgrade
brew outdated sdl2      || brew install sdl2
brew outdated freeimage || brew install freeimage
brew outdated assimp    || brew install assimp
brew outdated freetype  || brew install freetype
brew outdated boost     || brew install boost
brew outdated glm       || brew install glm
