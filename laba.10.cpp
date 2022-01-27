#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;


class Player {
public:
	float x, y, w, h, dx, dy, speed = 0;
	int dir = 0; // направление игрока
	String File;
	Image i;
	Texture t;
	Sprite s;
	Player(String F, float X, float Y, float W, float H) {
		dx = 0; dy = 0; speed = 0; dir = 0;
		File = F;
		w = W; h = H;
		i.loadFromFile("images/" + File);
		i.createMaskFromColor(Color(41, 33, 59));
		t.loadFromImage(i);
		s.setTexture(t);
		x = X; y = Y;
		s.setTextureRect(IntRect(0, 0, w, h));
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;    // чтобы не ходил по диагонали
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0; // зануляем чтобы персонаж останавливался после отпуска кнопки
		s.setPosition(x, y);
	}
};

class Circle {
private:
	int radius;
	int x;
	int y;
public:
	int getRadius() {
		return radius;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setRadius(int valueRadius) {
		radius = valueRadius;
	}
	void setX(int valueX) {
		x = valueX;
	}
	void setY(int valueY) {
		y = valueY;
	}
};


int main()
{
	RenderWindow window(VideoMode(840, 840), "Karaban");

	Player p("hero.png", 250, 250, 96.0, 96.0);

	Circle ball;

	ball.setRadius(10);
	ball.setX(rand() % 840);
	ball.setY(rand() % 840);
	Clock c;

	float CurrentFrame = 0;
	while (window.isOpen()) {
		float time = c.getElapsedTime().asMicroseconds();
		c.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}


		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.15;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.s.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.15;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.s.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.15;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.s.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			p.dir = 2; p.speed = 0.15;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.s.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));

		}

		p.update(time);

		window.clear();
		window.draw(p.s);
		window.display();

	}
	return 0;
}
