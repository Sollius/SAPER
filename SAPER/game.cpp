#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <array>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <random>

std::random_device rd;
std::mt19937 mersenne(rd());

using namespace sf;

int game(RenderWindow& window, int& diff, int& size);

class Numbers
{
public:
	int m_value;
	int m_bombCount = 0;
	bool m_openly = 0;
	bool m_flaged = 0;

	friend std::ostream& operator<< (std::ostream& out, const Numbers& number);
};

std::ostream& operator<< (std::ostream& out, const Numbers& number)
{
	out << number.m_value;

	return out;
}

class Array
{
public:
	std::array <std::array <Numbers, 10>, 10> m_massiv{ 0 };
	int m_numberOfFlags = 0;
	int m_numberOfBombs = 0;

	Array()
	{
	};

	Array(int size, int diff)
	{
		//m_size = 10;
		//m_diff = 10;
	};

	bool inRange(int x, int y)
	{
		if ((x >= 0 && x <= 9) && (y >= 0 && y <= 9))
			return 1;
		else
			return 0;
	}

	int getValue(int x, int y)
	{
		if (inRange(x, y))
			return m_massiv[x][y].m_value;
	};

	bool getFlaged(int x, int y)
	{
		if (inRange(x, y))
			return m_massiv[x][y].m_flaged;
	}

	bool getOpenly(int x, int y)
	{
		if (inRange(x, y))
			return m_massiv[x][y].m_openly;
	};

	int getBombCount(int x, int y)
	{
		if (inRange(x, y))
			return m_massiv[x][y].m_bombCount;
	};

	void setValue(int x, int y, int value)
	{
		if (inRange(x, y))
			m_massiv[x][y].m_value = value;
	};

	void setOpenly(int x, int y)
	{
		if (inRange(x, y))
			m_massiv[x][y].m_openly = 1;
	};

	void setClosely(int x, int y)
	{
		if (inRange(x, y))
			m_massiv[x][y].m_openly = 0;
	};

	void setFlaged(int x, int y)
	{
		if (inRange(x, y) && (getOpenly(x, y) == 0))
		{
			//std::cout << "In Range" << std::endl;
			m_massiv[x][y].m_flaged = 1;
		}
		//std::cout << "Flaged Complete" << std::endl;
	}

	void setUnflaged(int x, int y)
	{
		if (inRange(x, y) && (getFlaged(x, y) == 1))
			m_massiv[x][y].m_flaged = 0;
	}

	void setBombCount(int x, int y, int value)
	{
		if (inRange(x, y))
			m_massiv[x][y].m_bombCount = value;
	}

	int randomNumber()
	{
		return mersenne() % 100;
	};

	void openAround(int x, int y)
	{
		setOpenly(x - 1, y - 1);
		setOpenly(x - 1, y);
		setOpenly(x - 1, y + 1);
		setOpenly(x, y - 1);
		setOpenly(x, y + 1);
		setOpenly(x + 1, y - 1);
		setOpenly(x + 1, y);
		setOpenly(x + 1, y + 1);
	}

	int fillField(int diff)
	{
		for (int countY = 0; countY <= (10 - 1); countY++)
			for (int countX = 0; countX <= (10 - 1); countX++)
			{
				setValue(countX, countY, randomNumber());
				setUnflaged(countX, countY);
				
				if (m_massiv[countX][countY].m_value < diff)
				{
					m_numberOfBombs++;

					//распределение цифр вокруг бомб
					m_massiv[countX][countY].m_bombCount = 10;
					
					if (countX > 0 && countY > 0 && m_massiv[countX - 1][countY - 1].m_bombCount != 10)
						m_massiv[countX - 1][countY - 1].m_bombCount++;
					if (countY > 0 && m_massiv[countX][countY - 1].m_bombCount != 10)
						m_massiv[countX][countY - 1].m_bombCount++;
					if (countX < (10 - 1) && countY > 0 && m_massiv[countX + 1][countY - 1].m_bombCount != 10)
						m_massiv[countX + 1][countY - 1].m_bombCount++;
					if (countX > 0 && m_massiv[countX - 1][countY].m_bombCount != 10)
						m_massiv[countX - 1][countY].m_bombCount++;
					if (countX < (10 - 1) && m_massiv[countX + 1][countY].m_bombCount != 10)
						m_massiv[countX + 1][countY].m_bombCount++;
					if (countX > 0 && countY < (10 - 1) && m_massiv[countX - 1][countY + 1].m_bombCount != 10)
						m_massiv[countX - 1][countY + 1].m_bombCount++;
					if (countY < (10 - 1) && m_massiv[countX][countY + 1].m_bombCount != 10)
						m_massiv[countX][countY + 1].m_bombCount++;
					if (countX < (10 - 1) && countY < (10 - 1) && m_massiv[countX + 1][countY + 1].m_bombCount != 10)
						m_massiv[countX + 1][countY + 1].m_bombCount++;
				}
			}
		std::cout << "There r " << m_numberOfBombs << "bombs" << std::endl;
		return m_numberOfBombs;
	}

