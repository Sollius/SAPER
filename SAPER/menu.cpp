#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;



int menu(RenderWindow& window, int& diff, int& size, int debug)
{
	//ContextSettings settings;
	//settings.antialiasingLevel = 64;

	bool exit = 0, exitAccept = 0, exit1 = 0;
	int menuCount = 0;

	//музычку нарулил (закомментировано для того, чтобы создать иллюзию безпрерывного звучания позже)
	Music menu_music_bg_1;
	{
		//Music menu_music_bg_2;
		menu_music_bg_1.openFromFile("sounds\\menu_bg.ogg");
		//menu_music_bg_2.openFromFile("C:\\Users\\Professional\\source\\repos\\SAPER\\sounds\\menu_bg.ogg");
		menu_music_bg_1.setLoopPoints(Music::TimeSpan(seconds(0), seconds(69.6)));
		//menu_music_bg_2.setLoopPoints(Music::TimeSpan(seconds(0), seconds(69.6)));
		menu_music_bg_1.setLoop(1);
		//menu_music_bg_2.setLoop(1);
		menu_music_bg_1.play();
		//Time loop = seconds(69.6);
	}

	//и звуки
	SoundBuffer buffer;
	Sound pick;
	{
		buffer.loadFromFile("sounds\\pick.ogg");
		pick.setBuffer(buffer);
	}

	//конструкторы ттекстур
	Texture menu_bg_txt, accept_txt, accept_yes_txt, accept_no_txt,
		menu_logo_txt, menu_button_new_txt, menu_button_opt_txt, menu_button_exit_txt;

	//loading files
	{
		menu_bg_txt.loadFromFile("img\\menu_bg1.png");
		accept_txt.loadFromFile("img\\accept.png");
		accept_yes_txt.loadFromFile("img\\accept_yes_big.png");
		accept_no_txt.loadFromFile("img\\accept_no_big.png");
		menu_logo_txt.loadFromFile("img\\menu_logo.png");
		menu_button_new_txt.loadFromFile("img\\new.png");
		menu_button_opt_txt.loadFromFile("img\\opt.png");
		menu_button_exit_txt.loadFromFile("img\\exit_button.png");
	}
	
	//конструкторы спрайтов
	Sprite bg_sprite(menu_bg_txt), accept_sprite(accept_txt), accept_yes_sprite(accept_yes_txt), accept_no_sprite(accept_no_txt),
		menu_logo_sprite(menu_logo_txt), menu_button_new_sprite(menu_button_new_txt), menu_button_opt_sprite(menu_button_opt_txt),
		menu_button_exit_sprite(menu_button_exit_txt);

	//текстуры и спрайты
	{
		menu_logo_sprite.move(40, 20);
		menu_button_new_sprite.move(730, 323);
		menu_button_opt_sprite.move(736, 423);
		menu_button_exit_sprite.move(942, 603);

		accept_sprite.move(770, 480);
		accept_no_sprite.move(800, 580);
		accept_yes_sprite.move(980, 580);
	}

	while (window.isOpen())
	{
		Event event1;
		while (window.pollEvent(event1))
		{
			if (event1.type == Event::Closed)
			{
				exit1 = 1;
			}

			if (event1.type == Event::KeyPressed)
			{

				if (event1.key.code == Keyboard::Escape)
				{
					if (exit == 0)
						exit1 = 1;
					else
						exit1 = 0;
				}

				//if (exit == 0)

				if (event1.key.code == Keyboard::W && exit == 0)
				{
					menuCount--;
					pick.play();
				}
				if (event1.key.code == Keyboard::S && exit == 0)
				{
					menuCount++;
					pick.play();
				}
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
					{
						exitAccept = 1;
						pick.play();
					}
				if (event1.key.code == Keyboard::A)
					if (exit == 1)
					{
						exitAccept = 0;
						pick.play();
					}

				if (IntRect(730, 323, 300, 50).contains(Mouse::getPosition(window)) && exit == 0)
				{ 
					menuCount = 1; 
				}
				if (IntRect(736, 423, 300, 50).contains(Mouse::getPosition(window)) && exit == 0)
				{ 
					menuCount = 2; 
				}
				if (IntRect(942, 603, 300, 50).contains(Mouse::getPosition(window)) && exit == 0)
				{ 
					menuCount = 3; 
				}

				if (Mouse::isButtonPressed(Mouse::Left))
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

				}

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


		//}		*/
			}
		}

		//отрисовка
		{
			window.clear(Color::Green);
			window.draw(bg_sprite);
			window.draw(menu_logo_sprite);
			window.draw(menu_button_new_sprite);
			window.draw(menu_button_opt_sprite);
			window.draw(menu_button_exit_sprite);
		}
		switch (menuCount)
		{
		case 0:
			menu_button_new_sprite.setColor(Color::Red);
			menu_button_opt_sprite.setColor(Color::White);
			menu_button_exit_sprite.setColor(Color::White);
			break;

		case 1:
			menu_button_new_sprite.setColor(Color::White);
			menu_button_opt_sprite.setColor(Color::Red);
			menu_button_exit_sprite.setColor(Color::White);
			break;

		case 2:
			menu_button_new_sprite.setColor(Color::White);
			menu_button_opt_sprite.setColor(Color::White);
			menu_button_exit_sprite.setColor(Color::Red);
			break;
		}

		if (exit1 == 1)
			exit = 1;
		else
			exit = 0;

		//отрисовка окна выхода
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
