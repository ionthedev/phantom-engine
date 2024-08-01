
#include "game/YourGame.h"


#define MAX_COLUMNS 20

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    //Initializes game and engine loop
    YourGame game(true);

    return 0;
}