#pragma once

class VisibleGameObject {
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();
	
	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow &window);
	virtual void Update(float) = 0;
	virtual void Reset();

	virtual void SetPosition(float x, float y);
	virtual void SetDefaultPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;

	virtual float GetHeight() const;
	virtual float GetWidth() const;

	virtual sf::Rect<float> GetBoundingRect() const;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite _sprite;
	sf::Image _image;
	sf::Texture _texture;
	std::string _fileName;
	bool _isLoaded;
	sf::Vector2f _defaultPosition;
};