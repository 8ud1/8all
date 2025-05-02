#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	if (!game.Start("8all Game"))
	{
		return -1;
	}

	game.Run();
	game.Cleanup();

	return 0;
}