	void printField(int debug)
	{
		if (debug == 1)
		{
			for (int countY = 0; countY < 10; countY++)
			{
				for (int countX = 0; countX < 10; countX++)
				{
					std::cout << m_massiv[countX][countY] << '\t';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	void printBombCounts(int debug)
	{
		if (debug == 1)
		{
			for (int countY = 0; countY < 10; countY++)
			{
				for (int countX = 0; countX < 10; countX++)
				{
					std::cout << m_massiv[countX][countY].m_bombCount << '\t';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	void printValue(int x, int y, int debug)
	{
		if(debug == 1)
			std::cout << m_massiv[x][y].m_value << std::endl;
	}

	void printFlaged(int debug)
	{
		if (debug == 1)
		{
			for (int countY = 0; countY < 10; countY++)
			{
				for (int countX = 0; countX < 10; countX++)
				{
					std::cout << m_massiv[countX][countY].m_flaged << '\t';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}

	void printNumberOfFlags(int debug)
	{
		int numberOfFlags = 0;
		for (int countY = 0; countY < 10; countY++)
		{
			for (int countX = 0; countX < 10; countX++)
			{
				if (m_massiv[countX][countY].m_flaged == 1)
					numberOfFlags++;
			}
		}
		m_numberOfFlags = numberOfFlags;
		std::cout << "There r " << m_numberOfFlags << " flags" << std::endl;
	}

	void printBombCount(int x, int y, int debug)
	{
		if (debug == 1)
			std::cout << m_massiv[x][y].m_bombCount << std::endl;
	}

	bool checkFlaged(int x, int y)
	{
		if (inRange(x, y))
		{
			if (m_massiv[x][y].m_flaged == 1 && m_massiv[x][y].m_bombCount >= 10)
				return 1;
			else
				return 0;
		}
	}

	bool pseudoFlaged(int x, int y)
	{
		if (inRange(x, y))
		{
			if (m_massiv[x][y].m_flaged == 1 && m_massiv[x][y].m_bombCount < 10)
				return 1;
			else
				return 0;
		}
	}

	void openAll(int debug)
	{
		if (debug == 1)
		{
			std::cout << "openAll - works!" << std::endl;
		}

		for(int countY = 0; countY < 10; countY++)
			for (int countX = 0; countX < 10; countX++)
			{
				m_massiv[countX][countY].m_flaged == 0;
				m_massiv[countX][countY].m_openly == 1;
			}
	}

	bool checkResult(int debug)
	{
		if (debug == 1)
		{
			std::cout << "Bombs = " << m_numberOfBombs << ", Flags = " << m_numberOfFlags << std::endl;
		}

		if (m_numberOfBombs == m_numberOfFlags)
		{
			if (debug == 1)
			{
				std::cout << "checkResult returns 1";
			}
			return 1;
		}
		else
		{
			openAll(debug);
			if (debug == 1)
			{
				std::cout << "checkResult returns 0";
			}
			return 0;
		}
	}

	bool checkEmpties(int debug)
	{
		printNumberOfFlags(debug);
		for(int countY = 0; countY < 10; countY++)
			for (int countX = 0; countX < 10; countX++)
			{
				if (getOpenly(countX, countY) == 0)
				{
					if (getFlaged(countX, countY) == 0)
					{
						if (debug == 1)
						{
							std::cout << "checkEmpties - works! Return 0." << std::endl;
						}
						return 0;
					}
				}
			}

		if (debug == 1)
		{
			std::cout << "checkEmpties - works! Return 1!!!" << std::endl;
		}
		return 1;
	}
};



int game(RenderWindow& window, int& diff, int& size, int debug)
{
	ContextSettings settings;
	settings.antialiasingLevel = 64;

	//целые переменные
	int music_mode = 1, music_int = 0;

	Array playField;
	music_int = playField.fillField(diff);
	playField.printField(debug);
	playField.printBombCounts(debug);

	std::cout << playField.m_numberOfBombs << std::endl;

	//курсор
	int cursX = 0, cursY = 0;
	int cursor[2] = { cursX, cursY };

	//отрисовка пол€
	int width = 320, height = 40, cageSize = 64;

	//булевые переменные
	bool startGame = 1, losing = 0, winning = 0, losing_accept = 1, winning_accept = 1,
		newGame = 1, playing = 1, exit = 0, exit_accept = 1, checking_true = 0;

	


	//////////////////////////////
	//////текстуры и спрайты//////
	//////////////////////////////

	//определение текстур
	Texture game_bg_txt, units_txt, frame_txt, losing_txt, winning_txt, exit_txt, info_txt;

	//загрузка текстур
	{
		game_bg_txt.loadFromFile("img\\game_bg_1.png");
		units_txt.loadFromFile("img\\units.png");
		frame_txt.loadFromFile("img\\game_frame1.png");
		losing_txt.loadFromFile("img\\losing.png");
		winning_txt.loadFromFile("img\\winning.png");
		exit_txt.loadFromFile("img\\game_exit.png");
		info_txt.loadFromFile("img\\game_info.png");
	}

	//определение спрайтов
	Sprite game_bg_sprite(game_bg_txt), frame_sprite(frame_txt), zero_sprite(units_txt),
		i_sprite(units_txt), ii_sprite(units_txt), iii_sprite(units_txt), iv_sprite(units_txt),
		v_sprite(units_txt), vi_sprite(units_txt), vii_sprite(units_txt), iix_sprite(units_txt),
		b_sprite(units_txt), f_sprite(units_txt), empty_sprite(units_txt), cursor_sprite(units_txt),
		sprite_losing_bg(losing_txt), sprite_yes(losing_txt), sprite_no(losing_txt), sprite_winning_bg(winning_txt),
		sprite_exit_bg(exit_txt), sprite_info(info_txt);

	//определение участков текстур дл€ спрайтов €чеек
	{
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
		cursor_sprite.setTextureRect(IntRect(768, 0, 64, 64));
		empty_sprite.setTextureRect(IntRect(704, 0, 64, 64));
	}
//цвет пустого спрайта, типа прозрачный
	empty_sprite.setColor(Color(255, 255, 255, 150));
	

	//...дл€ спрайтов окна проигрыша, выигрыша и выхода
	{
		sprite_losing_bg.setTextureRect(IntRect(0, 0, 600, 330));
		sprite_winning_bg.setTextureRect(IntRect(0, 0, 600, 330));
		sprite_exit_bg.setTextureRect(IntRect(0, 0, 600, 330));
		sprite_yes.setTextureRect(IntRect(600, 0, 200, 100));
		sprite_no.setTextureRect(IntRect(600, 100, 200, 100));
	}

	//движение фона
	{
		game_bg_sprite.setOrigin(1000, 1000);
		game_bg_sprite.move(800, 450);
		game_bg_sprite.setRotation((rand() % 360));
	}

	/*
	//рамка v1
	CircleShape frame(449, 4);
	{
		frame.setPosition(5, 360);
		frame.setFillColor(Color(0, 0, 0, 60));
		frame.setOutlineColor(Color(0, 60, 0, 255));
		frame.setOutlineThickness(4.0);
		frame.setRotation(-45.0);
	}
	*/

	sprite_info.setPosition(970, 60);

	//рамка v2
	RectangleShape frame(Vector2f(639, 639));
	{
		frame.setFillColor(Color(0, 0, 0, 255));
		frame.setOutlineThickness(3);
		frame.setOutlineColor(Color(0, 50, 0, 255));
		frame.setPosition(320, 40);
	}

	//общее затемнение
	RectangleShape darkPlate(Vector2f(1280, 720));
	{
		darkPlate.setOrigin(640, 360);
		darkPlate.setFillColor(Color(0, 0, 0, 125));
		darkPlate.setPosition(640, 360);
	}


	///////////////////
	//////музычка//////
	///////////////////

	//конструкторы
	Music game_music_1, game_music_2, game_music_3, game_music_4, game_music_5, game_music_6,
		game_music_7, game_music_8, music_losing, music_winning;

	//открытие файлов
	{
		game_music_1.openFromFile("sounds\\game_bg_1.ogg");
		game_music_2.openFromFile("sounds\\game_bg_2.ogg");
		game_music_3.openFromFile("sounds\\game_bg_3.ogg");
		game_music_4.openFromFile("sounds\\game_bg_4.ogg");
		game_music_5.openFromFile("sounds\\game_bg_5.ogg");
		game_music_6.openFromFile("sounds\\game_bg_6.ogg");
		game_music_7.openFromFile("sounds\\game_bg_7.ogg");
		game_music_8.openFromFile("sounds\\game_bg_8.ogg");
		music_losing.openFromFile("sounds\\losing_all.ogg");
		music_winning.openFromFile("sounds\\winning_music.ogg");
	}

	//ограничение петли
	{
		//1 - 4.8
		//2 - 4.36
		//3 - 4
		//4 - 3.69
		//5 - 3.42
		//6 - 3.2
		//7 - 3
		//8 - 2.82 - 5.64
		game_music_1.setLoopPoints(Music::TimeSpan(seconds(0), seconds(4.8)));
		game_music_2.setLoopPoints(Music::TimeSpan(seconds(0), seconds(4.36)));
		game_music_3.setLoopPoints(Music::TimeSpan(seconds(0), seconds(4)));
		game_music_4.setLoopPoints(Music::TimeSpan(seconds(0), seconds(3.69)));
		game_music_5.setLoopPoints(Music::TimeSpan(seconds(0), seconds(3.42)));
		game_music_6.setLoopPoints(Music::TimeSpan(seconds(0), seconds(3.2)));
		game_music_7.setLoopPoints(Music::TimeSpan(seconds(0), seconds(3)));
		game_music_8.setLoopPoints(Music::TimeSpan(seconds(0), seconds(5.64)));
		music_losing.setLoopPoints(Music::TimeSpan(seconds(37), seconds(177)));
		music_winning.setLoopPoints(Music::TimeSpan(seconds(26), seconds(57)));
	}

	//включение петли
	{
		game_music_1.setLoop(1);
		game_music_2.setLoop(1);
		game_music_3.setLoop(1);
		game_music_4.setLoop(1);
		game_music_5.setLoop(1);
		game_music_6.setLoop(1);
		game_music_7.setLoop(1);
		game_music_8.setLoop(1);
		music_losing.setLoop(1);
		music_winning.setLoop(1);
	}

	//включение музыки
	switch (music_mode)
	{
	case 1:
		game_music_1.play();
		break;
	case 2:
		game_music_2.play();
		break;
	case 3:
		game_music_3.play();
		break;
	case 4:
		game_music_4.play();
		break;
	case 5:
		game_music_5.play();
		break;
	case 6:
		game_music_6.play();
		break;
	case 7:
		game_music_7.play();
		break;
	case 8:
		game_music_8.play();
		break;
	}


	//звуки
	SoundBuffer b_pick, b_exI, b_exO, b_exS;

	//загрузка из файла
	{
		b_pick.loadFromFile("sounds\\pick.ogg");
		b_exI.loadFromFile("sounds\\game_exit_in.ogg");
		b_exO.loadFromFile("sounds\\game_exit_out.ogg");
		b_exS.loadFromFile("sounds\\game_exit_silence.ogg");
	}

	//конструкторы
	Sound pick, exitIn, exitOut, exitSilence;

	//определение буфера
	{
		pick.setBuffer(b_pick);
		exitIn.setBuffer(b_exI);
		exitOut.setBuffer(b_exO);
		exitSilence.setBuffer(b_exS);
		exitSilence.setLoop(1);
	}

	//отображение времени
	Clock clock;
	Font font;
	Text time;
	{
	font.loadFromFile("fonts\\Calibri.ttf");

	time.setOutlineColor(Color::Black);
	time.setOutlineThickness(3.0);
	time.setFillColor(Color(0, 180, 0, 255));
	time.setFont(font);
	time.setCharacterSize(48);
	time.setPosition(60, 30);
	}
	int seconds = 0, minutes = 0;

	Clock music_time;
	music_time.restart();
	int music_timer = 0;


	while (window.isOpen())
	{
		music_timer = 9.6;
		music_timer = music_time.getElapsedTime().asSeconds();

		//цикл событий
		Event event1;
		while (window.pollEvent(event1))
		{
			if (event1.type == Event::Closed)
				exit = 1;

			if (event1.type == Event::KeyPressed)
			{
				if (event1.key.code == Keyboard::Escape)
				{
					if (exit == 0)
					{
						exit = 1;
						exitIn.play();
						exitSilence.play();
						switch (music_mode)
						{
						case 1:
							game_music_1.pause();
						case 2:
							game_music_2.pause();
						case 3:
							game_music_3.pause();
						case 4:
							game_music_4.pause();
						case 5:
							game_music_5.pause();
						case 6:
							game_music_6.pause();
						case 7:
							game_music_7.pause();
						case 8:
							game_music_8.pause();
						}
					}
					else
					{
						exit = 0;
						exitOut.play();
						exitSilence.pause();
						switch (music_mode)
						{
						case 1:
							game_music_1.play();
							break;
						case 2:
							game_music_2.play();
							break;
						case 3:
							game_music_3.play();
							break;
						case 4:
							game_music_4.play();
							break;
						case 5:
							game_music_5.play();
							break;
						case 6:
							game_music_6.play();
							break;
						case 7:
							game_music_7.play();
							break;
						case 8:
							game_music_8.play();
							break;
						}
					}
				}

				if (event1.key.code == Keyboard::T)
					playField.openAll(debug);
				
				if (losing == 1)
				{
					if (event1.key.code == Keyboard::A)
					{

						if (losing_accept == 1)
						{
							losing_accept = 0;
							pick.play();
						}
						else
						{
							losing_accept = 1;
							pick.play();
						}
					}

					if (event1.key.code == Keyboard::D)
					{

						if (losing_accept == 0)
						{
							losing_accept = 1;
							pick.play();
						}
						else
						{
							losing_accept = 0;
							pick.play();
						}
					}

					if (event1.key.code == Keyboard::Enter)
					{
						if (losing_accept == 1)
						{
							music_losing.stop();
							return 2;
						}
						if (losing_accept == 0)
						{
							music_losing.stop();
							return 1;
						}
					}
				}

				if (winning == 1)
				{
					if (event1.key.code == Keyboard::A)
					{
						pick.play();
						if (winning_accept == 1)
							winning_accept = 0;
						else
							winning_accept = 1;
					}

					if (event1.key.code == Keyboard::D)
					{
						pick.play();
						if (winning_accept == 0)
							winning_accept = 1;
						else
							winning_accept = 0;
					}

					if (event1.key.code == Keyboard::Enter)
					{
						if (winning_accept == 1)
							return 2;
						if (winning_accept == 0)
							return 1;
					}
				}
				
				if (losing == 0 && winning == 0 && exit == 0)
				{
					if (event1.key.code == Keyboard::W)
					{
						cursY--;
						if (cursY < 0)
							cursY = 9;
					}
					if (event1.key.code == Keyboard::A)
					{
						cursX--;
						if (cursX < 0)
							cursX = 9;
					}
					if (event1.key.code == Keyboard::S)
					{
						cursY++;
						if (cursY > 9)
							cursY = 0;
					}
					if (event1.key.code == Keyboard::D)
					{
						cursX++;
						if (cursX > 9)
							cursX = 0;
					}

					if (event1.key.code == Keyboard::Enter)
					{
						if(debug == 1)
							std::cout << "losing=" << losing << std::endl;

						playField.setOpenly(cursX, cursY);

						if (playField.getBombCount(cursX, cursY) >= 10)
						{
							//playField.printValue(cursX, cursY, debug);
							//playField.printBombCount(cursX, cursY, debug);
							switch (music_mode)
							{
							case 1:
								game_music_1.pause();
							case 2:
								game_music_2.pause();
							case 3:
								game_music_3.pause();
							case 4:
								game_music_4.pause();
							case 5:
								game_music_5.pause();
							case 6:
								game_music_6.pause();
							case 7:
								game_music_7.pause();
							case 8:
								game_music_8.pause();
							}
							music_losing.play();
							losing = 1;
						}
						else
						{
							//playField.printValue(cursX, cursY, debug);
							//playField.printBombCount(cursX, cursY, debug);

							if (playField.checkEmpties(debug) == 1)
							{
								if (playField.checkResult(debug) == 1)
								{
									std::cout << "Winning!" << std::endl;
									switch (music_mode)
									{
									case 1:
										game_music_1.pause();
									case 2:
										game_music_2.pause();
									case 3:
										game_music_3.pause();
									case 4:
										game_music_4.pause();
									case 5:
										game_music_5.pause();
									case 6:
										game_music_6.pause();
									case 7:
										game_music_7.pause();
									case 8:
										game_music_8.pause();
									}

									music_winning.play();
									winning = 1;
								}
								else
								{
									std::cout << "Losing!" << std::endl;
									switch (music_mode)
									{
									case 1:
										game_music_1.pause();
									case 2:
										game_music_2.pause();
									case 3:
										game_music_3.pause();
									case 4:
										game_music_4.pause();
									case 5:
										game_music_5.pause();
									case 6:
										game_music_6.pause();
									case 7:
										game_music_7.pause();
									case 8:
										game_music_8.pause();
									}

									music_losing.play();
									//playField.openAll(debug);
									losing = 1;
								}
							}
						}

						
					}

					if (event1.key.code == Keyboard::Space)
					{
						//1 - 4.8
						//2 - 4.36
						//3 - 4
						//4 - 3.69
						//5 - 3.42
						//6 - 3.2
						//7 - 3
						//8 - 2.82 - 5.64 (= 2.82)
						if (music_mode == 1 && (music_timer >= 9.6))
						{
							music_time.restart();
							music_mode = 2;
						}
						else
							if (music_mode == 2 && (music_timer >= 8.72))
							{
								music_time.restart();
								music_mode = 3;
							}
							else
								if (music_mode == 3 && (music_timer >= 8))
								{
									music_time.restart();
									music_mode = 4;
								}
								else
									if (music_mode == 4 && (music_timer >= 7.38))
										{
											music_time.restart();
											music_mode = 5;
										}
									else
										if (music_mode == 5 && (music_timer >= 6.84))
											{
												music_time.restart();
												music_mode = 6;
											}
										else
											if (music_mode == 6 && (music_timer >= 6.4))
												{
													music_time.restart();
													music_mode = 7;
												}
											else
												if (music_mode == 7 && (music_timer >= 6))
													{
														music_time.restart();
														music_mode = 8;
													}
						switch (music_mode)
						{
						case 1:
							game_music_1.play();
							break;
						case 2:
							game_music_1.pause();
							game_music_2.play();
							break;
						case 3:
							game_music_2.pause();
							game_music_3.play();
							break;
						case 4:
							game_music_3.pause();
							game_music_4.play();
							break;
						case 5:
							game_music_4.pause();
							game_music_5.play();
							break;
						case 6:
							game_music_5.pause();
							game_music_6.play();
							break;
						case 7:
							game_music_6.pause();
							game_music_7.play();
							break;
						case 8:
							game_music_7.pause();
							game_music_8.play();
							break;
						}  


						//playField.printFlaged(debug);
						//playField.printBombCount(cursX, cursY, debug);
						//if (playField.getOpenly(cursX, cursY == 0))

						if (playField.getFlaged(cursX, cursY) == 0)
						{
							if(playField.getOpenly(cursX, cursY) == 0)
							{
								playField.setFlaged(cursX, cursY);
								//playField.m_numberOfFlags++;
							}
							
							
							//if (music_int < 8);
								//это изменю позже
							//music_mode = (9 - music_int--);
						}
						//playField.setOpenly(cursX, cursY);
						else
						{
							playField.setUnflaged(cursX, cursY);
							//music_mode--;
							//playField.m_numberOfFlags--;
						//	music_int++;
						}
						//playField.setClosely(cursX, cursY);

						if (debug == 1)
						{
							std::cout << "there r " << playField.m_numberOfFlags << " bombs" << std::endl;
							
							for (int countY = 0; countY < 10; countY++)
							{
								for (int countX = 0; countX < 10; countX++)
								{
									std::cout << playField.getFlaged(countX, countY) << " ";
								}
								std::cout << std::endl;
							}
						}

						
						if (playField.checkEmpties(debug) == 1)
						{
							if (playField.checkResult(debug) == 1)
							{
								switch (music_mode)
								{
								case 1:
									game_music_1.pause();
								case 2:
									game_music_2.pause();
								case 3:
									game_music_3.pause();
								case 4:
									game_music_4.pause();
								case 5:
									game_music_5.pause();
								case 6:
									game_music_6.pause();
								case 7:
									game_music_7.pause();
								case 8:
									game_music_8.pause();
								}

								music_winning.play();
								winning = 1;
							}
							else
							{
								switch (music_mode)
								{
								case 1:
									game_music_1.pause();
								case 2:
									game_music_2.pause();
								case 3:
									game_music_3.pause();
								case 4:
									game_music_4.pause();
								case 5:
									game_music_5.pause();
								case 6:
									game_music_6.pause();
								case 7:
									game_music_7.pause();
								case 8:
									game_music_8.pause();
								}

								music_losing.play();
								//playField.openAll(debug);
								losing = 1;
							}
						}
						
					}
				}

				if (exit == 1)
				{
					if (event1.key.code == Keyboard::A)
					{

						if (exit_accept == 1)
						{
							exit_accept = 0;
							pick.play();
						}
						else
						{
							exit_accept = 1;
							pick.play();
						}
					}

					if (event1.key.code == Keyboard::D)
					{
						if (exit_accept == 0)
						{
							exit_accept = 1;
							pick.play();
						}
						else
						{
							exit_accept = 0;
							pick.play();
						}
					}

					if (event1.key.code == Keyboard::Enter)
					{
						if (exit_accept == 1)
						{
							exitOut.play();
							exitSilence.pause();
							switch (music_mode)
							{
							case 1:
								game_music_1.play();
								break;
							case 2:
								game_music_2.play();
								break;
							case 3:
								game_music_3.play();
								break;
							case 4:
								game_music_4.play();
								break;
							case 5:
								game_music_5.play();
								break;
							case 6:
								game_music_6.play();
								break;
							case 7:
								game_music_7.play();
								break;
							case 8:
								game_music_8.play();
								break;
							}
							exit = 0;
						}
						
						if (exit_accept == 0)
							return 1;

						exit_accept = 0;
					}
				}
			}
		}

		//цикл открывани€ соседних с открытой игроком клеткой
		for (int countY = 0; countY < 10; countY++)
			for (int countX = 0; countX < 10; countX++)
			{
				if ((playField.getOpenly(countX, countY) == 1) && playField.getBombCount(countX, countY) == 0)
				{
					playField.openAround(countX, countY);
				}
			}

		//отрисовка бекграунда (с вращением)
		{
			window.clear(Color::Green);
			game_bg_sprite.rotate(0.05);
			window.draw(game_bg_sprite);
			window.draw(frame);
			window.draw(sprite_info);
		}

		//отрисовка пол€
		width = 320; 
		height = 40;
		cageSize = 64;
		for (int countY = 0; countY < size; countY++)
			{
				for (int countX = 0; countX < size; countX++)
				{
					if (playField.getOpenly(countX, countY) == 0)
					{
						empty_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
						window.draw(empty_sprite);
					}
					else
					{
						switch (playField.getBombCount(countX, countY))
							{
							case 0:
								zero_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(zero_sprite);
								break;
							case 1:
								i_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(i_sprite);
								break;
							case 2:
								ii_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(ii_sprite);
								break;
							case 3:
								iii_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(iii_sprite);
								break;
							case 4:
								iv_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(iv_sprite);
								break;
							case 5:
								v_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(v_sprite);
								break;
							case 6:
								vi_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(vi_sprite);
								break;
							case 7:
								vii_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(vii_sprite);
								break;
							case 8:
								iix_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(iix_sprite);
								break;
							default:
								b_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
								window.draw(b_sprite);
								break;
							}
					}

					if (playField.getFlaged(countX, countY) == 1)
					{
						f_sprite.setPosition(width + (countX * cageSize), height + (countY * cageSize));
						window.draw(f_sprite);
					}
				}
			}
			
		//отрисовка курсора
		cursor_sprite.setPosition(width + ((cursX) * cageSize), height + ((cursY) * cageSize));
		window.draw(cursor_sprite);

		//отрисовка счЄтчика
		if (!exit && !losing && !winning)
		{
			seconds = clock.getElapsedTime().asSeconds();
			if (seconds == 60)
			{
				minutes++;
				clock.restart();
			}
			if (seconds < 10)
			{
				time.setString(std::to_string(minutes) + ":0" + std::to_string(seconds));
			}
			else
				time.setString(std::to_string(minutes) + ":" + std::to_string(seconds));
		}
		window.draw(time);

		//изменени€ всего экрана
		
		//отрисовка окна проигрыша
		if (losing == 1)
		{
			window.draw(darkPlate);
			if (losing_accept == 0)
			{
				sprite_no.setColor(Color(150, 0, 0, 255));
				sprite_yes.setColor(Color(255,255,255,180));
			}
			else
			{
				sprite_yes.setColor(Color(150, 0, 0, 255));
				sprite_no.setColor(Color(255, 255, 255, 180));
			}

			sprite_losing_bg.setPosition(340, 195);
			window.draw(sprite_losing_bg);

			sprite_yes.setPosition(415, 395);
			window.draw(sprite_yes);
			sprite_no.setPosition(665, 395);
			window.draw(sprite_no);
		}

		//отрисовка окна выигрыша
		if (winning == 1)
		{
			window.draw(darkPlate);
			if (winning_accept == 0)
			{
				sprite_no.setColor(Color(150, 0, 0, 255));
				sprite_yes.setColor(Color(255, 255, 255, 180));
			}
			else
			{
				sprite_yes.setColor(Color(150, 0, 0, 255));
				sprite_no.setColor(Color(255, 255, 255, 180));
			}

			sprite_winning_bg.setPosition(340, 195);
			window.draw(sprite_winning_bg);

			sprite_yes.setPosition(415, 395);
			window.draw(sprite_yes);
			sprite_no.setPosition(665, 395);
			window.draw(sprite_no);
		}

		//отрисовка окна выхода
		if (exit == 1)
		{
			window.draw(darkPlate);
			if (exit_accept == 1)
			{
				sprite_no.setColor(Color(150, 0, 0, 255));
				sprite_yes.setColor(Color(255, 255, 255, 180));
			}
			else
			{
				sprite_yes.setColor(Color(150, 0, 0, 255));
				sprite_no.setColor(Color(255, 255, 255, 180));
			}

			sprite_exit_bg.setPosition(340, 195);
			window.draw(sprite_exit_bg);

			sprite_yes.setPosition(415, 395);
			window.draw(sprite_yes);
			sprite_no.setPosition(665, 395);
			window.draw(sprite_no);
		}
		window.display();
	}

	return 0;
}