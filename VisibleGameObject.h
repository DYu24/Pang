#pragma once
class VisibleGameObject {
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();
	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow& renderWindow);
	virtual void setPosition(float x, float y);
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
};