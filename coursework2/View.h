#pragma once
#include "FontManager.h"
#include <SFML/Graphics.hpp>
#include "View.h"
#include <Windows.h>
#include <string>
#include <vector>
#include "Figure.h"
#include <iostream>

using namespace std;

class Screen
{
public:
	virtual void render(sf::RenderWindow* window) = 0;
	virtual void update(sf::RenderWindow* window, sf::Event event) = 0;
protected:
	bool _rinning;

	FontManager fontManager;
	
	sf::Clock* clock;
	sf::Time time;
};


class GameScreen : public Screen
{
public:
	GameScreen();
	void render(sf::RenderWindow* window) override;
	void update(sf::RenderWindow* window, sf::Event event) override;

	bool isRunning() { return this->_rinning; };
	void setRunning(bool value) { this->_rinning = value; };

	void addFigure();

	bool waitingTime(sf::Event event);

	int playerType;
	enum playerTypes { cross_type, zero_type };

	bool needSend = false;
	bool needWalk = false;
	bool gameEnd = false;
	bool zeroWins = false;
private:
	void restart();
	void keyPressed(sf::Event event);

	sf::Time _time;
	sf::Clock* _clock;

	int currentItem;

	int starsCount = 5;
	std::vector<SfmlStar*> stars;

	sf::Sprite* crossWinsScreen;
};