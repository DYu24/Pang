#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
	: _isLoaded(false)
{}

VisibleGameObject::~VisibleGameObject() {}

void VisibleGameObject::load(std::string filename) {
	if (_texture.loadFromFile(filename) == false) {
		_filename = "";
		_isLoaded = false;
	}
	else {
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::draw(sf::RenderWindow& renderWindow) {
	if (_isLoaded)
		renderWindow.draw(_sprite);
}

void VisibleGameObject::update(float elapsedTime) {}

void VisibleGameObject::setPosition(float x, float y) {
	if (_isLoaded)
		_sprite.setPosition(x, y);
}

sf::Vector2f VisibleGameObject::getPosition() const {
	if (_isLoaded)
		return _sprite.getPosition();
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::getSprite() {
	return _sprite;
}

bool VisibleGameObject::isLoaded() const {
	return _isLoaded;
}

float VisibleGameObject::getWidth() const {
	return _sprite.getGlobalBounds().width;
}

float VisibleGameObject::getHeight() const {
	return _sprite.getGlobalBounds().height;
}

sf::Rect<float> VisibleGameObject::getBoundingRect() const {
	/*
	sf::FloatRect size = _sprite.getGlobalBounds();
	sf::Vector2f position = _sprite.getPosition();
	return sf::Rect<float>(
		position.x - size.width / 2,
		position.y - size.height / 2,
		position.x + size.width / 2,
		position.y + size.height / 2
		);
	*/
	return _sprite.getGlobalBounds();
}