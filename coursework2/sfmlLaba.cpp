#include "Controller.h"

using namespace sf;
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "RU");

	Game game;

	game.gameRun();
}