#include <time.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <dos.h>
#include <fstream>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace sf;

int score, currentSel, buyz, ptitsa;

void zapis(int x)
{
	std::ofstream chet("Chet.txt");
	chet << x;
	chet.close();
	std::ifstream vivod("chet.txt");
	vivod >> score;
	vivod.close();
}

void currentBird(int x)
{
	std::ofstream currentBird("Current.txt");
	currentBird << x;
	currentBird.close();

}

void buy(int x)
{
	std::ofstream buys("Buy.txt");
	buys << x;
	buys.close();
}

int Incialize(int &xBird, int &height, float &xPic, float &xPic2, float &x, float &y)
{
	height = rand() % 320, xBird = 150, xPic = 0, xPic2 = 699, x = 710, y = 200;
	return xBird, height, xPic, xPic2, x, y;
}

class textur
{
public:
	String Directory;
	Texture Tex;
	Sprite Spr;
	textur(String Di)
	{
		Directory = Di;
		Tex.loadFromFile("images/" + Di);
		Spr.setTexture(Tex);
	}
};

int main()
{
	srand(time(NULL));
	int timerlose = 0, timercoin = 0, TexSto = 0, Men = 1, height = 0, xBird = 0;
	bool rul = false, market = false;
	float Frame = 5.8, FrameCoin = 0, TIMER = 0, y = 200, coins[2][2], x = 710, xPic = 0, xPic2 = 0;

	Incialize(xBird, height, xPic, xPic2, x, y);

	RenderWindow window(VideoMode(700, 400), "Runner");
	Time t = microseconds(3500), minus = microseconds(0.1), tt = microseconds(0.1);
	Time lose = seconds(2);
	Clock clock;
	coins[0][0] = 1200;
	coins[1][0] = rand() % 370;

	Font font;
	font.loadFromFile("aalbionictitulbrk_bold.ttf");
	Text text("", font, 30), select("", font, 30), buy1("", font, 20);
	select.setColor(Color::Red);
	buy1.setString("купить за 500 \n\n    монет?");
	buy1.setPosition(390, 230);
	buy1.setColor(Color::Red);

	textur background("background.png"), MenuS("menu.png"), RuleS("rule.png"), MarketS("market.png"), coinS("coin2.png"), background1("background.png"), birdS("birdAnim.png"), loseS("lose.png"), stolbS("Stone.jpg"), stolbS2("Stone.jpg");
	birdS.Spr.setTextureRect(IntRect(290, 100, 40, 40));
	birdS.Spr.setPosition(xBird, y);
	stolbS.Spr.setTextureRect(IntRect(150, 0, 40, height));
	stolbS2.Spr.setTextureRect(IntRect(150, 0, 40, 400 - height - 80));
	MenuS.Spr.setPosition(0, 0);
	RuleS.Spr.setPosition(0, 0);
	MarketS.Spr.setPosition(0, 0);
	coinS.Spr.setScale(Vector2f(0.2, 0.2));



	std::ifstream vivod("chet.txt");
	vivod >> score;
	vivod.close();
	std::ifstream SelBir("Current.txt");
	SelBir >> currentSel;
	SelBir.close();
	std::ifstream buyy("Buy.txt");
	buyy >> buyz;
	buyy.close();

	while (window.isOpen())
	{
		std::ostringstream Pscore;
		Pscore << score;
		text.setString("Монет : " + Pscore.str());
		text.setPosition(20, 360);
		text.setColor(Color::Green);

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1000;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (Men == 1) {
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					Vector2i Pos = Mouse::getPosition(window);
					if (Pos.x > 10 && Pos.y > 310 && Pos.x < 230 && Pos.y < 340)score += 500, zapis(score);
					if (Pos.x > 10 && Pos.y > 360 && Pos.x < 180 && Pos.y < 390)zapis(0);
				}
			}
		}
		window.clear();

		if (Men == 2)
		{
			if (TexSto == 160)TexSto = 0;
			if (x >= -40)x = x - (0.3 * time), stolbS.Spr.setPosition(x, 0), stolbS2.Spr.setPosition(x, height + 80);
			else x = 710, height = rand() % 320, stolbS.Spr.setTextureRect(IntRect(150 + TexSto, 0, 40, height)), stolbS2.Spr.setTextureRect(IntRect(150 + TexSto, 0, 40, 400 - height - 80));
			if (coins[0][0] >= -40)coins[0][0] = coins[0][0] - (0.3 * time), coinS.Spr.setPosition(coins[0][0], coins[1][0]);
			else coins[0][0] = 710, coins[1][0] = rand() % 370, timercoin = 0;
			TexSto = TexSto + 40;

			if (timercoin != 1)if (y >= coins[1][0] - 20 && xBird + 51 >= coins[0][0] && y <= coins[1][0] + 20 && xBird + 50 < coins[0][0] + 60)timercoin = 1, score++;

			if (Keyboard::isKeyPressed(Keyboard::Up))y = y - (time * 0.35), birdS.Spr.setPosition(xBird, y);
			if (Keyboard::isKeyPressed(Keyboard::Down))y = y + (time * 0.35), birdS.Spr.setPosition(xBird, y);

			if (y < height && xBird > x && xBird < x + 40)timerlose = 1;
			if (y + 40 > height + 80 && xBird + 35 > x && xBird < x + 40)timerlose = 1;
			if (y == 0)y = y + (time * 0.35);
			if (y == 361)y = y - (time * 0.35);

			if (Frame >= 9)Frame = 6;
			birdS.Spr.setTextureRect(IntRect(int(Frame) * 47.2, ptitsa, 42, 40));
			Frame += 0.01 * time;

			if (xPic > -700)xPic = xPic - (0.1 * time), background.Spr.setPosition(xPic, 0);
			else xPic = 698, background.Spr.setPosition(xPic, 0);
			if (xPic2 > -700)xPic2 = xPic2 - (0.1 * time), background1.Spr.setPosition(xPic2, 0);
			else xPic2 = 698, background1.Spr.setPosition(xPic2, 0);

			if (FrameCoin >= 8)FrameCoin = 0;
			coinS.Spr.setTextureRect(IntRect(int(FrameCoin) * 140, 0, 125, 125));
			FrameCoin += 0.02 * time;

			minus = minus + tt;

		}

		if (Men == 1) {
			if (Mouse::isButtonPressed(sf::Mouse::Left)) {
				Vector2i Pos = Mouse::getPosition(window);
				if (Pos.x > 260 && Pos.y > 170 && Pos.x < 420 && Pos.y < 210)Men = 2;
				if (Pos.x > 250 && Pos.y > 240 && Pos.x < 430 && Pos.y < 290) {
					Men = 3;
					rul = true;
				}
				if (Pos.x > 540 && Pos.y > 350 && Pos.x < 675 && Pos.y < 380)Men = 3, market = true;
				if (Pos.x > 270 && Pos.y > 310 && Pos.x < 410 && Pos.y < 340)window.close();
				switch (currentSel) {
				case 1:ptitsa = 100; break;
				case 2:ptitsa = 290; break;
				}
			}
		}
		if (rul == true)
		{
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i Pos = Mouse::getPosition(window);
				if (Pos.x > 220 && Pos.y > 330 && Pos.x < 460 && Pos.y < 360)Men = 1, rul = false;
			}
		}
		if (market == true)
		{
			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i Pos = Mouse::getPosition(window);
				if (Pos.x > 240 && Pos.y >350 && Pos.x < 460 && Pos.y < 370)Men = 1, market = false;
			}
			select.setString("выбрано");
			if (currentSel == 2)select.setPosition(400, 100);
			if (currentSel == 1)select.setPosition(130, 100);

			if (Mouse::isButtonPressed(Mouse::Left)) {
				Vector2i Pos = Mouse::getPosition(window);
				if (Pos.x > 440 && Pos.y > 170 && Pos.x < 480 && Pos.y < 230)
				{
					if (buyz != 1)if (score >= 500)currentSel = 2, currentBird(currentSel), buyz = 1, score -= 500, zapis(score), buy(buyz);
					if (buyz == 1)currentSel = 2, currentBird(currentSel);
				}
				if (Pos.x > 180 && Pos.y > 170 && Pos.x < 220 && Pos.y < 230)currentSel = 1, currentBird(currentSel);
			}
			text.setPosition(0, 0);
			text.setColor(Color::Red);

		}

		if (Men == 2)
		{
			if (timerlose == 0) {
				window.draw(background.Spr);
				window.draw(background1.Spr);
				window.draw(birdS.Spr);
				if (timercoin == 0)window.draw(coinS.Spr);
				window.draw(stolbS.Spr);
				window.draw(stolbS2.Spr);
				window.draw(text);
				window.display();
				sleep(t - minus);
			}
			if (timerlose != 0) {
				zapis(score);
				window.draw(loseS.Spr);
				window.display();
				sleep(lose);
				Men = 1;
				timerlose = 0;
				Incialize(xBird, height, xPic, xPic2, x, y);
				birdS.Spr.setPosition(xBird, y), stolbS.Spr.setPosition(x, height), stolbS2.Spr.setPosition(x, height + 80);
				stolbS.Spr.setTextureRect(IntRect(150, 0, 40, height));
				stolbS2.Spr.setTextureRect(IntRect(150, 0, 40, 400 - height - 80));
				coins[0][0] = 1200;
			}
		}
		if (Men == 1)
		{
			window.draw(MenuS.Spr);
			window.display();
		}
		if (rul == true)
		{
			window.draw(RuleS.Spr);
			window.display();

		}
		if (market == true)
		{
			window.draw(MarketS.Spr);
			window.draw(select);
			window.draw(text);
			if (buyz != 1)window.draw(buy1);
			window.display();
		}
	}
	return 0;
}