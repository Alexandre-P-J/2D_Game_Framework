# 2D Game Engine

### Installation
  - Game code under game/src and game/include
  - Engine code under game/src and game/include
  - Create a separated folder and generate cmake files there (set the BITS variable to 64 to override the 32bit default)
  - On Linux (build for linux target) :
    - make
  - On Windows (build for windows target) :
    - Open the generated VS solution and build

The packaged game will be generated under a folder named PACKED

### Supported Platforms:
  - Linux 64bit (SDL2 and SDL2_image shared libraries required)
  - Linux 32bit (SDL2 and SDL2_image shared libraries required)
  - Windows WIP
