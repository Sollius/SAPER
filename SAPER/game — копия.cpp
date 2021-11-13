#include <SFML/Graphics.hpp>
#include <time.h>
#include <array>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace sf;
/*
class Unit
{
private:
	int m_x;
	int m_y;
	int m_value;
	bool m_openly;
	bool m_cursored;

public:
	Unit() : m_x(0), m_y(0), m_value(0), m_openly(0), m_cursored(0) {}

	Unit(int x, int y) : m_x(x), m_y(y) {}

	void setValue(int x, int y, int value)	{m_value = value;}

	void opening(int x, int y) { m_openly = 1; }
};

class Field
{
private:
	std::vector <Unit*> m_unit;

public:
	void setValue(Unit* unit, int value)
	{
		m_value = value;
	}
};
*/


//bool cell(int)



//2021.08.13;16:34 - возможно нужно заменить все дес€тки на дев€тки

/*
int grn(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// –авномерно распредел€ем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
*/

int game(RenderWindow& window)
{
	srand(time(0));

	ContextSettings settings;
	settings.antialiasingLevel = 64;

	//определение текстур
	Texture game_bg_txt, units_txt, frame_txt, losing_txt;
	//загрузка текстур
	game_bg_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\game_bg_1.png");
	units_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	frame_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\game_frame1.png");
	losing_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\losing.png");
	//определение спрайтов
	Sprite game_bg_sprite(game_bg_txt), frame_sprite(frame_txt),
		zero_sprite(units_txt), i_sprite(units_txt), ii_sprite(units_txt), iii_sprite(units_txt), iv_sprite(units_txt), v_sprite(units_txt),
		vi_sprite(units_txt), vii_sprite(units_txt), iix_sprite(units_txt), b_sprite(units_txt), f_sprite(units_txt), empty_sprite(units_txt),
		cursor_sprite(units_txt), sprite_losing_bg(losing_txt), sprite_losing_yes(losing_txt), sprite_losing_no(losing_txt);
	//определение участков текстур дл€ спрайтов €чеек
	zero_sprite.setTextureRect(IntRect(0, 0, 64, 64));
	i_sprite.setTextureRect(IntRect(64, 0, 64, 64));
	ii_sprite.setTextureRect(IntRect(128, 0, 64, 64));
	iii_sprite.setTextureRect(IntRect(192, 0, 64, 64));
	iv_sprite.setTextureRect(IntRect(256, 0, 64, 64));
	v_sprite.setTextureRect(IntRect(320, 0, 64, 64));
	vi_sprite.setTextureRect(IntRect(384, 0, 64, 64));
	vii_sprite.setTextureRect(IntRect(448, 0, 64, 64));
	iix_sprite.setTextureRect(IntRect(512, 0, 64, 64));
	b_sprite.setTextureRect(IntRect(576, 0, 64, 64));
	f_sprite.setTextureRect(IntRect(640, 0, 64, 64));
	empty_sprite.setTextureRect(IntRect(704, 0, 64, 64));
	cursor_sprite.setTextureRect(IntRect(768, 0, 64, 64));
	//...дл€ спрайтов окна проигрыша
	sprite_losing_bg.setTextureRect(IntRect(0, 0, 600, 330));
	sprite_losing_yes.setTextureRect(IntRect(600, 0, 200, 100));
	sprite_losing_no.setTextureRect(IntRect(600, 100, 200, 100));
	//цвет пустого спрайта, типа прозрачный
	empty_sprite.setColor(Color(255, 255, 255, 150));
	//движение фона
	game_bg_sprite.setOrigin(1000, 1000);
	game_bg_sprite.move(800, 450);
	game_bg_sprite.setRotation((rand() % 360));

	// ѕеременные дл€ таймера и задержки
	//float timer = 0, delay = 1;
	// „асы (таймер)
	//Clock clock;

	int difficult = 10;
	//if (difficult == 0)
	const int X = 10;
	const int Y = 10;
	int playField[X][Y] = { 0 };			//массив значений €чеек пол€
	int playFieldCount[X][Y] = { 0 };	//массив-счЄтчик бомб
	bool playFieldOpenFlag[X][Y] = { 0 };	//массив открытости	€чеек пол€

	int cursX = 0, cursY = 0;
	int cursor[2] = { cursX, cursY };		//курсор

	bool startGame = 1, losing = 0, losing_accept = 0, newGame = 1;			//булевые переменные

	int bgCountX = 0, bgCountY = 0;

	

	//frame_sprite.move(320, 20);

	while (window.isOpen())
	{

		//float time = clock.getElapsedTime().asSeconds();
		//clock.restart();
		//timer += time;

		
		Event event1;
		while (window.pollEvent(event1))
		{
			if (event1.type == Event::KeyPressed)
			{
				if (event1.key.code == Keyboard::Escape)
				{
					return 1;
				}
				
				if (losing == 1)
				{
					if (event1.key.code == Keyboard::A)
					{

						if (losing_accept == 1)
							losing_accept = 0;
						else
							losing_accept = 1;
					}

					if (event1.key.code == Keyboard::D)
					{

						if (losing_accept == 0)
							losing_accept = 1;
						else
							losing_accept = 0;
					}

					if (event1.key.code == Keyboard::Enter)
					{
						if (losing_accept == 1)
						{
							
							startGame = 1;
							losing = 0;
						}

						if (losing_accept == 0)
							return 1;
							losing = 0;
							
					}
				}
				
				if (losing == 0)
				{
					if (event1.key.code == Keyboard::W)
					{
						cursY--;
						if (cursY < 1)
							cursY = 10;
					}

					if (event1.key.code == Keyboard::A)
					{
						cursX--;
						if (cursX < 1
							)
							cursX = 10;
					}
					if (event1.key.code == Keyboard::S)
					{
						cursY++;
						if (cursY > 10)
							cursY = 1;
					}

					if (event1.key.code == Keyboard::D)
					{
						cursX++;
						if (cursX > 10)
							cursX = 1;
					}

					if (event1.key.code == Keyboard::Enter)
					{
						playFieldOpenFlag[cursX][cursY] = 1;

						if (playFieldCount[cursX][cursY] == 0)
						{


							/*
							if (playFieldCount[cursX+n][cursY+m] == 0)
							{
								n++;
								m++;
							}
							*/
						}

						if (playFieldCount[cursX][cursY] >= 10)
						{
							losing = 1;
						}
					}
				}

				
			}
		}

		for(int countY = 1; countY <= 10; countY++)
			for (int countX = 1; countX <= 10; countX++)
			{
				if ((playFieldOpenFlag[countX][countY] == 1) && (playFieldCount[countX][countY] == 0))
				{
					if (playFieldOpenFlag[countX][countY - 1] == 0 && playFieldCount[countX][countY - 1] < 10)
					{
						playFieldOpenFlag[countX][countY - 1] = 1;
					}

					if (playFieldOpenFlag[countX - 1][countY] == 0 && playFieldCount[countX - 1][countY] < 10)
					{
						playFieldOpenFlag[countX - 1][countY] = 1;
					}

					if (playFieldOpenFlag[countX + 1][countY] == 0 && playFieldCount[countX + 1][countY] < 10)
					{
						playFieldOpenFlag[countX + 1][countY] = 1;
					}

					if (playFieldOpenFlag[countX][countY + 1] == 0 && playFieldCount[countX][countY + 1] < 10)
					{
						playFieldOpenFlag[countX][countY + 1] = 1;
					}

					if (playFieldOpenFlag[countX - 1][countY - 1] == 0 && playFieldCount[countX - 1][countY - 1] < 10)
					{
						playFieldOpenFlag[countX - 1][countY - 1] = 1;
					}

					if (playFieldOpenFlag[countX - 1][countY+1] == 0 && playFieldCount[countX - 1][countY+1] < 10)
					{
						playFieldOpenFlag[countX - 1][countY+1] = 1;
					}

					if (playFieldOpenFlag[countX + 1][countY-1] == 0 && playFieldCount[countX + 1][countY-1] < 10)
					{
						playFieldOpenFlag[countX + 1][countY-1] = 1;
					}

					if (playFieldOpenFlag[countX+1][countY + 1] == 0 && playFieldCount[countX+1][countY + 1] < 10)
					{
						playFieldOpenFlag[countX+1][countY + 1] = 1;
					}
				}
			}

		//if (losing == 0)
		
			//заполнение €чеек пол€
			if (startGame == 1)
			{
				//playField[X][Y] = { 0 };			//массив значений €чеек пол€
				//playFieldCount[X][Y] = { 0 };	//массив-счЄтчик бомб
				//playFieldOpenFlag[X][Y] = { 0 };	//массив открытости	€чеек пол€

				//первый цикл дл€ столбцов
				for (int countY = 1; countY <= 10; countY++)
				{
					//второй дл€ строк
					for (int countX = 1; countX <= 10; countX++)
					{
						playField[countX][countY] = (rand()%100);				//закладывание бомб
						playFieldOpenFlag[countX][countY] = 0;					//закрытие всех €чеек от посторонних глаз

						//распределение цифр вокруг бомб
						if (playField[countX][countY] > (100 - difficult))
						{
							playFieldCount[countX][countY] = 10;
							if (countX > 1 && countY > 1)
								playFieldCount[countX - 1][countY - 1]++;
							if(countY > 1)
								playFieldCount[countX][countY - 1]++;
							if(countX < 10 && countY > 1)
								playFieldCount[countX + 1][countY - 1]++;
							if(countX > 1)
								playFieldCount[countX - 1][countY]++;
							if(countX < 10)
								playFieldCount[countX + 1][countY]++;
							if(countX > 1 && countY < 10)
								playFieldCount[countX - 1][countY + 1]++;
							if(countY < 10)
								playFieldCount[countX][countY + 1]++;
							if(countX <10 && countY <10)
								playFieldCount[countX + 1][countY + 1]++;
						}
					}
				}

				for (int countY = 1; countY <= 10; countY++)
				{
					for (int countX = 1; countX <= 10; countX++)
					{
						std::cout << playField[countX][countY] << ' ' << playFieldCount[countX][countY] << '\t';
					}

					std::cout << std::endl;
				}

				startGame = 0;
			}

			window.clear(Color::Green);

			game_bg_sprite.rotate(0.003);
			window.draw(game_bg_sprite);

			//отрисовка пол€
			for (int countY = 1; countY <= Y; countY++)
			{
				for (int countX = 1; countX <= X; countX++)
				{
					if (playFieldOpenFlag[countX][countY] == 0)
					{
						empty_sprite.setPosition(320 + ((countX-1) * 64), 20 + ((countY-1) * 64));
						window.draw(empty_sprite);
					}
					else
					{
						switch (playFieldCount[countX][countY])
						{
						case 0:
							zero_sprite.setPosition(320 + ((countX-1) * 64), 20 + ((countY-1) * 64));
							window.draw(zero_sprite);
							break;
						case 1:
							i_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(i_sprite);
							break;
						case 2:
							ii_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(ii_sprite);
							break;
						case 3:
							iii_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(iii_sprite);
							break;
						case 4:
							iv_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(iv_sprite);
							break;
						case 5:
							v_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(v_sprite);
							break;
						case 6:
							vi_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(vi_sprite);
							break;
						case 7:
							vii_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(vii_sprite);
							break;
						case 8:
							iix_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(iix_sprite);
							break;
						default:
							b_sprite.setPosition(320 + ((countX - 1) * 64), 20 + ((countY - 1) * 64));
							window.draw(b_sprite);
							break;
						}
					}
				}
			}
			if (cursX != 0 && cursY != 0)
			{
				cursor_sprite.setPosition(320 + ((cursX-1) * 64), 20 + ((cursY-1) * 64));
				window.draw(cursor_sprite);
			}
			
		

		if (losing == 1)
		{
			if (losing_accept == 0)
			{
				sprite_losing_no.setColor(Color(150, 0, 0, 255));
				sprite_losing_yes.setColor(Color(255,255,255,180));
			}
			else
			{
				sprite_losing_yes.setColor(Color(150, 0, 0, 255));
				sprite_losing_no.setColor(Color(255, 255, 255, 180));
			}

			sprite_losing_bg.setPosition(340, 195);
			window.draw(sprite_losing_bg);

			sprite_losing_yes.setPosition(415, 395);
			window.draw(sprite_losing_yes);
			sprite_losing_no.setPosition(665, 395);
			window.draw(sprite_losing_no);
		}
			

		window.display();

	}

	return 0;
}