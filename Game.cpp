#include "Game.h"

void Game::initGameState()
{
	this->GameState = 1;
	this->delaySel = 0;
}

//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Player Unknowed Battle Field I", sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initVariable()
{
	//Arrow
	this->speedArrow = 20.f;

	//Enemies
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
	
	//Score
	this->point = 0;
	this->hp = 30;
	this->hpMax = 30;
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Font/SF.ttf"))
	{
		std::cout << "ERROR::GAME::FONT::INITTEXTURE::Could not load font file." << "\n";
	}

	if (!this->fontcomic.loadFromFile("Font/SFcomic.ttf"))
	{
		std::cout << "ERROR::GAME::FONTCOMIC::INITTEXTURE::Could not load font file." << "\n";
	}
}

void Game::initGUI()
{
	//Scoreboard
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(50.f);

	//HP Bar
	this->hpBar.setSize(sf::Vector2f(300.f, 25.f));

	this->hpBarLoss = this->hpBar;
	this->hpBar.setFillColor(sf::Color::Green);
	this->hpBar.setPosition(905.f, 630.f);
	this->hpBar.setScale(0.3f, 0.3f);

	this->hpBarLoss = this->hpBar;
	this->hpBarLoss.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initMap()
{
	this->background = new Background();
}

void Game::initName()
{
	this->scoreName = new NameScore(true);
	this->scoreName->setFont(this->font);
	this->scoreName->setPosition({1920 / 2 - 210, 1080 / 2 - 80 });
	this->scoreName->setOutline(5, sf::Color::Black);
	this->scoreName->setLimit(true, 7);
}

void Game::initMenu()
{
	this->menu = new Menu();
}

void Game::initText()
{
	//BACK
	this->backText.setFont(this->font);
	this->backText.setPosition(50, 1080 / 2 + 450);
	this->backText.setString("<| Back(ESC)");
	this->backText.setFillColor(sf::Color::White);
	this->backText.setOutlineThickness(5);
	this->backText.setCharacterSize(50);

	//ENTER
	this->enterText.setFont(this->font);
	this->enterText.setPosition(1920 / 2 + 550, 1080 / 2 + 450);
	this->enterText.setString("Start(Enter) |>");
	this->enterText.setFillColor(sf::Color::White);
	this->enterText.setOutlineThickness(5);
	this->enterText.setCharacterSize(50);
}

void Game::initGameOver()
{
	//Game Over
	this->gameoverText.setFont(this->font);
	this->gameoverText.setCharacterSize(150);
	this->gameoverText.setFillColor(sf::Color::White);
	this->gameoverText.setOutlineColor(sf::Color::Black);
	this->gameoverText.setOutlineThickness(10);
	this->gameoverText.setString("Game Over");
	this->gameoverText.setPosition(this->window->getSize().x / 2.f - this->gameoverText.getGlobalBounds().width / 2.f, this->window->getSize().y / 2.f - this->gameoverText.getGlobalBounds().height / 2.f);

	//Game Over Explain
	this->gameoverExplain.setFont(this->font);
	this->gameoverExplain.setCharacterSize(50);
	this->gameoverExplain.setFillColor(sf::Color(169, 169, 169));
	this->gameoverExplain.setOutlineColor(sf::Color::Black);
	this->gameoverExplain.setOutlineThickness(5);
	this->gameoverExplain.setString("press  Enter  for  play  again  or  press  ESC  for  exit  to  main  menu");
	this->gameoverExplain.setPosition(120.f, 990.f);
}

//Con/Des
Game::Game()   
{
	this->initGameState();
	this->initMenu();
	this->initWindow();
	this->initVariable();
	this->initFont();
	this->initGUI();
	this->initMap();
	this->initPlayer();
	this->initName();
	this->initScoreboard();
	this->initText();
	this->initGameOver();
}

Game::~Game()
{
	delete this->window;
	delete this->background;
	delete this->player;
	
	//Delete enemies
	for (auto* i : this->enemy)
	{
		delete i;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		//Exit
		if (this->GameState == 0) this->window->close();

		//Menu
		else if (this->GameState == 1)
		{
			this->updateMenu();
			this->renderMenu();
		}

		//Game
		else if (this->GameState == 2)
		{
			this->updates();
			this->render();
		}

		//GameOver
		else if (this->GameState == 3)
		{
			this->restart();
			this->updateGameOver();
			this->renderGameOver();
		}

		//Scoreboard
		else if (this->GameState == 4)
		{
			this->scorePollEvent();
			this->renderScoreboard();
		}

		//Input Name
		else if (this->GameState == 5)
		{
			this->updateInputName();
			this->renderInputName();
		}
	}
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateEnemies()
{
	this->randomPos = rand() % 4;
	this->randomType = rand() % 3 + 1;

	//Spawn
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		if (this->randomPos == 0) this->enemy.push_back(new Enemies(this->randomType, rand() % 111 + 850, 0.f));
		if (this->randomPos == 1) this->enemy.push_back(new Enemies(this->randomType, 0.f, rand() % 61 + 620));
		if (this->randomPos == 2) this->enemy.push_back(new Enemies(this->randomType, rand() % 101 + 840 , 990.f));
		if (this->randomPos == 3) this->enemy.push_back(new Enemies(this->randomType, 1850.f, rand() % 91 + 510));
		this->spawnTimer = 0;
	}
	else this->spawnTimer += 0.2f;
	
	//Delete enemies
	unsigned counter = 0;
	for (auto* enemies : this->enemy)
	{
		enemies->updates();

		if (enemies->getPosition().x > 860.f && enemies->getPosition().x < 920.f && enemies->getPosition().y > 520.f && enemies->getPosition().y < 560.f)
		{
			//DAMAGE
			this->DmgToHp = enemies->getDamagetoHp();

			delete enemies;
			this->enemy.erase(this->enemy.begin() + counter);
			this->hp -= this->DmgToHp;
			--counter;
			break;
		}
		++counter;
	}

	if(this->spawnTimerMax >= 7.5f) this->spawnTimerMax -= 0.005f;
}

void Game::updateShooting()
{
	if (player->canAttack() == true)
	{
		if (player->DirPlayer() == 0) this->bullets.push_back(new Arrow(player->DirPlayer(), this->player->getPos().x+30, this->player->getPos().y, 0.f, -1.f, this->speedArrow));
		else if (player->DirPlayer() == 1) this->bullets.push_back(new Arrow(player->DirPlayer(), this->player->getPos().x, this->player->getPos().y+70, -1.f, 0.f, this->speedArrow));
		else if (player->DirPlayer() == 2) this->bullets.push_back(new Arrow(player->DirPlayer(), this->player->getPos().x+70, this->player->getPos().y, 0.f, 1.f, this->speedArrow));
		else if (player->DirPlayer() == 3) this->bullets.push_back(new Arrow(player->DirPlayer(), this->player->getPos().x, this->player->getPos().y+35, 1.f, 0.f, this->speedArrow));
	}

	unsigned counter = 0;
	for (auto* arrow : this->bullets)
	{
		arrow->updates();

		//Bullet culling (top of screen)
		if (arrow->getBounds().top + arrow->getBounds().height < 0.f)
		{
			//Delete bullets
			delete arrow;
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			break;
		}
		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemy.size(); ++i)
	{
		bool enemyDEL = false;
		for (size_t k = 0; k < this->bullets.size() && enemyDEL == false; k++)
		{
			if (this->enemy[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				delete this->enemy[i];
				this->enemy.erase(this->enemy.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				this->point++;

				enemyDEL = true;

				break;
			}
		}
	}
}

void Game::updateGUI()
{	
	//Score
	std::stringstream scr;
	scr <<"Point : " << this->point;
	this->scoreText.setString(scr.str());

	//HP
	float hpPercent = static_cast<float>(this->hp) / this->hpMax;
	this->hpBar.setSize(sf::Vector2f(300.f * hpPercent, this->hpBar.getSize().y));
	this->hpBar.setFillColor(sf::Color::Color(89, 197, 61));
}

void Game::updatePollEvent()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->GameState = 0;
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->GameState = 1; 
	}
}

void Game::updateInputName()
{
	this->delaySel++;

	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::TextEntered:
			this->scoreName->typedOn(ev);
		}
	}
	
	//INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->delaySel > 10)
	{
		this->GameState = 2;
		this->delaySel = 0;
		this->name = this->scoreName->getText();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->delaySel > 10)
	{
		this->menu->setToMenu(); 
		this->GameState = 1;
		this->delaySel = 0;
		this->initName();
	}
}

