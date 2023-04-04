
#include "Game.h"

int main(int argc, char *argv[])
{
    Game game;
    bool Success = game.Initialize();
    if (Success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
