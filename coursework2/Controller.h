#pragma once
#include <SFML/Graphics.hpp>
#include "View.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();

public:
	void update();
	void render();
public:
	void gameRun();

private:
	sf::RenderWindow* window;
	sf::Event event;

	bool gameScreenIsOpen;
	GameScreen gameScreen;
};

