#ifdef __unix__
    #define OS_Windows 0
    #undef main
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"

#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows 1
    #include "SDL.h"
    #include "SDL_image.h"
    
#endif

