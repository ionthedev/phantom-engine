
#include "Core/Program.h"

#include "PhantomEngine.h"

#define MAX_COLUMNS 20

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    auto game = Phantom::CreateProgram();
    //game->Run();
    delete game;
}
