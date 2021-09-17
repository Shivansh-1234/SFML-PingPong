#include "Game.h"

Game* game = new Game();

int main()
{
	while (game->running())
	{
		game->update();
		game->render();
	}
}