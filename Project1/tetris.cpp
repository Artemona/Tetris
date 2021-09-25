#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <windows.h>
		
using namespace std;
using namespace sf;

const int W = 10;	
const int H = 20;
int field[H][W] = { 0 };

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Cube
{
	int x, y;
} a[4], b[4];

bool checked()
{
	for (int i=0;i<4;i++)
	{
		if (a[i].x<0||a[i].x>=W||a[i].y>=H) return 0;
		else if (field[a[i].y][a[i].x]) return 0;
	}
	return 1;
}

bool gameOver()
{
	for (int i = 0; i < W; i++)
	{
		if (field[1][i] > 0) return 1;
	}
	return 0;
}

void menu(RenderWindow& window, Music& music, bool volGO, bool menuP, bool& mNG)
{
	Texture m1T, m2T, m3T, aboutT, mBackgroundT, minusT, plusT;
	m1T.loadFromFile("..\\..\\Project1\\Release\\111.png");
	m2T.loadFromFile("..\\..\\Project1\\Release\\222.png");
	m3T.loadFromFile("..\\..\\Project1\\Release\\333.png");
	aboutT.loadFromFile("..\\..\\Project1\\Release\\mem.png");
	mBackgroundT.loadFromFile("..\\..\\Project1\\Release\\menuBG.png");
	minusT.loadFromFile("..\\..\\Project1\\Release\\minus.png");
	plusT.loadFromFile("..\\..\\Project1\\Release\\plus.png");

	Sprite m1(m1T), m2(m2T), m3(m3T), about(aboutT), mBackground(mBackgroundT), minus(minusT), plus(plusT);

	bool isMenu = 1;
	int menuNum = 0;
	float volume;
	if (volGO == true) { volume = music.getVolume(); volume = (ceil(volume / 10)) * 10; } else volume = 100.0;

	mBackground.setPosition(Vector2f(0, 0));
	m1.setPosition(Vector2f(10, 30));
	m2.setPosition(Vector2f(10, 90));
	m3.setPosition(Vector2f(10, 150));
	plus.setPosition(Vector2f(260, 380));
	minus.setPosition(Vector2f(260, 440));

	// Text
	Font menuF;
	menuF.loadFromFile("..\\..\\Project1\\Release\\Samson.ttf");

	Text menuV("", menuF, 30);
	menuV.setCharacterSize(20);
	menuV.setPosition(Vector2f(275, 344));

	Texture rectT;
	rectT.loadFromFile("..\\..\\Project1\\Release\\paper.png");

	Sprite rect(rectT);
	rect.setTextureRect(IntRect(0, 0, 50, 35));
	rect.setColor(Color(4, 69, 22));
	rect.setPosition(Vector2f(260, 340));

	// Arrow
	Texture arrowT;
	arrowT.loadFromFile("..\\..\\Project1\\Release\\arrow.png");

	Sprite arrow(arrowT);
	arrow.setPosition(Vector2f(10, 210));

	while (isMenu)
	{
		m1.setColor(Color::White);
		m2.setColor(Color::White);
		m3.setColor(Color::White);
		minus.setColor(Color::Green);
		plus.setColor(Color::Green);
		arrow.setColor(Color::White);

		menuNum = 0;

		if (IntRect(10, 30, 300, 50).contains(Mouse::getPosition(window))) { m1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(10, 90, 300, 50).contains(Mouse::getPosition(window))) { m2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(10, 150, 300, 50).contains(Mouse::getPosition(window))) { m3.setColor(Color::Blue); menuNum = 3; }
		if (IntRect(260, 380, 50, 40).contains(Mouse::getPosition(window))) { plus.setColor(Color::Cyan); menuNum = 4; }
		if (IntRect(260, 440, 50, 15).contains(Mouse::getPosition(window))) { minus.setColor(Color::Cyan); menuNum = 5; }
		if (menuP == true) { if (IntRect(10, 210, 100, 50).contains(Mouse::getPosition(window))) { arrow.setColor(Color::Blue); menuNum = 6; } }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { if (menuP == true) mNG = true; isMenu = false; }
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)) {} }
			if (menuNum == 3) { window.close(); isMenu = false; }
			if (menuNum == 4) { if (music.getVolume() < 100) { volume = music.getVolume() + 10.f; volume = (ceil(volume / 10)) * 10; music.setVolume(volume); Sleep(500); } }
			if (menuNum == 5) { if (music.getVolume() > 0) { volume = music.getVolume() - 10.f; volume = (ceil(volume / 10)) * 10; music.setVolume(volume); Sleep(500); } }
			if (menuNum == 6) { isMenu = false; }
		}
		
		// Text
		menuV.setString(to_string(int(volume)));

		window.draw(mBackground);
		window.draw(m1);
		window.draw(m2);
		window.draw(m3);
		window.draw(minus);
		window.draw(plus);
		window.draw(rect);
		window.draw(menuV);
		if (menuP == true) window.draw(arrow);

		window.display();
	}
}

