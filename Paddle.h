#pragma once
#include <SFML/graphics.hpp>
class Paddle
{
private:
	sf::RectangleShape m_Spape;
	sf::Vector2f m_Position;
	float m_Speed = 1100.0f;

	bool m_MovingLeft = false;
	bool m_MovingRight = false;

public: 
	Paddle(float startX, float startY);

	sf::RectangleShape getShape();
	sf::FloatRect getposition();

	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();

	void update(sf::Time dt);
};

