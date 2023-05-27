#include "Controller.h"

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(900, 900), "laba");
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);


	this->gameScreen.setRunning(true);
}

Game::~Game()
{
	delete this->window;
}

void Game::gameRun()
{
	while (this->window->isOpen())
	{
		this->update();

		this->render();
	}
}

void Game::update()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
		}
	}

	if (this->gameScreen.isRunning() == true) {
		this->gameScreen.update(this->window, this->event);
	}
}

void Game::render()
{
	this->window->clear();

	if (this->gameScreen.isRunning() == true) {
		this->gameScreen.render(this->window);
	}

	this->window->display();
}