int main(void)
{
	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "Tetris");
	
	// Music
	Music music;
	music.openFromFile("..\\..\\Project1\\Release\\acdc.ogg");

	// Variable
	bool mNG = false;

	// Menu
	menu(window, music, false, false, mNG);

	// Music 2
	music.setLoop(true);
	music.play();

	// Textures
	Texture texture, tex_background, tex_frame, tex_rect;
	texture.loadFromFile("..\\..\\Project1\\Release\\tiles.png");
	tex_background.loadFromFile("..\\..\\Project1\\Release\\background.png");
	tex_frame.loadFromFile("..\\..\\Project1\\Release\\frame.png");
	tex_rect.loadFromFile("..\\..\\Project1\\Release\\paper.png");

	// Создание спрайта
	Sprite sprite(texture), sprite_background(tex_background), sprite_frame(tex_frame);
	
	sprite.setTextureRect(IntRect(0, 0, 18, 18));

	Sprite sprite_rect(tex_rect);
	sprite_rect.setTextureRect(IntRect(0, 0, 100, 40));
	sprite_rect.setPosition(Vector2f(210.f,410.f));

	// Text
	Font font;
	font.loadFromFile("..\\..\\Project1\\Release\\egypt_font.ttf");

	Text text1("GAMEOVER", font, 70);
	text1.setOutlineThickness(2);
	text1.setOutlineColor(Color::Black);
	text1.setPosition(Vector2f(20.f, 160.f));

	Text text2("score", font, 50);
	text2.setOutlineThickness(2);
	text2.setOutlineColor(Color::Black);
	text2.setPosition(Vector2f(20.f, 240.f));

	Text text3("", font, 60);
	text3.setOutlineThickness(3);
	text3.setOutlineColor(Color::Cyan);
	text3.setPosition(Vector2f(160.f, 230.f));

	Text text4("", font, 24);
	text4.setOutlineThickness(2);
	text4.setOutlineColor(Color::Black);
	text4.setPosition(Vector2f(235.f, 415.f));
	
	/*
	Vector2f centerPos = Vector2f(sprite_rect.getPosition().x + 50, sprite_rect.getPosition().y + 20);
	text4.setPosition(centerPos.x - text4.getGlobalBounds().width / 2, centerPos.y - text4.getGlobalBounds().height / 2);
	*/

	// Variables
	int dx = 0;
	bool rotate_s = 0;
	int points = 0;
	int colorNum = 1;
	bool beginGame = true;
	int n = rand() % 7;
	bool gameOverMenu = false;

	float timer = 0, delay = 0.3;

	// Часики
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		if (gameOverMenu == true) music.play();

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					music.pause();
					menu(window, music, true, true, mNG);
					if (mNG == true)
					{
						music.stop();

						// set vars in start-positions 
						dx = 0;
						rotate_s = 0;
						delay = 0.3;
						gameOverMenu = false;
						beginGame = true;
						//timer = 0;
						points = 0;
						for (int i = 0; i < 4; i++) { a[i].x = 0; a[i].y = 0; b[i].x = 0; b[i].y = 0; }
						for (int i = 0; i < H; i++)
						{
							for (int j = 0; j < W; j++)
							{
								field[i][j] = 0;
							}
						}

						music.play();
					} 
					else music.play(); 
					mNG = false; 
				}
				if (event.key.code == Keyboard::Up) rotate_s = 1;
				if (event.key.code == Keyboard::Left) dx += -1;
				else if (event.key.code == Keyboard::Right) dx += 1;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

		// move on X
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!checked())
		{
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
		}

		// Rotate
		if (rotate_s)
		{
			Cube cube = a[1];
			for (int i = 0; i < 4; i++)
			{
				b[i] = a[i];

				int x = a[i].y - cube.y;
				int y = a[i].x - cube.x;
				a[i].x = cube.x - x;
				a[i].y = cube.y + y;
			}
			if (!checked())
			{
				for (int i = 0; i < 4; i++)
					a[i] = b[i];
			}
		}

		// move on Y
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
			if (!checked())
			{
				for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
				
				colorNum = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			timer = 0;
		}

		//----ПРОВЕРКА ЛИНИИ----//
		int k = H - 1;
		for (int i = H - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < W; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < W) k--; // if all is good go together
			else points += 100;
		}

		// Первое появление тетрамино на поле?
		if (beginGame)
		{
			beginGame = false;
			n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}

		// Returning variables in start-state
		dx = 0;
		rotate_s = 0;
		delay = 0.3;
		gameOverMenu = false;

		// drawing
		window.clear(Color::White);
		window.draw(sprite_background);
		window.draw(sprite_frame);
		window.draw(sprite_rect);
		text4.setString(to_string(points));
		window.draw(text4);

		// для уже пристыковавшихся
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18, i * 18);
				sprite.move(28, 31); // смещение
				window.draw(sprite);

			}
		}

		// gameover part
		if (gameOver())
		{
			// drawing score
			window.draw(text1);
			window.draw(text2);
			text3.setString(to_string(points));
			window.draw(text3);

			window.display();

			Sleep(6000);

			// turn off music
			music.stop();
			
			// set vars in start-positions 
			beginGame = true; 
			timer = 0;
			points = 0;
			for (int i = 0; i < 4; i++) { a[i].x = 0; a[i].y = 0; b[i].x = 0; b[i].y = 0; }
			for (int i = 0; i < H; i++)
			{
				for (int j = 0; j < W; j++)
				{
					field[i][j] = 0;
				}
			}

			menu(window, music, true, false, mNG);

			gameOverMenu = true;
		}
		
		// moving parts + window.display()
		if (gameOverMenu == false)
		{
			// для приколов в движении
			for (int i = 0; i < 4; i++)
			{
				sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
				sprite.setPosition(a[i].x * 18, a[i].y * 18);
				sprite.move(28, 31); // смещение
				window.draw(sprite);
			}

			window.display();
		}

	}

	return 0;
}