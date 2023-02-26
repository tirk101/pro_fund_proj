#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Background
{
private:
	//MAP
	sf::Texture bgTexture;
	sf::Sprite background;
	sf::Sprite bgGameOver;

	//Portal
	sf::Texture portalTexture;
	sf::Sprite portal;
	sf::IntRect portalFrame;
	sf::Clock portalTimer;

	//Private Functions
	void initTexture();
	void initVariables();
	void initBackground();

public:
	Background();
	virtual ~Background();

	//Accessor
	const sf::FloatRect getBoundsPortal() const;
	const sf::Sprite getBGGameOver() const;
	
	//functions
	void animPortal();
	void updates();
	void render(sf::RenderTarget& target);
};

