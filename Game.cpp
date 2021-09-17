#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initShapes();
	this->initFont();
}

Game::~Game()
{

}

void Game::initShapes()
{
	//Player1
	this->player1 = new sf::RectangleShape;
	this->player1->setPosition(player1Pos);
	this->player1->setFillColor(sf::Color::Green);
	this->player1->setOutlineColor(sf::Color::White);
	this->player1->setOutlineThickness(2.f);
	this->player1->setSize(player1Size);

	//Player2
	this->player2 = new sf::RectangleShape;
	this->player2->setPosition(player2Pos);
	this->player2->setFillColor(sf::Color::Cyan);
	this->player2->setOutlineColor(sf::Color::White);
	this->player2->setOutlineThickness(2.f);
	this->player2->setSize(player2Size);

	//Ball
	this->ball = new sf::CircleShape;
	this->ball->setPosition(ballPos);
	this->ball->setFillColor(sf::Color::Red);
	this->ball->setRadius(ballRadius);
	this->ball->setOutlineColor(sf::Color::Yellow);
	this->ball->setOutlineThickness(1.f);
}

void Game::initFont()
{
	//Font
	this->font = new sf::Font;

	if (!font->loadFromFile("pixel.ttf"))
		std::cout << "Unable to load Font";

	//Player 1 Text
	this->player1Text = new sf::Text;
	this->player1WinText = new sf::Text;
	this->player1Text->setFont(*font);
	this->player1Text->setFillColor(sf::Color::Cyan);
	this->player1Text->setCharacterSize(10);
	this->player1Text->setPosition(sf::Vector2f(10.f, 10.f));
	this->player1WinText->setFont(*font);
	this->player1WinText->setString("Player 2 Wins! \nThank You For Playing \nMade By Shivansh Ahuja");
	this->player1WinText->setFillColor(sf::Color::Red);
	this->player1WinText->setCharacterSize(50);
	this->player1WinText->setPosition(sf::Vector2f(videoMode.width / 2 - 300.f, videoMode.height / 2 - 100.f));

	//Player 2 Text
	this->player2Text = new sf::Text;
	this->player2WinText = new sf::Text;
	this->player2Text->setFont(*font);
	this->player2Text->setFillColor(sf::Color::Green);
	this->player2Text->setCharacterSize(10);
	this->player2Text->setPosition(sf::Vector2f(10.f, 700.f));
	this->player2WinText->setFont(*font);
	this->player2WinText->setString("Player 1 Wins! \nThank You For Playing \nMade By Shivansh Ahuja");
	this->player2WinText->setFillColor(sf::Color::Red);
	this->player2WinText->setCharacterSize(50);
	this->player2WinText->setPosition(sf::Vector2f(videoMode.width / 2 - 300.f, videoMode.height / 2 - 100.f));
}

void Game::initWindow()
{
	this->videoMode.width = 1280;
	this->videoMode.height = 720;

	this->window = new sf::RenderWindow(this->videoMode, "PingPong", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(144);
}

void Game::initVariables()
{
	//Player1Parameters
	this->player1Size.x = 200.f;
	this->player1Size.y = 25.f;
	this->player1Pos.x = this->videoMode.width / 2 - 100.f;
	this->player1Pos.y = this->videoMode.height / 2 + 300.f;
	this->player1Velocity = 6.0f;

	//Player2Parameters
	this->player2Size.x = 200.f;
	this->player2Size.y = 25.f;
	this->player2Pos.x = this->videoMode.width / 2 - 100.f;
	this->player2Pos.y = this->videoMode.height / 2 - 330.f;
	this->player2Velocity = 6.0f;

	//BallParameters
	this->ballRadius = 5.f;
	this->ballPos.x = this->videoMode.width / 2 - 10.f;
	this->ballPos.y = this->videoMode.height / 2 + 275.f;
	this->ballVelocity.y = 3.0f;
	this->ballVelocity.x = 3.0f;

	this->moveBall = false;
	this->player1Points = 0;
	this->player2Points = 0;
	this->player1Health = 3;
	this->player2Health = 3;

	this->endGame = false;
}

void Game::handleEvents()
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				this->window->close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				moveBall = true;
			break;

		default:
			break;
		}
	}

	std::stringstream ss1;
	std::stringstream ss2;

	ss1 << "Points: " << this->player1Points << "\t" << "Health: " << this->player1Health;
	this->player1Text->setString(ss1.str());

	ss2 << "Points: " << this->player2Points << "\t" << "Health: " << this->player2Health;
	this->player2Text->setString(ss2.str());
}