void Game::scorePollEvent()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
		{
			this->menu->setToMenu();
			this->GameState = 1;
		}
	}
}

void Game::updates()
{
	//Check Gameover
	if (this->hp <= 0)
	{
		this->initScoreboard();
		this->GameState = 3;
	}
	
	this->updatePollEvent();

	this->updateShooting();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();

	//Player
	this->updatePlayer();
	
	//Background
	this->background->updates();
}

void Game::renderScoreboard()
{
	this->window->clear();
	this->scoreboard->renderBackground(*this->window);
	this->window->draw(this->backText);
	this->scoreboard->render(*this->window);
	for (int i = 1; i <= 5; i++) {
		this->rankScore[i]->render(*this->window);
		this->rankName[i]->render(*this->window);
	}
	this->window->display();
}

void Game::renderInputName()
{
	this->window->clear();
	this->scoreName->render(*this->window);
	this->window->draw(this->backText);
	this->window->draw(this->enterText);
	this->window->display();
}

void Game::renderGUI()
{
	//Score
	this->window->draw(this->scoreText);

	//HP
	this->window->draw(this->hpBarLoss);
	this->window->draw(this->hpBar);
}

void Game::render()
{
	this->window->clear();
	this->background->render(*this->window);

	//Draw all the stuffs
	for (auto* arrow : this->bullets) arrow->render(*this->window);
	this->renderGUI();
	for (auto* enemies : this->enemy) enemies->render(*this->window);
	this->player->render(*this->window);

	this->window->display();
}

