#include "Paddle.h"

Paddle::Paddle(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Spape.setSize(sf::Vector2f(50, 5));
	m_Spape.setFillColor(sf::Color::Magenta);
	m_Spape.setOutlineColor(sf::Color::White);
	m_Spape.setOutlineThickness(3);

	m_Spape.setPosition(m_Position);

}

sf::FloatRect Paddle::getposition() {

	return m_Spape.getGlobalBounds();
}

sf::RectangleShape Paddle::getShape()
{
	return m_Spape;
}

void Paddle::moveLeft()
{
	m_MovingLeft = true;
}

void Paddle::moveRight()
{
	m_MovingRight = true;
}

void Paddle::stopLeft()
{
	m_MovingLeft = false;
}

 void Paddle::stopRight(){
	m_MovingRight = false;
}

 void Paddle::update(sf::Time dt)
 {
	 if (m_MovingLeft)
	 {
		 m_Position.x -= m_Speed * dt.asSeconds();
	 }


	 if (m_MovingRight)
	 {
		 m_Position.x += m_Speed * dt.asSeconds();
	 }

	 m_Spape.setPosition(m_Position);
 }