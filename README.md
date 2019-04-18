# 2D Game Framework

This framework its at an early state, not yet usable for its purpose. See [To_Do](https://github.com/EvilPyro/2D_GameEngine/blob/master/TODO.md).
Do not use this Framework in production.

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
