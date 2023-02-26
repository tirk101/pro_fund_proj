#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Background.h"
#include "Player.h"
#include "Enemies.h"
#include "Arrow.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "NameScore.h"
#include <sstream>
#include <string.h>


class Game
{
private:
	//Game State
	int GameState;
	/*
		gamestate 0 = Exit
		gamestate 1 = Menu
		gamestate 2 = Play
		gamestate 3 = Gameover
		gamestate 4 = Scoreboard
		gamestate 5 = NameInput
	*/

	//Menu
	Menu* menu;

	//Window
	sf::RenderWindow* window;
	
	//Player
	Player* player;

	//Map
	Background* background;

	//Enemies
	Enemies* enemies;
	std::vector<Enemies*> enemy;
	int randomPos;
	int randomType;
	float spawnTimer;
	float spawnTimerMax;
	int DmgToHp;
	int HpEnemy;

	//Arrow
	Arrow* arrow;
	std::vector<Arrow*> bullets;
	float speedArrow;

	//GUI
	sf::Font font;
	sf::Font fontcomic;
	sf::Text scoreText;
	unsigned int point;
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarLoss;
	int hp;
	int hpMax;

	//GameOver
	sf::Text gameoverText;
	sf::Text gameoverExplain;

	//Scoreboard
	sf::Text backText;
	sf::Text enterText;
	NameScore* scoreName;
	std::string name;
	Scoreboard* scoreboard;
	Scoreboard* rankName[6];
	Scoreboard* rankScore[6];
	FILE* scoreFile;
	int delaySel;

	//Private functions
	void initGameState();
	void initWindow();
	void initVariable();
	void initFont();
	void initGUI();
	void initPlayer();
	void initMap();
	void initName();
	void initMenu();
	void initText();
	void initGameOver();
public: 
	Game();
	virtual ~Game();
	
	//Main functions
	void run();

	//Player
	void updatePlayer();

	//Enemies
	void updateEnemies();
	void updateShooting();
	void updateCombat();

	//GUI
	void updateGUI();
	void renderGUI();
	
	//Game
	void updatePollEvent();
	void updates();
	void render();
	
	//InputName
	void updateInputName();
	void renderInputName();

	//Scoreboard
	void initScoreboard();
	void scorePollEvent();
	void renderScoreboard();

	//Menu
	void updateSelectMenu();
	void updateMenu();
	void renderMenu();

	//Game Over
	void updateGameOver();
	void renderGameOver();

	//RESTART!!!
	void restart();
};