void Game::updateSelectMenu()
{
	this->GameState = this->menu->getGameState();
}

void Game::initScoreboard()
{
	char tempRank[255];
	int scoreRank[6];
	std::string nameRank[6];
	std::vector <std::pair<int, std::string>> userScore;

	this->scoreboard = new Scoreboard(this->window->getSize().x / 2 - 400, 25, "Scoreboard", &this->font);
	this->scoreboard->setFontColor(sf::Color(255, 215, 0));
	this->scoreboard->setFontSize(150);

	//Read
	this->scoreFile = fopen("Scoreboard/score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(this->scoreFile, "%s", &tempRank);
		nameRank[i] = tempRank;
		fscanf(this->scoreFile, "%d", &scoreRank[i]);
		userScore.push_back(std::make_pair(scoreRank[i], nameRank[i]));
	}
	nameRank[5] = this->name;
	scoreRank[5] = this->point;
	userScore.push_back(std::make_pair(scoreRank[5], nameRank[5]));
	sort(userScore.begin(), userScore.end());
	fclose(this->scoreFile);

	//Write
	fopen("Scoreboard/score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(tempRank, userScore[i].second.c_str());
		fprintf(this->scoreFile, "%s %d\n", tempRank, userScore[i].first);
	}
	fclose(this->scoreFile);

	for (int i = 1; i <= 5; i++)
	{
		this->rankName[i] = new Scoreboard(600, 800 - (i * 100), userScore[i].second, &this->font);
		this->rankScore[i] = new Scoreboard(1200, 800 - (i * 100), std::to_string(userScore[i].first), &this->font);
		if (i == 5)
		{
			this->rankName[i]->setFontColor(sf::Color::Red);
			this->rankScore[i]->setFontColor(sf::Color::Red);
		}
	}
}

void Game::updateMenu()
{
	this->updatePollEvent();

	this->updateSelectMenu();
	this->menu->updateInput();
}

void Game::renderMenu()
{
	this->window->clear();
	this->menu->render(*this->window);
	this->window->display();
}

void Game::updateGameOver()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		this->GameState = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->menu->setToMenu();
		this->GameState = 1;
	}
}

void Game::renderGameOver()
{
	this->window->clear();

	this->window->draw(this->background->getBGGameOver());
	this->window->draw(this->gameoverText);
	this->window->draw(this->gameoverExplain);

	this->window->display();
}

void Game::restart()
{
	this->initVariable();

	this->enemy.clear();
	this->bullets.clear();
}