void Game::checkCollision(sf::CircleShape* circle, sf::RectangleShape* rectangle)
{
	if ((circle->getPosition().y + circle->getRadius()) >= (rectangle->getPosition().y) &&
		(circle->getPosition().y - circle->getRadius()) < (rectangle->getPosition().y + (rectangle->getSize().y )) &&
		(circle->getPosition().x + circle->getRadius()) > (rectangle->getPosition().x) &&
		(circle->getPosition().x - circle->getRadius()) < (rectangle->getPosition().x + (rectangle->getSize().x )))
	{
		ballVelocity.y *= -1;
		ballVelocity.x = (((circle->getPosition().x - (rectangle->getPosition().x + (rectangle->getSize().x/2))) / (rectangle->getSize().x / 2))) * 4;
	}
}


void Game::ballPhysics()
{
	this->ball->move(this->ballVelocity.x, -this->ballVelocity.y);

	if (ball->getPosition().x <= 0.f)
		this->ballVelocity.x *= -1;
		
	if (ball->getPosition().x >= this->videoMode.width)
		this->ballVelocity.x *= -1;

	if (ball->getPosition().y < 0.f)
	{
		this->resetBall();
		this->player2Points += 5;
		this->player1Health--;
	}

	if (ball->getPosition().y > this->videoMode.height)
	{
		this->resetBall();
		this->player1Points += 5;
		this->player2Health--;
	};

	this->checkCollision(this->ball, this->player1);
	this->checkCollision(this->ball, this->player2);
}

void Game::playerPhysics()
{
	//Player 1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player1->move(-player1Velocity, 0.f);
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player1->move(player1Velocity, 0.f);
	
	if (player1->getPosition().x <= 0.f)
		player1->setPosition(0.f, player1Pos.y);
	if (player1->getPosition().x >= videoMode.width - player1Size.x)
		player1->setPosition(videoMode.width - player1Size.x, player1Pos.y);

	//Player2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->player2->move(-player2Velocity, 0.f);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player2->move(player2Velocity, 0.f);

	if (player2->getPosition().x <= 0.f)
		player2->setPosition(0.f, player2Pos.y);
	if (player2->getPosition().x >= videoMode.width - player2Size.x)
		player2->setPosition(videoMode.width - player2Size.x, player2Pos.y);
}

void Game::resetBall()
{
	moveBall = false;
	this->ball->setPosition(sf::Vector2f(videoMode.width / 2, videoMode.height / 2));
}

void Game::update()
{
	this->handleEvents();
	this->playerPhysics();

	if (moveBall)
	{
		this->ballPhysics();
	}

	if (player1Health == 0 || player2Health == 0)
		endGame = true;
}

void Game::render()
{
	this->window->clear();

	if (!endGame)
	{
		this->window->draw(*player1);
		this->window->draw(*player2);
		this->window->draw(*ball);
		this->window->draw(*player1Text);
		this->window->draw(*player2Text);
	}

	if(endGame && player1Health == 0)
		this->window->draw(*player2WinText);

	else if (endGame && player2Health == 0)
		this->window->draw(*player1WinText);

	this->window->display();
}

const bool Game::running() const
{
	return this->window->isOpen();
}
