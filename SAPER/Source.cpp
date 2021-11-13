#include <SFML/Graphics.hpp>
#include <time.h>
#include <Windows.h>

using namespace sf;

int game(RenderWindow& window, int& diff, int& size, int debug);
int menu(RenderWindow& window, int& diff, int& size, int debug);

bool debug = 0;

/*
bool exit(RenderWindow& window)
{
	Texture accept_txt, accept_yes_txt, accept_no_txt;

	accept_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\accept.png");
	accept_yes_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\accept_yes_big.png");
	accept_no_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\accept_no_big.png");

	Sprite accept_sprite(accept_txt), accept_yes_sprite(accept_yes_txt), accept_no_sprite(accept_no_txt);

	accept_sprite.move(770, 480);
	accept_no_sprite.move(800, 580);
	accept_yes_sprite.move(980, 580);

	bool exitAccept = 0, exit1 = 1;

	while (window.isOpen())
	{
		Event exitEvent;
		while (window.pollEvent(exitEvent))
		{
			if (exitEvent.key.code == Keyboard::Escape)
			{
				return 0;
			}

			if (exitEvent.key.code == Keyboard::D)
				exitAccept = 1;
			if (exitEvent.key.code == Keyboard::A)
				exitAccept = 0;

			if (exitEvent.key.code == Keyboard::Enter)
				if (exitAccept == 0)
					return 0;
				else
				{
					window.close();
					return 1;
				}
			
		}

		if (exit1 == 1)
		{
			window.draw(accept_sprite);
			window.draw(accept_yes_sprite);
			window.draw(accept_no_sprite);
		}
		
		if (exitAccept == 0)
		{
			accept_no_sprite.setColor(Color::Red);
			accept_yes_sprite.setColor(Color::White);
		}
		else
		{
			accept_no_sprite.setColor(Color::White);
			accept_yes_sprite.setColor(Color::Red);
		}

		window.clear(Color(Color::Red));
	}
}
*/ 
//ненужная походу функция выхода 
/*

int menu(RenderWindow& window)
{
	ContextSettings settings;
	settings.antialiasingLevel = 64;

	bool exit = 0, exitAccept = 0, exit1 = 0;
	int menuCount = 0;

	
		Texture menu_bg_txt, accept_txt, accept_yes_txt, accept_no_txt,
			menu_logo_txt, menu_button_new_txt, menu_button_opt_txt, menu_button_exit_txt;
		{
			menu_bg_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\menu_bg1.png");
			accept_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\accept.png");
			accept_yes_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\accept_yes_big.png");
			accept_no_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\accept_no_big.png");
			menu_logo_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\menu_logo.png");
			menu_button_new_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\new.png");
			menu_button_opt_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\opt.png");
			menu_button_exit_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\exit_button.png");
		}
		//loading files

		Sprite bg_sprite(menu_bg_txt), accept_sprite(accept_txt), accept_yes_sprite(accept_yes_txt), accept_no_sprite(accept_no_txt),
			menu_logo_sprite(menu_logo_txt), menu_button_new_sprite(menu_button_new_txt), menu_button_opt_sprite(menu_button_opt_txt),
			menu_button_exit_sprite(menu_button_exit_txt);

		menu_logo_sprite.move(40, 20);
		menu_button_new_sprite.move(730, 323);
		menu_button_opt_sprite.move(736, 423);
		menu_button_exit_sprite.move(942, 603);

		accept_sprite.move(770, 480);
		accept_no_sprite.move(800, 580);
		accept_yes_sprite.move(980, 580);
	
	//текстуры и спрайты

	while (window.isOpen())
	{

		Event event1;
		while (window.pollEvent(event1))
		{
			if (event1.type == Event::KeyPressed)
			{

				if (event1.key.code == Keyboard::Escape)
				{
					//exit(window);
					if (exit == 0)
						exit1 = 1;
					else
						exit1 = 0;
				
				}

				//if (exit == 0)
				
				if (event1.key.code == Keyboard::W && exit == 0)
					menuCount--;
				if (event1.key.code == Keyboard::S && exit == 0)
					menuCount++;

				if (menuCount < 0)
					menuCount = 2;
				if (menuCount > 2)
					menuCount = 0;

				if (event1.key.code == Keyboard::Enter)
				{
					if (exit == 0)
					{
						if (menuCount == 0)
							return 2;
						if (menuCount == 1)
							int x = 0;
						if (menuCount == 2)
							exit1 = 1;
					}
					
					if (exit == 1)
					{
						if (exitAccept == 0)
							exit1 = 0;
						if (exitAccept == 1)
							return 0;
					}
				}

				if (event1.key.code == Keyboard::D)
					if (exit == 1)
						exitAccept = 1;
				if (event1.key.code == Keyboard::A)
					if (exit == 1)
						exitAccept = 0;

						/*
					Event acceptExit = 0;
					while (window.pollEvent(acceptExit));
					{
						if (acceptExit.type == Event::KeyPressed)
						{
							if (acceptExit.key.code == Keyboard::D)
								exitAccept = 1;

							if (acceptExit.key.code == Keyboard::A)
								exitAccept = 0;

							if (acceptExit.key.code == Keyboard::Enter)
								if (exitAccept == 0)
									exit = 0;
								else
									return 1;
						}
						
						//break;
						//window.close();
					//}

					
				//}
			}
		}

			window.clear(Color::Green);

			window.draw(bg_sprite);

			window.draw(menu_logo_sprite);
		
			if (menuCount == 0)
			{
				menu_button_new_sprite.setColor(Color::Red);
				menu_button_opt_sprite.setColor(Color::White);
				menu_button_exit_sprite.setColor(Color::White);
			}
			if (menuCount == 1)
			{
				menu_button_new_sprite.setColor(Color::White);
				menu_button_opt_sprite.setColor(Color::Red);
				menu_button_exit_sprite.setColor(Color::White);
			}
			if (menuCount == 2)
			{
				menu_button_new_sprite.setColor(Color::White);
				menu_button_opt_sprite.setColor(Color::White);
				menu_button_exit_sprite.setColor(Color::Red);
			}

			window.draw(menu_button_new_sprite);
			window.draw(menu_button_opt_sprite);
			window.draw(menu_button_exit_sprite);
			
			if (exit1 == 1)
				exit = 1;
			else
				exit = 0;

		if (exit == 1)
		{
			if (exitAccept == 0)
			{
				accept_no_sprite.setColor(Color::Red);
				accept_yes_sprite.setColor(Color::White);
			}
			else
			{
				accept_no_sprite.setColor(Color::White);
				accept_yes_sprite.setColor(Color::Red);
			}

			window.draw(accept_sprite);
			window.draw(accept_yes_sprite);
			window.draw(accept_no_sprite);
		}


		window.display();

	}

	return 0;
}
*/

