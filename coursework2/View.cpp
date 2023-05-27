#include "View.h"

GameScreen::GameScreen() {
	this->crossWinsScreen = TextureManager::load("img/1.jpg", 900, 900);
	this->clock = new sf::Clock;
	this->_clock = new sf::Clock;

	for (int i = 0; i < starsCount; i++) {
		this->stars.push_back(new SfmlStar(rand() % 300 + 400, rand() % 300 + 300));
		this->stars[i]->setNumber(i);
	}
	this->stars[0]->setActive(true);

	this->restart();
}

void GameScreen::render(sf::RenderWindow* window)
{
	for (int i = 0; i < starsCount; i++) {
		if (this->stars[i]->getActive() == true) {
			window->draw(*this->fontManager.getText(L"активна€ звезда:", 20, sf::Color::White, 0, 0));
			window->draw(*this->fontManager.getText(to_string(this->stars[i]->getNumber()), 20, sf::Color::White, 0, 20));

			window->draw(*this->fontManager.getText(L"размер:", 20, sf::Color::White, 0, 40));
			window->draw(*this->fontManager.getText(to_string(this->stars[i]->getSize()) + "px", 20, sf::Color::White, 0, 60));
		}
	}

	window->draw(*this->fontManager.getText(L"1 - изменить цвет\n2 - сменить фигуру\n3 - изменить размер\n4 - вправо\n5 - влево\n6 - вниз\n7 - вверх\n8 - сменить\nнапрадение вращени€\n9 - добавить фигуру", 20, sf::Color::White, 0, 100));

	for (int i = 0; i < starsCount; i++) {
		this->stars[i]->render(window);
	}
}

void GameScreen::update(sf::RenderWindow* window, sf::Event event)
{
	if (this->waitingTime(event) == true) {
		keyPressed(event);
		for (int i = 0; i < this->starsCount; i++) {
			this->stars[i]->move(stars);
		}
	}
}

void GameScreen::addFigure()
{
	if (this->starsCount < 10) {
		this->starsCount++;
		this->stars.push_back(new SfmlStar(rand() % 300 + 400, rand() % 300 + 300));
		this->stars[this->stars.size() - 1]->setNumber(this->stars.size() - 1);
	}
}

bool GameScreen::waitingTime(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) {
		this->time = sf::seconds(2);
	}
	this->time = this->clock->getElapsedTime();
	return (this->time.asMilliseconds() >= 200);
}


void GameScreen::keyPressed(sf::Event event)
{
	for (int i = sf::Keyboard::Num0; i <= sf::Keyboard::Num9; i++) {
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
			this->clock->restart();

			if (i == 27) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->chengeColor();
					}
				}
			}
			else if (i == 28) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->setActive(false);
						this->stars[(j + 1) % this->starsCount]->setActive(true);
						break;
					}
				}
			}
			else if (i == 29) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->setSize(this->stars[j]->getSize() + 1);
						break;
					}
				}
			}
			else if (i == 30) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->setX(this->stars[j]->getX() + 1);
						break;
					}
				}
			}
			else if (i == 31) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->setX(this->stars[j]->getX() - 1);
						break;
					}
				}
			}
			else if (i == 32) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->setY(this->stars[j]->getY() + 1);
						break;
					}
				}
			}
			else if (i == 33) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->setY(this->stars[j]->getY() - 1);
						break;
					}
				}
			}
			else if (i == 34) {
				for (int j = 0; j < this->starsCount; j++) {
					if (this->stars[j]->getActive() == true) {
						this->stars[j]->setSide(this->stars[j]->getSide() == 1 ? -1 : 1);
						break;
					}
				}
			}
			else if (i == 35) {
				addFigure();
			}

			break;
		}
	}
}

void GameScreen::restart()
{
	this->clock->restart();
	this->_clock->restart();
	this->time = sf::microseconds(0);
	this->_time = sf::microseconds(0);
	this->_rinning = false;
	this->currentItem = 0;
}


