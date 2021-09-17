#pragma once

#include<iostream>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::RectangleShape* player1;
	sf::Vector2f player1Size;
	sf::Vector2f player1Pos;
	float player1Velocity;
	int player1Health;

	sf::RectangleShape* player2;
	sf::Vector2f player2Size;
	sf::Vector2f player2Pos;
	float player2Velocity;
	int player2Health;

	sf::CircleShape* ball;
	sf::Vector2f ballPos;
	float ballRadius;
	sf::Vector2f ballVelocity;
	bool moveBall;

	sf::Font* font;
	sf::Text* player1Text;
	sf::Text* player2Text;
	sf::Text* player1WinText;
	sf::Text* player2WinText;
	int player1Points;
	int player2Points;

	bool endGame;

	void initWindow();
	void initVariables();
	void initShapes();
	void initFont();
	void handleEvents();
	void checkCollision(sf::CircleShape* circle, sf::RectangleShape* rectangle);

	void ballPhysics();
	void playerPhysics();
	void resetBall();
public:
	Game();
	virtual ~Game();

	void update();
	void render();

	const bool running() const;
};