/*
int game(RenderWindow& window)
{
	srand(time(0));

	ContextSettings settings;
	settings.antialiasingLevel = 64;

	// Переменные для таймера и задержки
	float timer = 0, delay = 1;

	// Часы (таймер)
	Clock clock;

	int bgCountX = 0, bgCountY = 0;

	Texture game_bg_txt, units_txt, 0txt, 1txt, 2txt, 3txt, 4txt, 5txt, 6txt, 7txt, 8txt, btxt, ftxt;

	game_bg_txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\game_bg_1.png");
	0txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	1txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	2txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	3txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	4txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	5txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	6txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	7txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	8txt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	btxt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");
	ftxt.loadFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\img\\units.png");

	Sprite game_bg_sprite(game_bg_txt);
	

	//game_bg_sprite.setPosition(-2000, -2000);
	game_bg_sprite.setOrigin(1000, 1000);
	game_bg_sprite.move(800, 450);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;


		Event event1;
		while (window.pollEvent(event1))
		{
			if (event1.type == Event::KeyPressed)
			{
				if (event1.key.code == Keyboard::Escape)
				{

					return 1;
					//window.close();
				}
			}
		}

		window.clear(Color::Green);

		//if (timer > delay)
		//if (bgCountX < )
		//game_bg_sprite.move(1, 1);
		game_bg_sprite.rotate(0.003);
		
		window.draw(game_bg_sprite);

		window.display();

	}

	
}
*/



int main()
{
	if (debug == 0)
	{
		HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
		ShowWindow(hConsole, SW_HIDE);
	}

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1280, 720), "SAPER");
	window.setFramerateLimit(60);
	ContextSettings settings;
	settings.antialiasingLevel = 8;
		
	int main_c = 1;
	int diff = 10;
	int size = 10;

	while (main_c)
	{
		if (main_c == 1)
			main_c = menu(window, diff, size, debug);
		if (main_c == 2)
			main_c = game(window, diff, size, debug);
	}

	return 0;
}

