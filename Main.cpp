#include "Game.h"
#include <time.h>

int main()
{
    Game game;

    srand(static_cast<unsigned>(time(0)));

    game.run();

    return 0;
}