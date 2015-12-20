#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject()
	:_isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject(){}

void VisibleGameObject::Load(std::string filename) {
	if (!_image.loadFromFile(filename)) {
		_fileName = "";
		_isLoaded = false;
	}
	else {
		_fileName = filename;
		_texture.loadFromImage(_image);
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow &window) {
	if (_isLoaded) {
		window.draw(_sprite);
	}
}

void VisibleGameObject::Reset() {
	SetPosition(_defaultPosition.x, _defaultPosition.y);
}

void VisibleGameObject::SetPosition(float x, float y) {
	if (_isLoaded) {
		_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::SetDefaultPosition(float x, float y) {
	_defaultPosition = { x, y };
	SetPosition(x, y);
}

sf::Vector2f VisibleGameObject::GetPosition() const {
	if (_isLoaded) {
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite() {
	return _sprite;
}

bool VisibleGameObject::IsLoaded() const {
	return _isLoaded;
}

float VisibleGameObject::GetWidth() const {
	return _sprite.getLocalBounds().width;
}

float VisibleGameObject::GetHeight() const {
	return _sprite.getLocalBounds().height;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const {
	return _sprite.getGlobalBounds();
}
