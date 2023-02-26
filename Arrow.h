#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Arrow
{
private:
	sf::Sprite arrow;
	sf::Texture arrowTex;
	
	sf::Vector2f dirArrow;
	float movementSpeed;

	int dir;

	void initTexture();
	void initArrow();
public:
	Arrow(float dirPlayer, float posX, float posY, float dirX, float dirY, float movementspeed);
	virtual ~Arrow();

	//Accessor
	const sf::FloatRect getBounds() const;

	void updates();
	void render(sf::RenderTarget& target);
};

#endif // !ARROW_H

