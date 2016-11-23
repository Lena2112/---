#include "stdafx.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

unsigned int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 650;
const float BALL_RADIUS = 20.f, BALL_VELOCITY = 8.f;

struct Ball
{
	CircleShape shape;
	Vector2f velocity{ -BALL_VELOCITY, 0 };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(BALL_RADIUS);
		shape.setFillColor(Color::White);
	}

	void update()
	{
		shape.move(velocity);

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0 - BALL_RADIUS)
			velocity.x = -BALL_VELOCITY;
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < WINDOW_WIDTH - BALL_RADIUS)
			velocity.x = BALL_VELOCITY;
		else
			velocity.x = 0.f;
	}

	float x() 		{ return shape.getPosition().x; }
	float left() 	{ return x() - shape.getRadius(); }
	float right() 	{ return x() + shape.getRadius(); }
};

int main(int argc, char * argv[])
{
	Ball ball{ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT * 8 / 9.f };

	RenderWindow window{ { WINDOW_WIDTH, WINDOW_HEIGHT }, "Game" };
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		window.clear();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		ball.update();
		window.draw(ball.shape);
		window.display();
	}
	return 0;
}