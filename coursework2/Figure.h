#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "FontManager.h"
#include <Windows.h>
#include <string>
#include <vector>


using namespace std;

class figure
{
public:
	sf::Sprite* getSprite() { return this->sprite; }

	float getX() { return x; }
	float getY() { return y; }
	int getSize() { return size; }

	virtual void setSize(int size) = 0 {};

	virtual void setY(float y) = 0 {};
	virtual void setX(float x) = 0 {};

protected:
	float x = 0;
	float y = 0;

	sf::Sprite* sprite;

	int size = 30;
};

class SfmlStar : public figure
{
public:
	SfmlStar() {
		this->sprite = TextureManager::load("img/star.jpg", size, size);
	};
	SfmlStar(float x, float y) {
		this->x = x;
		this->y = y;
		this->_x = x;
		this->_y = y;
		if (rand() % 100 < 50) {
			side = 1;

		}
		else {
			side = -1;
		}
		this->speed = (rand() % 100 + 100) / 100;
		this->sprite = TextureManager::load("img/star.png", size, size);
		this->sprite->setPosition(x, y);
	}

	void setSize(int size) override { 
		this->size = size;
		sprite->setScale(
			size / sprite->getLocalBounds().width,
			size / sprite->getLocalBounds().height);
	}
	void setX(float x) override {
		this->x = x;
		this->sprite->setPosition(x, this->y);
	}
	void setY(float y) override {
		this->y = y;
		this->sprite->setPosition(this->x, y);
	}
	void setActive(bool active) { 
		this->isActive = active; 
	}
	void setNumber(int number) {
		this->number = number;
	}
	void setSide(int side) {
		this->side = side;
	}

	void chengeColor() {
		this->sprite->setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
	}

	void render(sf::RenderWindow* window) {
		window->draw(*this->fontManager.getText(to_string(this->number), 20, sf::Color::White, x - 20, y + size/2 - 10));

		window->draw(*this->sprite);
	}

	int getNumber() { return number; }
	bool getActive() { return isActive; }
	int getSide() { return side; }

	void move(vector<SfmlStar*>& stars) {
		i += (speed * side);

		if (_x + round(r * cos(i * 3.1415 / 180)) < 0 || _x + round(r * cos(i * 3.1415 / 180)) > 900 - size ||
			_y + round(r * sin(i * 3.1415 / 180)) > 900 - size || _y + round(r * sin(i * 3.1415 / 180)) < 0) {
			setSide(side == 1 ? -1 : 1);

			i *= side;
		}

		for (int i = 0; i < stars.size(); i++) {
			if (stars[i]->getNumber() != number && x > stars[i]->getX() && x < stars[i]->getX() + stars[i]->getSize() &&
				y > stars[i]->getY() && y < stars[i]->getY() + stars[i]->getSize()) {
				setSide(side == 1 ? -1 : 1);

				i *= side;
			}
		}

		setX(_x + round(r * cos(i * 3.1415 / 180)));
		setY(_y + round(r * sin(i * 3.1415 / 180)));
	};
private:
	int i = 0;
	FontManager fontManager;
	int number = 0;
	int r = 150;
	bool isActive = false;

	float speed = 3.2;

	float _x = 0;
	float _y = 0;

	int side = 1;
};

