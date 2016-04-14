
#include "Game.h"

int main( int argc, char* args[] )
{
    Game* game = new Game();

    while(!game->isClosed()) {
        game->handleEvents();

    }

    delete game;

	return 0;
}
