[![Build Status](https://travis-ci.org/jhartell/monorun-sdl.svg?branch=master)](https://travis-ci.org/jhartell/monorun-sdl)

# Monorun-sdl #
An SDL game based on the Javascript game [Monorun!](https://github.com/beije/monorun) by Benjamin Horn.

## Dependencies ##
* libSDL2
* libSDL2_image

## Installation ##
The package is built using GNU Autotools.
```
./autogen.sh
./configure
make
make install
```

## Todo ##
- Implement start and end screens
- Make `make install` work properly with graphics
- Images are currently loaded from the working dir, support installed paths
- Fullscreen support
- Draw thicker lines between Rolands
- Implement highscore (?)
- Cross platform support
